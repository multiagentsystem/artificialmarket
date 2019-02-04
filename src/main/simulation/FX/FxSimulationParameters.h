/*
 * FxSimulationParameters.h
 *
 *  Created on: 2019/01/22
 *      Author: yusuke
 */

#ifndef FXSIMULATIONPARAMETERS_H_
#define FXSIMULATIONPARAMETERS_H_

#include <tracelog.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility.h>

using namespace std;

const int NUM_FX_PARAMS = 18;

class FxSimulationParameters {
private:
	std::string newsFilePath;
	std::string paraFilePath;
	std::string fxFilePath;

	/* para.txt */
	double scale_factor; // 1
	int predict_step; // 2
	double min_band_lweeks; // 3
	double min_band; // 4
	double min_band_five_weeks; // 5
	int num_agents; // 6
	int mingen; // 7
	int maxgen; // 8
	int train_term_length; // 9
	double prob_cross; // 10
	double prob_mutation; // 11
	double prob_gap; // 12
	int sim_iter; // 13
	int train_iter; // 14
	string output_type; // 15

public:
	FxSimulationParameters();
	virtual ~FxSimulationParameters();

	void init() {
		string fxInputPath = utility::getCurrentDir() + "/" + "src/main/simulation/FX/input";

		/* news file path */
		this->newsFilePath = fxInputPath + "/" + "data.dat";

		/* parameter file path */
		this->paraFilePath = fxInputPath + "/" + "para.txt";

		/* rate file path */
		this->fxFilePath = fxInputPath + "/" + "fx.dat";
	}

	void info() {
		tracelog::tag( "ParameterInformation");
		tracelog::keyvalue("news file", this->newsFilePath);
		tracelog::keyvalue("parameter file", this->paraFilePath);
		std::ostringstream oss;
		oss << this->scale_factor;
		tracelog::keyvalue( " scaling factor", oss.str().c_str() );
		oss.str("");
		oss << this->num_agents;
		tracelog::keyvalue( " num agents", oss.str().c_str() );
	}

	bool readFile() {
		if ( !this->readParamFile( this->paraFilePath ) ) {
			cerr << "Error: file read failed: parameter" << endl;
			return false;
		}
		return true;
	}

	bool readParamFile(const std::string& fname) {
		std::ifstream ifs( fname );
		if ( ifs.fail() ) {
			std::cerr << "Not foud a parameter file" << std::endl;
			throw "Exception : file open fales.";
		}
		if( !ifs.is_open() ) return false;
		if( ifs.eof() ) return false;

		std::string str;

		/* 1 */
		getline( ifs, str );
		this->scale_factor = atof( str.c_str() );
		/* 2 */
		getline( ifs, str );
		this->predict_step = atoi( str.c_str() );
		/* 3 */
		getline( ifs, str );
		this->min_band_lweeks = atof( str.c_str() );
		/* 4 */
		getline( ifs, str );
		this->min_band = atof( str.c_str() );
		/* 5 */
		getline( ifs, str );
		this->min_band_five_weeks = atof( str.c_str() );
		/* 6 */
		getline( ifs, str );
		this->num_agents = atoi( str.c_str() );
		/* 7 */
		getline( ifs, str );
		this->mingen = atoi( str.c_str() );
		/* 8 */
		getline( ifs, str );
		this->maxgen = atoi ( str.c_str() );
		/* 9 */
		getline( ifs, str );
		this->train_term_length = atoi ( str.c_str() );
		/* 10 */
		getline( ifs, str );
		this->prob_cross = atof ( str.c_str() );
		/* 11 */
		getline( ifs, str );
		this->prob_mutation = atof ( str.c_str() );
		/* 12 */
		getline( ifs, str );
		this->prob_gap = atof( str.c_str() );
		/* 13 */
		getline( ifs, str );
		this->sim_iter = atoi( str.c_str() );
		/* 14 */
		getline( ifs, str );
		this->train_iter = atoi( str.c_str() );
		/* 15 */
		getline( ifs, str );
		this->output_type = str;

		return true;
	}

	/* getter */
	int getMingen() {
		return this->mingen;
	}
	int getMaxgen() {
		return this->maxgen;
	}
	double getITrend1() {
		return this->min_band_lweeks;
	}
	double getITrend2() {
		return this->min_band;
	}
	double getITrend3() {
		return this->min_band_five_weeks;
	}
	int getTrainLength() {
		return this->train_term_length;
	}
	string getNewsFilePath() {
		return this->newsFilePath;
	}
	string getFxFilePath() {
		return this->fxFilePath;
	}
	int getNumAgents() {
		return this->num_agents;
	}
};

#endif /* FXSIMULATIONPARAMETERS_H_ */
