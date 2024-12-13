/* [주석 1 : 과제 설명]
   컴퓨터 프로그래밍 및 실습 평가과제 (배점 25점)
   학과 :컴퓨터공학부
   학번 :202304132
   이름 :서첨
   과제 주제 : 미래의 축구 - 9개 팀의 축구 리그 시뮬레이션
*/
#ifndef TEAM_H
#define TEAM_H

#include <string>
#include <vector>
#include <iostream>
#include "LeagueEntity.h"
#include "Player.h"

/* [Comment:
   - Team class inherits from LeagueEntity.
   - Each team has 11 players with ATT/DEF values.
   - TeamPupil: ATT/DEF in [0..9] They're really weak, lol.
   - Others: ATT/DEF in [30..99]
   - 12.13 Add resetPoints() method to clear points before re-simulation.
*/

class Team : public LeagueEntity {
private:
    std::string teamName;
    std::vector<Player> players;
    int points; // accumulated points
public:
    Team(const std::string& name);
    virtual ~Team() {}
    virtual std::string getName() const { return teamName; }
    void addPlayer(const Player& p);
    int getTotalSkill() const;
    int getPoints() const { return points; }
    void addPoints(int p) { points += p; }
    void resetPoints() { points = 0; } // new method
    const std::vector<Player>& getPlayers() const { return players; }
    friend std::ostream& operator<<(std::ostream& os, const Team& t);
};

#endif
