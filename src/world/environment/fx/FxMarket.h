/*
 * FxMarket.h
 *
 *  Created on: 2019/01/18
 *      Author: naritomi
 */

#ifndef SRC_ENVIRONMENT_MARKET_FXMARKET_H_
#define SRC_ENVIRONMENT_MARKET_FXMARKET_H_

#include <string>
#include <vector>
#include <map>
#include <RealFx.h>
#include <tracelog.h>
#include <errorlog.h>
#include "Market.h"

using namespace std;

class FxMarket : public Market {
private:
	RealFx realFx;
	vector<int> importance;
	std::list<Agent *> agents;
	int idx;
	int date;
	double ln;
	double realrate;
	double rate1; // 現在
	double rate2; // 1日前
	double rate3; // 2日前
	double rate4; // 3日前
	double rate5; // 4日前

public:
	FxMarket();
	virtual ~FxMarket();

	void initialize( int date ) {
		this->idx = realFx.getID( date );
		if ( this->idx < 0 ) {
			errorlog::error("Not found date");
			errorlog::abort();
		}
		this->date = realFx.getDate(this->idx);
		this->ln = realFx.getLn(this->idx);
		this->realrate = realFx.getRtn(this->idx);
		this->rate1 = 0.0;
		this->rate2 = 0.0;
		this->rate3 = 0.0;
		this->rate4 = 0.0;
		this->rate5 = 0.0;
	}

	void next() {
		this->idx++;
		this->date = realFx.getDate(this->idx);
		if ( this->date < 0 ) {
			return;
		}
		this->ln = realFx.getLn(this->idx);
		this->realrate = realFx.getRtn(this->idx);
	}

	void regist(Agent *agent) {
		//tracelog::keyvalue("name", agent->getName() );
		this->agents.push_back(agent);
	}

	void readFxFile(const string& file, unsigned int start, unsigned int end) {
	}

	double getRealRate() {
		return this->realrate;
	}

	double getRate() {
		return this->rate1;
	}
	double getRate2() {
		return this->rate2;
	}
	double getRate3() {
		return this->rate3;
	}
	double getRate4() {
		return this->rate4;
	}
	double getRate5() {
		return this->rate5;
	}
};

#endif /* SRC_ENVIRONMENT_MARKET_FXMARKET_H_ */
