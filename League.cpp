/* [주석 1 : 과제 설명]
   컴퓨터 프로그래밍 및 실습 평가과제 (배점 25점)
   학과 :컴퓨터공학부
   학번 :202304132
   이름 :서첨
   과제 주제 : 미래의 축구 - 9개 팀의 축구 리그 시뮬레이션
*/
#include "League.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <random>

League::League() : simulated(false) {}

League::~League() {
    for (auto t : teams) {
        delete t;
    }
    teams.clear();
}

void League::addTeam(Team* t) {
    teams.push_back(t);
}

void League::resetAllPoints() {
    for (auto t : teams) {
        t->resetPoints();
    }
}

/* [Comment:
   simulateLeague():
   - All teams play each other once.
   - Determine winner by total skill + random factor.
   - Points: win=3, draw=1, loss=0
*/
void League::simulateLeague() {
    if (teams.size() < 2) {
        std::cout << "Not enough teams to simulate.\n";
        return;
    }

    // Reset points before simulation
    resetAllPoints();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 10);

    for (size_t i = 0; i < teams.size(); i++) {
        for (size_t j = i + 1; j < teams.size(); j++) {
            Team* A = teams[i];
            Team* B = teams[j];
            int skillA = A->getTotalSkill() + dist(gen);
            int skillB = B->getTotalSkill() + dist(gen);

            if (skillA > skillB) {
                A->addPoints(3);
            }
            else if (skillA < skillB) {
                B->addPoints(3);
            }
            else {
                A->addPoints(1);
                B->addPoints(1);
            }
        }
    }

    simulated = true;
}

void League::showStandings() const {
    if (!simulated) {
        std::cout << "League not simulated yet.\n";
        return;
    }

    std::vector<Team*> sortedTeams = teams;
    std::sort(sortedTeams.begin(), sortedTeams.end(), [](Team* a, Team* b) {
        if (a->getPoints() != b->getPoints())
            return a->getPoints() > b->getPoints();
        return a->getTotalSkill() > b->getTotalSkill();
        });

    std::cout << "Standings:\n";
    for (size_t i = 0; i < sortedTeams.size(); i++) {
        // Find original index to show team number
        // Since they are stored in a vector in order, we can find it:
        int originalIndex = -1;
        for (size_t k = 0; k < teams.size(); k++) {
            if (teams[k] == sortedTeams[i]) {
                originalIndex = (int)k;
                break;
            }
        }

        std::cout << (i + 1) << ". (No." << (originalIndex + 1) << ") "
            << sortedTeams[i]->getName()
            << " - Points: " << sortedTeams[i]->getPoints()
            << ", TotalSkill: " << sortedTeams[i]->getTotalSkill() << "\n";
    }

    std::cout << "Champion: " << sortedTeams.front()->getName() << "\n";
}

Team* League::getTeamByNumber(int number) const {
    if (number < 1 || number >(int)teams.size()) {
        return nullptr;
    }
    return teams[number - 1];
}

void League::showTeam(int teamNumber) const {
    Team* t = getTeamByNumber(teamNumber);
    if (!t) {
        std::cout << "Invalid team number.\n";
        return;
    }
    std::cout << "Team Number: " << teamNumber << "\n";
    std::cout << *t << "\n";
}

void League::oneOnOneMatch(int teamA, int teamB) const {
    Team* A = getTeamByNumber(teamA);
    Team* B = getTeamByNumber(teamB);

    if (!A || !B) {
        std::cout << "Invalid team number.\n";
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 10);

    int skillA = A->getTotalSkill() + dist(gen);
    int skillB = B->getTotalSkill() + dist(gen);

    std::cout << "1 vs 1 match: (No." << teamA << ") " << A->getName()
        << " vs (No." << teamB << ") " << B->getName() << "\n";
    std::cout << "Result: ";
    if (skillA > skillB) {
        std::cout << A->getName() << " wins.\n";
    }
    else if (skillA < skillB) {
        std::cout << B->getName() << " wins.\n";
    }
    else {
        std::cout << "Draw.\n";
    }
}