/*
 * errorlog.h
 *
 *  Created on: 2019/01/23
 *      Author: naritomi
 */

#ifndef SRC_COMMON_ERRORLOG_H_
#define SRC_COMMON_ERRORLOG_H_

#include <iostream>
#include <string>

using namespace std;

class errorlog {
public:
	errorlog();
	virtual ~errorlog();

	static void error(const string& mesg) {
		cerr << "Error: " << mesg << endl;
	}

	static void abort() {
		exit(1);
	}
};

#endif /* SRC_COMMON_ERRORLOG_H_ */
