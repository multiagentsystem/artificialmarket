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
#include <FxSimulationParameters.h>

using namespace std;

const int NUM_FX_VARIABLES = 17;
const int NUM_FX_INTERNAL = 14;

class FxAgent : public Agent {
private:
	FxMarket *fxmarket;
	News *news;
	FxSimulationParameters *params;
	int x[NUM_FX_VARIABLES]; // characteristic value
	int w[NUM_FX_VARIABLES]; // importance of an agnet
	double exlogrtn; // expectation of logarithmic return
	double tvar; // inverse of logarithmic return variance

	double fitness; // 実際の為替との適合度

public:
	FxAgent();
	virtual ~FxAgent();

	/* get information from the environments. */
	void see() {
		vector<int> news_importance = this->news->getImportance();
		for ( int i = 0; i < NUM_FX_INTERNAL; i++ ) {
			this->x[ i ] = news_importance[ i ];
		}
		// テクニカル系はまだ未対応
		this->x[ NUM_FX_INTERNAL     ] = 0.0;
		this->x[ NUM_FX_INTERNAL + 1 ] = 0.0;
		this->x[ NUM_FX_INTERNAL + 2 ] = 0.0;
	}

	void state() {
		this->predict();
		cout << this->getName() << " exrtn:" << this->exlogrtn << " tvar:" << this->tvar << endl;
	}

	void action() {
	}

	void next() {
	}

	/* initialization of importances by random number */
	void init_importances( int seed ) {
		std::mt19937 rand_src(seed);
		std::uniform_int_distribution<int> rand_dist(-3, 3); // w = [ -3, 3 ]
		for ( int i = 0; i < NUM_FX_VARIABLES; i++ ) {
			this->w[ i ] = rand_dist( rand_src );
		}
	}

	void predict() {
		this->exlogrtn = this->calcExLogRtn();// 期待値の計算
		this->tvar = this->calcVar(); // 分散の計算
	}

	double calcExLogRtn() {
		double exlogrtn = 0.0;
		for ( int i = 0; i < NUM_FX_VARIABLES; i++ ) {
			exlogrtn += this->x[ i ] * this->w[ i ];
			//cout << this->x[i] << " " << this->w[i] << endl;
		}
		//cout << "exlogrtn: " << exlogrtn << endl;
		return utility::roundIzumi(exlogrtn, this->params->getPredictEndDate()) * this->params->getScaleFactor();
	}

	double calcVar() {
		double wplus = 0.0;
		double wminus = 0.0;
		for (int i = 0; i < NUM_FX_VARIABLES; i++) {
			double wx = this->w[ i ] * this->x[ i ];
			if ( wx > 0 ) {
				wplus += wx;
			} else {
				wminus -= wx;
		    }
		}
		return sqrt( fabs( wplus * wplus - wminus * wminus ) );
	}

	void calcFitness(double real, double pred) {
		this->fitness -= fabs( real - pred );
	}

	/* setter */
	void setFitness(double val) {
		this->fitness = val;
	}
	void setFxMarket( FxMarket* fxmarket ) {
		this->fxmarket = fxmarket;
	}
	void setNews( News* news ) {
		this->news = news;
	}
	void setFxSimulationParameters(FxSimulationParameters* params) {
		this->params = params;
	}

	/* getter */
	vector<int> getW() {
		vector<int> w_int;
		for( int i = 0; i < NUM_FX_VARIABLES; i++ ) {
			w_int.push_back( w[i] );

		}
		return w_int;
	}
	double getExLogRtn() {
		return this->exlogrtn;
	}
	double getTVar() {
		return this->tvar;
	}
	double getFitness() {
		return this->fitness;
	}

	static int getNumVariables() {
		return NUM_FX_VARIABLES;
	}
};

#endif /* SRC_AGENTS_FX_FXAGENT_H_ */
