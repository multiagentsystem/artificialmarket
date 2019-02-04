/*
 * main.cpp
 *
 *  Created on: 2019/01/18
 *      Author: yusuke
 */

#include <vector>
#include <string>
#include <list>
#include <World.h>
#include <FxMarket.h>
#include <News.h>
#include <FxAgent.h>
#include <tracelog.h>
#include <errorlog.h>
#include <utility.h>
#include "FxSimulationParameters.h"

using namespace std;

int main(int argc, char *argv[]) {

	/* Parameter Read */
	FxSimulationParameters param;
	param.init();
	if ( !param.readFile() ) {
		errorlog::error("File read failed.");
		return -1;
	}
	param.info();

	/* read fx.dat */
	RealFx realfx( param.getFxFilePath(), 0, param.getMaxgen() );
	vector<int> date = realfx.getDate();
	vector<double> rtn = realfx.getRtn();
	int start = param.getTrainLength();
	int end = param.getMaxgen();
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
	News news( param.getNewsFilePath() );
	news.setName("News");

	/* output news data + date */
	ofstream outputfile("importance.txt");
	int cnt_date = 5;
	while( !news.isEof() ) {
		vector<int> imp = news.getImportance();
		outputfile << date[ cnt_date ] << "\t";
		for ( int i = 0; i < imp.size(); i++ ) {
			outputfile << imp[i] << "\t";
		}
		outputfile << endl;

		cnt_date++;
		if ( cnt_date >= date.size() ) break;
		news.next();
	}
	news.restart();

	/* registration to world */
	world.regist( &fxmarket );
	world.regist( &news );

	/* create agents */
	tracelog::tag("Registration Agent");
	vector<FxAgent> ages( param.getNumAgents() );
	for ( int i = 0; i < param.getNumAgents(); i++ ) {
		FxAgent *age = &ages[ i ];

		// regist to the world
		world.regist( age );

		/* name of agent */
		char buf[1024];
		sprintf(buf, "%d", i + 1);
		string str(buf);
		string name( "Agent-" + str );
		age->setName( name );
		age->setInternalInfo( param.getITrend1(), param.getITrend2(), param.getITrend3() );

		/* initilize importances */
		age->init_importances( i ); // first arugument is random seed.

		/* list of environments that agent joins. */
		age->env_in( &fxmarket );
		age->env_in( &news );
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

	// 実行
	for( int i = 5; i < date.size(); i++ ) {
		cout << date[i] << endl;

		world.see();

		exit(1);


		world.next();
	}

	return 0;
}



