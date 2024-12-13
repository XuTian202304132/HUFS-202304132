﻿/* [주석 1 : 과제 설명]
   컴퓨터 프로그래밍 및 실습 평가과제 (배점 25점)
   학과 :컴퓨터공학부
   학번 :202304132
   이름 :서첨
   과제 주제 : 미래의 축구 - 9개 팀의 축구 리그 시뮬레이션
*/

#ifndef LEAGUEENTITY_H
#define LEAGUEENTITY_H

#include <string>

class LeagueEntity {
public:
    virtual ~LeagueEntity() {}
    virtual std::string getName() const = 0;
};

#endif