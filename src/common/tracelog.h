/*
 * tracelog.h
 *
 *  Created on: 2019/01/23
 *      Author: naritomi
 */

#ifndef SRC_COMMON_TRACELOG_H_
#define SRC_COMMON_TRACELOG_H_

#include <iostream>
#include <string>
using namespace std;

class tracelog {
public:
	tracelog();
	virtual ~tracelog();

	/* tagging */
	static void tag(const string& tag) {
		cout << "#####################################################" << endl;
		cout << "$" << tag << endl;
		cout << "#####################################################" << endl;
	}

	/* separator */
	static void sep() {
		cout << "-----------------------------------------------------" << endl;
	}
	static void sep_plus_minus() {
		cout << "+----------------------------------------------------" << endl;
	}

	static void keyvalue(string key, string value) {
		cout << key << " : " << value << endl;
	}
};

#endif /* SRC_COMMON_TRACELOG_H_ */
