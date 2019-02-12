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
#include <math.h>
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
	int predict_max_width; // 2
	double min_band_lweeks; // 3
	double min_band; // 4
	double min_band_five_weeks; // 5
	int num_agents; // 6
	int train_start_date; // 7
	int train_end_date; // 8
	int predict_start_date; // 9
	int predict_end_date; // 10
	int train_term_length; // 11
	double train_pcross; // 12
	double train_pmutation; // 13
	double train_gap; // 14
	double predict_pcross; // 15
	double predict_pmutation; // 16
	double predict_gap; // 17
	int sim_iter; // 18
	int train_iter; // 19
	string output_type; // 20

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
		this->predict_max_width = atoi( strs[0].c_str() );
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
		/* 11 */
		getline( ifs, str );
		strs = utility::split(str, '\t');
		this->train_pcross = atof ( strs[0].c_str() );
		/* 12 */
		getline( ifs, str );
		strs = utility::split(str, '\t');
		this->train_pmutation = atof ( strs[0].c_str() );
		/* 13 */
		getline( ifs, str );
		strs = utility::split(str, '\t');
		this->train_gap = atof( strs[0].c_str() );
		/* 14 */
		getline( ifs, str );
		strs = utility::split(str, '\t');
		this->predict_pcross = atof ( strs[0].c_str() );
		/* 15 */
		getline( ifs, str );
		strs = utility::split(str, '\t');
		this->predict_pmutation = atof ( strs[0].c_str() );
		/* 16 */
		getline( ifs, str );
		strs = utility::split(str, '\t');
		this->predict_gap = atof( strs[0].c_str() );
		/* 17 */
		getline( ifs, str );
		strs = utility::split(str, '\t');
		this->sim_iter = atoi( strs[0].c_str() );
		/* 18 */
		getline( ifs, str );
		strs = utility::split(str, '\t');
		this->train_iter = atoi( strs[0].c_str() );
		/* 19 */
		getline( ifs, str );
		strs = utility::split(str, '\t');
		this->output_type = strs[0];

		return true;
	}

	/* getter */
	double getScaleFactor() {
		return this->scale_factor;
	}
	int predictMaxWidth() {
		return this->predict_max_width;
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
	double getTrainPcross() {
		return this->train_pcross;
	}
	double getTrainPmutation() {
		return this->train_pmutation;
	}
	double getTrainGap() {
		return this->train_gap;
	}
	double getPredictPcross() {
		return this->predict_pcross;
	}
	double getPredictPmutation() {
		return this->train_pmutation;
	}
	double getPredictGap() {
		return this->train_gap;
	}
};

#endif /* FXSIMULATIONPARAMETERS_H_ */
