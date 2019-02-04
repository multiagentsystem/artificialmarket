/*
 * FxAgent.h
 *
 *  Created on: 2019/01/18
 *      Author: naritomi
 */

#ifndef SRC_AGENTS_FX_FXAGENT_H_
#define SRC_AGENTS_FX_FXAGENT_H_


#include <iostream>
#include <vector>
#include <list>
#include <random>
#include <functional>
#include <math.h>
#include <Environment.h>
#include <FxMarket.h>
#include <News.h>
#include <Agent.h>

const int NUM_VARIABLES = 17;

class FxAgent : public Agent {
private:
	FxMarket *fxmarket;
	News *news;
	int x[NUM_VARIABLES]; // characteristic value
	int w[NUM_VARIABLES]; // importance of an agnet
	std::list<Environment *> envs; // environments
	double alpha; // scale factor
	double exlogrtn; // expectation of logarithmic return
	double var; // variance of logarithmic return

	double min_band_lweeks; // 先週の変動幅の最小単位
	double min_band; // 変動の変動幅の最小単位
	double min_band_five_weeks; // 5週間の変動幅の最小単位

public:
	FxAgent();
	virtual ~FxAgent();

	void next() {
		this->see();
		this->action();
	}

	/* get information from the environments. */
	void see() {
		vector<int> news_importance = this->news->getImportance();
		int internal_var1 = this->fxmarket->getRate();
		//vector<int> market_importance =
//		cout << "2" << endl;
//		cout << news_importance.size() << endl;


//		for ( int i = 0; i < news_importance.size(); i++ ) {
//			cout << news_importance[i] << endl;
//		}
	}

	void action() {
	}

	/* initialization of importances by random number */
	void init_importances( int seed ) {
		std::mt19937 rand_src(seed);
		std::uniform_int_distribution<int> rand_dist(-3, 3); // w = [ -3, 3 ]
		for ( int i = 0; i < NUM_VARIABLES; i++ ) {
			this->w[ i ] = rand_dist( rand_src );
		}
	}

	void predict() {
		this->exlogrtn = this->calcExLogRtn();
	}

	double calcExLogRtn() {
		double exlogrtn = 0.0;
		for ( int i = 0; i < NUM_VARIABLES; i++ ) {
			exlogrtn += this->x[ i ] * this->w[ i ];
		}
		exlogrtn *= this->alpha;
		return floor(exlogrtn) * this->alpha;
	}

	/* setter */
	void setFxMarket( FxMarket* fxmarket ) {
		this->fxmarket = fxmarket;
	}
	void setNews( News* news ) {
		this->news = news;
	}
	void setInternalInfo(double trend1, double trend2, double trend3) {
		this->min_band_lweeks = trend1; // 先週の変動幅の最小単位
		this->min_band = trend2; // 変動の変動幅の最小単位
		this->min_band_five_weeks = trend3; // 5週間の変動幅の最小単位
	}

	vector<int> getW() {
		vector<int> w_int;
		for( int i = 0; i < NUM_VARIABLES; i++ ) {
			w_int.push_back( w[i] );

		}
		return w_int;
	}

};

#endif /* SRC_AGENTS_FX_FXAGENT_H_ */
