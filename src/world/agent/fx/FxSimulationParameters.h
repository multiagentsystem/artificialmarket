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
	int train_start_date; // 7
	int train_end_date; // 8
	int predict_start_date; // 9
	int predict_end_date; // 10
	int train_term_length; // 11
	double prob_cross; // 12
	double prob_mutation; // 13
	double prob_gap; // 14
	int sim_iter; // 15
	int train_iter; // 16
	string output_type; // 17

public:
	FxSimulationParameters();
	virtual ~FxSimulationParameters();

	void init() {
		string fxInputPath = utility::getCurrentDir() + "/" + "src/main/simulation/FX/input";

		/* news file path */
		this->newsFilePath = fxInputPath + "/" + "internal_importance.dat";

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
		oss.str("");
		oss << this->train_start_date;
		tracelog::keyvalue( " train start date", oss.str().c_str());
		oss.str("");
		oss << this->train_end_date;
		tracelog::keyvalue( " train end date", oss.str().c_str());
		oss.str("");
		oss << this->predict_start_date;
		tracelog::keyvalue( " predicit start date", oss.str().c_str());
		oss.str("");
		oss << this->predict_end_date;
		tracelog::keyvalue(" predict end date", oss.str().c_str());
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
		std::vector<string> strs;

		/* 1 */
		getline( ifs, str );
		strs = utility::split(str, '\t');
		this->scale_factor = atof( strs[0].c_str() );
		/* 2 */
		getline( ifs, str );
		strs = utility::split(str, '\t');
		this->predict_step = atoi( strs[0].c_str() );
		/* 3 */
		getline( ifs, str );
		strs = utility::split(str, '\t');
		this->min_band_lweeks = atof( strs[0].c_str() );
		/* 4 */
		getline( ifs, str );
		strs = utility::split(str, '\t');
		this->min_band = atof( strs[0].c_str() );
		/* 5 */
		getline( ifs, str );
		strs = utility::split(str, '\t');
		this->min_band_five_weeks = atof( strs[0].c_str() );
		/* 6 */
		getline( ifs, str );
		strs = utility::split(str, '\t');
		this->num_agents = atoi( strs[0].c_str() );
		/* 7 */
		getline( ifs, str );
		strs = utility::split(str, '\t');
		this->train_start_date = atoi( strs[0].c_str() );
		/* 8 */
		getline( ifs, str );
		strs = utility::split(str, '\t');
		this->train_end_date = atoi ( strs[0].c_str() );
		/* 9 */
		getline( ifs, str );
		strs = utility::split(str, '\t');
		this->predict_start_date = atoi ( strs[0].c_str() );
		/* 10 */
		getline( ifs, str );
		strs = utility::split(str, '\t');
		this->predict_end_date = atoi ( strs[0].c_str() );
		/* 10 */
		getline( ifs, str );
		strs = utility::split(str, '\t');
		this->prob_cross = atof ( strs[0].c_str() );
		/* 11 */
		getline( ifs, str );
		strs = utility::split(str, '\t');
		this->prob_mutation = atof ( strs[0].c_str() );
		/* 12 */
		getline( ifs, str );
		strs = utility::split(str, '\t');
		this->prob_gap = atof( strs[0].c_str() );
		/* 13 */
		getline( ifs, str );
		strs = utility::split(str, '\t');
		this->sim_iter = atoi( strs[0].c_str() );
		/* 14 */
		getline( ifs, str );
		strs = utility::split(str, '\t');
		this->train_iter = atoi( strs[0].c_str() );
		/* 15 */
		getline( ifs, str );
		strs = utility::split(str, '\t');
		this->output_type = strs[0];

		return true;
	}

	/* getter */
	double getScaleFactor() {
		return this->scale_factor;
	}
	int getTrainStartDate() {
		return this->train_start_date;
	}
	int getTrainEndDate() {
		return this->train_end_date;
	}
	int getPredictStartDate() {
		return this->predict_start_date;
	}
	int getPredictEndDate() {
		return this->predict_end_date;
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
