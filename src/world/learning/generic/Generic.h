/*
 * generic.h
 *
 *  Created on: 2019/02/08
 *      Author: yusuke
 */

#ifndef GENERIC_H_
#define GENERIC_H_

#include <FxAgent.h>
#include <utility.h>
#include <tracelog.h>
#include <errorlog.h>

class Generic {
	int cnt;
	vector<FxAgent *> agents;
	double pmutation; // 突然変異を起こす確率
	double pcross; // 交叉確率
	double gap; // 世代間ギャップ

	vector<int> id;

	// 突然変異を受けるエージェントのインデックス
	int pmutation_start;
	int pmutation_end;
	int pcross_start;
	int pcross_end;

	// エージェントシャッフル
	int seed_shuffle; // 乱数シード
	std::mt19937 mt_shuffle;

	// 変更するかどうかの判定
	int seed_flip;
	std::mt19937 mt_flip;

	// 突然変異
	int seed_mut; // 乱数シード
	std::mt19937 mt_mut;

	int num_mutations; // 突然変異をした数

	std::uniform_int_distribution<int> rand_imp;
	std::uniform_real_distribution<double> rand_prob;

public:
	Generic();
	Generic(vector<FxAgent *> agents, double pmutation, double pcross, double gap, int seed_shuffle = 0, int seed_flip = 1, int seed_mut = 2 ) :
		agents(agents), pmutation(pmutation), pcross(pcross), gap(gap),
		seed_shuffle(seed_shuffle), seed_flip(seed_flip), seed_mut(seed_mut),
		mt_shuffle(seed_shuffle), mt_flip(seed_flip), mt_mut(seed_mut),
		rand_imp(-4,4), rand_prob(0.0,1.0), cnt(0) {

		if ( this->pmutation >= 0.0 && this->pmutation <= 1.0 ) {
		} else {
			errorlog::error("pmutation is invalid value");
		}
		if ( this->pcross >= 0.0 && this->pcross <= 1.0 ) {
		} else {
			errorlog::error("pcross is invalid value");
		}
		if ( this->gap >= 0.0 && this->gap <= 1.0 ) {
		} else {
			errorlog::error("gap is invalid value");
		}
		this->pcross_start = 0;
		this->pcross_end = (int)( this->gap * this->agents.size() ) - 1;
		this->pmutation_start = this->pcross_end;
		this->pmutation_end = this->agents.size() - 1;
		if ( this->pmutation_start > this->pmutation_end ) {
			this->pmutation_start = this->pmutation_end;
		}
	}

	virtual ~Generic();

	void info() {
		tracelog::tag("GenericAlgorithParameter");
		tracelog::keyvalue("pmutation", to_string(this->pmutation));
		tracelog::keyvalue("pcross", to_string(this->pcross));
		tracelog::keyvalue("gap", to_string(this->gap));
		tracelog::keyvalue("pcross_start", to_string(this->pcross_start));
		tracelog::keyvalue("pcross_end", to_string(this->pcross_end));
		tracelog::keyvalue("pmutation_start", to_string(this->pmutation_start));
		tracelog::keyvalue("pmutaiton_end", to_string(this->pmutation_end));
		tracelog::keyvalue("num agents", to_string(this->agents.size()));
	}

	void learning() {
		// エージェントをシャッフル
		this->shuffle();
		// 突然変異
		this->mutation();
		cout << "num mutations: " << this->num_mutations << endl;
		this->cnt++;
	}

	void shuffle() {
		this->id = this->make_rand_array_unique( this->agents.size(), 0, this->agents.size() - 1);
	}

	void mutation() {
		int num_mutations = 0;
		for ( int i = this->pmutation_start; i <= this->pmutation_end; i++ ) {
			int select_id = this->id[ i ];
			FxAgent *pagent = this->agents[ select_id ];
			// 重要度のループ(17)
			for ( int j = 0; j < FxAgent::getNumVariables(); j++ ) {
				if( this->flip( this->pmutation ) ) {
					int imp = this->random_imp();
					// 値が同じだったらもう一度
					if ( imp == pagent->getW( j ) ) {
						j--;
						continue;
					}
					pagent->setImportance(j, imp);
					num_mutations++;
				}
			}
		}
		this->num_mutations = num_mutations;
	}

	void cross() {
		for ( int i = this->pcross_start; i <= this->pcross_end; i+=2 ) {
			int select_id =
		}
	}

	bool flip( double prob ) {
		if ( prob == 1.0 ) return true;
		/* rand_prob は[0.0, 1.0)の範囲 */
		double p = this->rand_prob( this->mt_flip);
		if ( p <= prob ) {
			return true;
		}
		return false;
	}

	double random_imp() {
		return this->decode( this->rand_imp( this->mt_flip ) );
	}

	double decode(int x) {
		double Result;
		switch (x) {
		case 4:
			Result = 3.0;
			break;

		case 3:
			Result = 1.0;
			break;

		case 2:
			Result = 0.5;
			break;

		case 1:
			Result = 0.1;
		    break;

		case 0:
	    	Result = 0.0;
	    	break;

		case -1:
			Result = -0.1;
			break;

		case -2:
			Result = -0.5;
		    break;

		case -3:
			Result = -1.0;
			break;

		case -4:
			Result = -3.0;
			break;
		}
		return Result;
	}

	std::vector<int> make_rand_array_unique(const size_t size, int rand_min, int rand_max){
		if(rand_min > rand_max) std::swap(rand_min, rand_max);
	    const size_t max_min_diff = static_cast<size_t>(rand_max - rand_min + 1);
	    if(max_min_diff < size) throw std::runtime_error("引数が異常です");

	    std::vector<int> tmp;
	    auto engine = this->mt_shuffle;
	    std::uniform_int_distribution<int> distribution(rand_min, rand_max);

	    const size_t make_size = static_cast<size_t>(size*1.2);

	    while(tmp.size() < size){
	        while(tmp.size() < make_size) tmp.push_back(distribution(engine));
	        std::sort(tmp.begin(), tmp.end());
	        auto unique_end = std::unique(tmp.begin(), tmp.end());

	        if(size < std::distance(tmp.begin(), unique_end)){
	            unique_end = std::next(tmp.begin(), size);
	        }
	        tmp.erase(unique_end, tmp.end());
	    }

	    std::shuffle(tmp.begin(), tmp.end(), engine);
	    return std::move(tmp);
	}

	/* setter */
	void addAgent(FxAgent *agent) {
		this->agents.push_back(agent);
	}
};

#endif /* GENERIC_H_ */
