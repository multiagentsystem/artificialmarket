/*
 * utility.h
 *
 *  Created on: 2019/01/22
 *      Author: naritomi
 */

#ifndef SRC_COMMON_UTILITY_H_
#define SRC_COMMON_UTILITY_H_

#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <math.h>

using namespace std;

class utility {
public:
	utility();
	virtual ~utility();

	/* カレントディレクトリ取得 */
	static string getCurrentDir() {
		char dir[1024];
		getcwd(dir,1024);
		string str(dir);
		return str;
	}


	/* 文字列スプリット */
	static std::vector<std::string> split(std::string str, char del) {
	    int first = 0;
	    int last = str.find_first_of(del);

	    std::vector<std::string> result;

	    while (first < str.size()) {
	        std::string subStr(str, first, last - first);

	        result.push_back(subStr);

	        first = last + 1;
	        last = str.find_first_of(del, first);

	        if (last == std::string::npos) {
	            last = str.size();
	        }
	    }

	    return result;
	}

	static double getAverage(unsigned int start, unsigned int end, vector<int> date, vector<double> vec) {
		if ( start > end ) return 0.0;
		double ave = 0.0;
		int cnt = 0;
		for ( int i = 0; i <= date.size(); i++ ) {
			if ( date[ i ] >= start && date[ i ] <= end ) {
				ave += vec[ i ];
				cnt++;
			}
		}
		ave /= cnt;
		return ave;
	}

	static double getStd(unsigned int start, unsigned int end, vector<int> date, vector<double> vec) {
		if ( start > end ) return 0.0;
		double m2 = 0.0;
		double m1 = 0.0;
		int cnt = 0;
		for ( int i = 0; i <= date.size(); i++ ) {
			if ( date[ i ] >= start && date[ i ] <= end ) {
				m2 += vec[ i ] * vec[ i ];
				m1 += vec[ i ];
				cnt++;
			}
		}
		m2 /= cnt;
		m1 /= cnt;
		double std = sqrt( m2 - m1 * m1 );
		return std;
	}

	static int roundIzumi( double x, double max ) {
		int a = 1;
		if (x < 0) {
		    a = -1;
		}
		if ( fabs( x ) < max ) {
		    return ((int)fabs(x) * a);
		} else {
			if (x >= max) {
				return max;
			} else {
		      return -max;
			}
		}
		return 0;
	}

	static std::mt19937 create_rand_engine(){
	    std::random_device rnd;
	    std::vector<std::uint_least32_t> v(10);// 初期化用ベクタ
	    std::generate(v.begin(), v.end(), std::ref(rnd));// ベクタの初期化
	    std::seed_seq seed(v.begin(), v.end());
	    return std::mt19937(seed);// 乱数エンジン
	}

	static std::mt19937 create_rand_engine(int seed) {
		std::mt19937 Get_random;
		Get_random.seed(seed);
		return Get_random;
	}

	static std::vector<int> make_rand_array_unique(int seed, const size_t size, int rand_min, int rand_max){
	    if(rand_min > rand_max) std::swap(rand_min, rand_max);
	    const size_t max_min_diff = static_cast<size_t>(rand_max - rand_min + 1);
	    if(max_min_diff < size) throw std::runtime_error("引数が異常です");

	    std::vector<int> tmp;
	    auto engine = create_rand_engine(seed);
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
};

#endif /* SRC_COMMON_UTILITY_H_ */
