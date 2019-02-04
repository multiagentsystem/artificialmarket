/*
 * utility.h
 *
 *  Created on: 2019/01/22
 *      Author: naritomi
 */

#ifndef SRC_COMMON_UTILITY_H_
#define SRC_COMMON_UTILITY_H_

#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

class utility {
public:
	utility();
	virtual ~utility();

	/* カレントディレクトリ取得 */
	static string getCurrentDir() {
		char dir[1024];
		getcwd(dir,1024);
		string str(dir);
		return str;
	}


	/* 文字列スプリット */
	static std::vector<std::string> split(std::string str, char del) {
	    int first = 0;
	    int last = str.find_first_of(del);

	    std::vector<std::string> result;

	    while (first < str.size()) {
	        std::string subStr(str, first, last - first);

	        result.push_back(subStr);

	        first = last + 1;
	        last = str.find_first_of(del, first);

	        if (last == std::string::npos) {
	            last = str.size();
	        }
	    }

	    return result;
	}

	static double getAverage(unsigned int start, unsigned int end, vector<int> date, vector<double> vec) {
		if ( start > end ) return 0.0;
		double ave = 0.0;
		int cnt = 0;
		for ( int i = 0; i <= date.size(); i++ ) {
			if ( date[ i ] >= start && date[ i ] <= end ) {
				ave += vec[ i ];
				cnt++;
			}
		}
		ave /= cnt;
		return ave;
	}

	static double getStd(unsigned int start, unsigned int end, vector<int> date, vector<double> vec) {
		if ( start > end ) return 0.0;
		double m2 = 0.0;
		double m1 = 0.0;
		int cnt = 0;
		for ( int i = 0; i <= date.size(); i++ ) {
			if ( date[ i ] >= start && date[ i ] <= end ) {
				m2 += vec[ i ] * vec[ i ];
				m1 += vec[ i ];
				cnt++;
			}
		}
		m2 /= cnt;
		m1 /= cnt;
		double std = sqrt( m2 - m1 * m1 );
		return std;
	}

	static int roundIzumi( double x ) {
		int a = 1;
		if (x < 0) {
		    a = -1;
		}
		if ( fabs( x ) < 3 ) {
		    return ((int)fabs(x) * a);
		} else {
			if (x >= 3) {
				return 3;
			} else {
		      return -3;
			}
		}
		return 0;
	}
};

#endif /* SRC_COMMON_UTILITY_H_ */
