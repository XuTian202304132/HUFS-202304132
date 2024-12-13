#ifndef UTILITY_H
#define UTILITY_H

#include <random>
#include <stdexcept>

/* [주석 1 : 과제 설명]
   컴퓨터 프로그래밍 및 실습 평가과제 (배점 25점)
   학과 :컴퓨터공학부
   학번 :202304132
   이름 :서첨
   과제 주제 : 미래의 축구 - 9개 팀의 축구 리그 시뮬레이션
*/
/* [Comment: A template random number generator for a given integer range]
*/

template<typename T>
class RandomGenerator {
private:
    T minVal;
    T maxVal;
    std::mt19937 gen;
public:
    RandomGenerator(T minv, T maxv) : minVal(minv), maxVal(maxv) {
        if (minVal > maxVal) {
            throw std::runtime_error("Invalid random range");
        }
        std::random_device rd;
        gen = std::mt19937(rd());
    }
    T get() {
        std::uniform_int_distribution<T> dist(minVal, maxVal);
        return dist(gen);
    }
};

#endif