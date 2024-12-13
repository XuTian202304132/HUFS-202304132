/* [주석 1 : 과제 설명]
   컴퓨터 프로그래밍 및 실습 평가과제 (배점 25점)
   학과 :컴퓨터공학부
   학번 :202304132
   이름 :서첨
   과제 주제 : 미래의 축구 - 9개 팀의 축구 리그 시뮬레이션
*/
#include "Team.h"
#include "Utility.h"

Team::Team(const std::string& name) : teamName(name), points(0) {
    int playerCount = 11;
    bool isPupil = (name == "TeamPupil");
    int minOffDef = isPupil ? 0 : 30;
    int maxOffDef = isPupil ? 9 : 99;

    RandomGenerator<int> rgOff(minOffDef, maxOffDef);
    RandomGenerator<int> rgDef(minOffDef, maxOffDef);

    for (int i = 0; i < playerCount; i++) {
        int off = rgOff.get();
        int def = rgDef.get();
        players.emplace_back(name + "_Player" + std::to_string(i), off, def);
    }
}

void Team::addPlayer(const Player& p) {
    players.push_back(p);
}

int Team::getTotalSkill() const {
    int sum = 0;
    for (auto& pl : players) {
        sum += pl.getTotalSkill();
    }
    return sum;
}

/* [- Offense as ATT
    - Defense as DEF
*/
std::ostream& operator<<(std::ostream& os, const Team& t) {
    os << "Team Name: " << t.teamName << "\n";
    os << "Points: " << t.points << "\n";
    os << "Total Skill: " << t.getTotalSkill() << "\n";
    os << "Players (ATT/DEF):\n";
    for (auto& pl : t.players) {
        os << "  " << pl.getName() << ": ATT=" << pl.getOffense() << ", DEF=" << pl.getDefense() << "\n";
    }
    return os;
}
