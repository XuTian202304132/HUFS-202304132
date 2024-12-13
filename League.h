/* [주석 1 : 과제 설명]
   컴퓨터 프로그래밍 및 실습 평가과제 (배점 25점)
   학과 :컴퓨터공학부
   학번 :202304132
   이름 :서첨
   과제 주제 : 미래의 축구 - 9개 팀의 축구 리그 시뮬레이션
*/
#ifndef LEAGUE_H
#define LEAGUE_H

#include "Team.h"
#include <vector>
#include <string>

/* [Comment:
   League class manages 9 teams, simulates matches, shows standings.
   12.13 Number (1 to 9) instead of name.
*/

class League {
private:
    std::vector<Team*> teams;
    bool simulated;
public:
    League();
    ~League();
    void addTeam(Team* t);
    void simulateLeague();
    void showStandings() const;
    void showTeam(int teamNumber) const;
    void oneOnOneMatch(int teamA, int teamB) const;
    int getTeamCount() const { return (int)teams.size(); }
    void resetAllPoints();

private:
    Team* getTeamByNumber(int number) const;
};

#endif
