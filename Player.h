/* [주석 1 : 과제 설명]
   컴퓨터 프로그래밍 및 실습 평가과제 (배점 25점)
   학과 :컴퓨터공학부
   학번 :202304132
   이름 :서첨
   과제 주제 : 미래의 축구 - 9개 팀의 축구 리그 시뮬레이션
*/
#ifndef PLAYER_H
#define PLAYER_H

#include <string>

/* [Comment: Player class with offense (ATT) and defense (DEF) attributes.
   The sum of ATT and DEF represents the player's overall skill.
*/

class Player {
private:
    std::string name;
    int offense;
    int defense;
public:
    Player(const std::string& n, int off, int def) : name(n), offense(off), defense(def) {}
    int getOffense() const { return offense; }
    int getDefense() const { return defense; }
    std::string getName() const { return name; }
    int getTotalSkill() const { return offense + defense; }
};

#endif
