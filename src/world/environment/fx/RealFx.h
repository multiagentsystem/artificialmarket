/*
 * RealFx.h
 *
 *  Created on: 2019/01/28
 *      Author: naritomi
 */

#ifndef SRC_WORLD_ENVIRONMENT_REALFX_H_
#define SRC_WORLD_ENVIRONMENT_REALFX_H_

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <errorlog.h>
#include <tracelog.h>
#include <utility.h>

using namespace std;

class RealFx {
	int start;
	int end;
	char frequency;
	string name;
	string code;
	vector<int> date;
	vector<double> dollyen;
	vector<double> ln;
	vector<int> week;
	vector<double> rtn;

public:
	RealFx();
	RealFx(const string& fname, int start, int end ) : start(), end(), frequency() {

		tracelog::tag("FxData");

		ifstream ifs( fname );
		vector<string> strs;
		string str, str_date;
		string year, month, day;
		char buf1[1000], buf2[1000], buf3[1000];

		/* start */
		getline(ifs, str);
		strs = utility::split(str, '\t');
		strs = utility::split(strs[1], '/');
		sprintf(buf1, "%04d", atoi(strs[0].c_str()));
		sprintf(buf2, "%02d", atoi(strs[1].c_str()));
		sprintf(buf3, "%02d", atoi(strs[2].c_str()));
		year = buf1;
		month = buf2;
		day = buf3;
		str_date = year + month + day;
		int data_start = atoi( str_date.c_str() );

		/* end */
		getline(ifs, str);
		strs = utility::split(str, '\t');
		strs = utility::split(strs[1], '/');
		sprintf(buf1, "%04d", atoi(strs[0].c_str()));
		sprintf(buf2, "%02d", atoi(strs[1].c_str()));
		sprintf(buf3, "%02d", atoi(strs[2].c_str()));
		year = buf1;
		month = buf2;
		day = buf3;
		str_date = year + month + day;
		int data_end = atoi( str_date.c_str() );

		/* frequency */
		getline(ifs, str);
		strs = utility::split(str, '\t');
		this->frequency = strs[1].c_str()[0];

		/* Name */
		getline(ifs, str);
		strs = utility::split(str, '\t');
		this->name = strs[1];

		/* Code */
		getline(ifs, str);
		strs = utility::split(str, '\t');
		this->code = strs[1];

		/* Tag but skip */
		getline(ifs, str);

		/* check and setting */
		if ( start > 0 ) {
			if ( start < data_start ) {
				errorlog::error("data from specified start does not exist in " + fname);
				errorlog::abort();
			}
			this->start = start;
		} else {
			this->start = data_start;
		}
		if ( end > 0 ) {
			if ( data_end < end ) {
				errorlog::error("data to specified end does not exist in " + fname);
				errorlog::abort();
			}
			this->end = end;
		} else {
			this->end = data_end;
		}

		int cnt = 0;
		while( true ) {
			getline(ifs, str);

			/* break check */
			if ( ifs.eof() ) break;

			vector<string> astrs = utility::split(str, '\t');

			/* date */
			strs = utility::split(astrs[0], '/');
			sprintf(buf1, "%04d", atoi(strs[0].c_str()));
			sprintf(buf2, "%02d", atoi(strs[1].c_str()));
			sprintf(buf3, "%02d", atoi(strs[2].c_str()));
			year = buf1;
			month = buf2;
			day = buf3;
			str_date = year + month + day;
			int int_date = atoi( str_date.c_str() );

			if ( this->start > int_date ||
					int_date > this->end ) break;

			this->date.push_back( int_date );

			/* doll yen */
			this->dollyen.push_back( atof( astrs[1].c_str() ) );

			/* the natural logarithm dollyen */
			this->ln.push_back( atof( astrs[2].c_str() ) );

			/* week */
			this->week.push_back( atof( astrs[3].c_str() ) );

			cnt++;
		}

		/* rtn */
		this->rtn.clear();
		this->rtn.push_back(0.0);
		for( int i = 1; i < this->ln.size(); i++ ) {
			this->rtn.push_back( this->ln[i] - this->ln[i-1] );
			// cout << this->ln[i]-this->ln[i-1] << " " << this->ln[i] << " " << this->ln[i-1] << endl;
		}

		tracelog::keyvalue("start", to_string(this->start));
		tracelog::keyvalue("end", to_string(this->end));
		tracelog::keyvalue("count", to_string(cnt));

		ifs.close();
	}
	virtual ~RealFx();


	/* getter */
	vector<int>& getDate() {
		return this->date;
	}
	vector<double>& getRtn() {
		return this->rtn;
	}
	int getDate(unsigned int idx) {
		if ( this->date.size() <= idx ) return -1;
		return this->date[ idx ];
	}
	double getLn(unsigned int idx) {
		return this->ln[ idx ];
	}
	double getRtn(unsigned int idx) {
		return this->rtn[ idx ];
	}
	int getID(int yyyymmdd) {
		for ( int i = 0; i < this->date.size(); i++ ) {
			if ( this->date[i] == yyyymmdd ) return i;
		}
		return -1;
	}

};

#endif /* SRC_WORLD_ENVIRONMENT_REALFX_H_ */
