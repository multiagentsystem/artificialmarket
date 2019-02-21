/*
 * main.cpp
 *
 *  Created on: 2019/01/18
 *      Author: yusuke
*/

#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>
#include <string>
#include <list>
#include <World.h>
#include <FxMarket.h>
#include <News.h>
#include <FxAgent.h>
#include <tracelog.h>
#include <errorlog.h>
#include <Generic.h>
#include <utility.h>
#include "FxSimulationParameters.h"

using namespace std;

int main(int argc, char *argv[]) {

	/* Parameter Read */
	FxSimulationParameters params;
	params.init();
	if ( !params.readFile() ) {
		errorlog::error("File read failed.");
		return -1;
	}
	params.info();

	/* read fx.dat */
	RealFx realfx( params.getFxFilePath() );

	vector<int> date = realfx.getDateList();
	vector<double> rtn = realfx.getRtn();
	int start = params.getTrainStartDate();
	int end = params.getPredictEndDate();
	double ave = utility::getAverage( start, end, date, rtn);
	double std = utility::getStd( start, end, date, rtn);
	tracelog::keyvalue("average", to_string(ave));
	tracelog::keyvalue("std", to_string(std));

	/* create world */
	World world;

	/* create fxmarket */
	FxMarket fxmarket;
	fxmarket.setName("FxMarket");

	/* create News */
	News news( params.getNewsFilePath() );
	news.setName("News");

	/* registration to world */
	world.regist( &fxmarket );
	world.regist( &news );

	/* create agents */
	tracelog::tag("Registration Agent");
	vector<FxAgent> ages( params.getNumAgents() );
	for ( int i = 0; i < params.getNumAgents(); i++ ) {
		FxAgent *age = &ages[i];

		// regist to the world
		world.regist( age );

		/* name of agent */
		char buf[1024];
		sprintf(buf, "%d", i + 1);
		string str(buf);
		string name( "Agent-" + str );
		age->setName( name );
		age->setFxSimulationParameters( &params );

		/* initilize importances */
		age->init_importances( i ); // first arugument is random seed.

		/* list of environments that agent joins. */
		age->setFxMarket( &fxmarket );
		age->setNews( &news );
		fxmarket.regist( age );
		news.regist( age );
	}

	// importance
	for( int i = 0; i < ages.size(); i++ ) {
		vector<int> w = ages[ i ].getW();
		cout << "Agent-" << i+1 << " ";
		for ( int i = 0; i < w.size(); i++ ) {
			cout << w[ i ] << " " ;
		}
		cout << endl;
	}

	int train_start_date_id = realfx.getID( params.getTrainStartDate() );
	int train_end_date_id = realfx.getID( params.getTrainEndDate() );
	int predict_start_date_id = realfx.getID( params.getPredictStartDate() );
	int predict_end_date_id = realfx.getID( params.getPredictEndDate() );

	cout << train_start_date_id << " " << date[train_start_date_id] << endl;
	cout << train_end_date_id << " " << date[train_end_date_id] << endl;
	cout << train_end_date_id - train_start_date_id + 1 << endl;

	cout << predict_start_date_id << " " << date[predict_start_date_id] << endl;
	cout << predict_end_date_id << " " << date[predict_end_date_id] << endl;
	cout << predict_end_date_id - predict_start_date_id + 1 << endl;

	vector<FxAgent *> pages;
	for( int i = 0; i < ages.size(); i++ ) {
		//cout << "agent-" << i << " " << ages[ i ].getFitness() << endl;
		pages.push_back( &ages[i] );
	}

	// ファイル出力(GA)
	std::ofstream writing_file;
	writing_file.open("ga_result.dat", std::ios::out);

	Generic generic( pages, params.getTrainPmutation(), params.getTrainPcross(), params.getTrainGap());
	generic.info();
	for ( int i = 0; i < params.getTrainIter(); i++ ) {
		// 全エージェントに対して訓練期間を用いた遺伝的アルゴリズムによる重要度の初期値計算
		int current_date = params.getTrainStartDate();
		news.setID( current_date );
		for( int i = 0; i < ages.size(); i++ ) {
			ages[ i ].setFitness(0.0);
		}
		// 最終時刻までなので、i < T としていることに注意 ( i=T だと1期間超えてしまう )
		for ( int i = train_start_date_id; i < train_end_date_id; i++ ) {
			int yyyymmdd = date[ i ];
			double realLogRate0 = realfx.getLn(i);
			double realLogRate1 = realfx.getLn(i+1);
			//cout << realLogRate0 << " " << realLogRate1 << endl;
			double realDiffLogRate = realLogRate1 - realLogRate0;
			for( int i = 0; i < ages.size(); i++ ) {
				ages[i].see();
				double predDiffLogRate = ages[ i ].calcExLogRtn();
				//cout << "pred: " << predDiffLogRate << endl;
				ages[ i ].calcFitness(realDiffLogRate, predDiffLogRate);
			}
			news.next();
		}
		//cout << "Enter learning" << endl;
		generic.learning();
		//cout << "End learning" << endl;

		cout << setprecision(6) << i << " " << generic.getFitness() / ages.size() << endl;
		writing_file << setprecision(6) << i << " " << generic.getFitness() / ages.size() << endl;
	}

	exit(1);

	// 実行
	tracelog::tag("Run");
	for( int i = 5; i 	< date.size(); i++ ) {
		cout << date[i] << "¥n";
		world.see();
		world.state();
		world.next();
	}

	return 0;
}



