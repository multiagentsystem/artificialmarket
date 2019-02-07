/*
 * News.h
 *
 *  Created on: 2019/01/18
 *      Author: yusuke
 */

#ifndef NEWS_H_
#define NEWS_H_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <Environment.h>
#include <utility.h>
#include <tracelog.h>
#include <errorlog.h>

using namespace std;

class News : public Environment {
private:
	static const unsigned int NUM_IMPORTANCE;
	ifstream ifs;
	vector<int> date;
	vector< vector<int> > importances;
	int initial_id;
	int id;
	std::string fname;

public:
	News(const string fname) : id(-1), initial_id(-1), fname(fname), ifs(fname) {
		if ( this->ifs.fail() ) {
			errorlog::error("Not found a news file");
			throw "Exception : Not found a news file";
		} else {
			tracelog::tag("Read news file");
			tracelog::keyvalue("news file", fname);
		}
		if( !this->ifs.is_open() ) {
			errorlog::error("File cannot open.");
		}
		if( this->ifs.eof() ) {
			errorlog::error("File is empty.");
			throw "Exception : File is empty.";
		}
		while(true) {
			if ( this->readline() == false ) break;
		}
	}

	virtual ~News() {
		if(this->ifs.is_open()) ifs.close();
	}

	bool readline() {
		std::string str;
		if ( !getline(this->ifs, str) ) return false;
		vector<string> strs = utility::split(str, '\t');
		this->date.push_back( atoi( strs[0].c_str() ) );
		vector<int> importance;
		for ( int i = 1; i < strs.size(); i++ ) {
			importance.push_back( atoi( strs[ i ].c_str() ) );
		}
		if ( importance.size() == 0 ) return false;
		if ( importance.size() != NUM_IMPORTANCE ) return false;
		this->importances.push_back( importance );
		return true;
	}

	void restart() {
		this->id = this->initial_id;
	}

	void next() {
		this->id++;
		if ( this->importances.size() > this->id + 1 ) {
			this->id++;
		} else {
			this->id = -1;
		}
	}

	void setID(int yyyymmdd) {
		this->id = -1;
		for ( int i = 0; i < this->date.size(); i++ ) {
			if ( this->date[ i ] == yyyymmdd ) {
				this->initial_id = i;
				this->id = i;
			}
		}
	}

	bool isEof() {
		if ( this->ifs.eof() ) return true;
		return false;
	}

	/* getter */
	vector< vector<int> >& getImportances() {
		return this->importances;
	}
	vector<int>& getImportance() {
		return this->importances[this->id];
	}
	vector<int>& getImportance(int id) {
		return this->importances[id];
	}
};

#endif /* NEWS_H_ */
