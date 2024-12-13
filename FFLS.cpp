/* [주석 1 : 과제 설명]
   컴퓨터 프로그래밍 및 실습 평가과제 (배점 25점)
   학과 :컴퓨터공학부
   학번 :202304132
   이름 :서첨
   과제 주제 : 미래의 축구 - 9개 팀의 축구 리그 시뮬레이션
*/

#include <iostream>
#include <string>
#include "League.h"
#include "Team.h"

/* [Comment:
   12.13 Use team numbers (1-9) instead of names.
   Teams are added in a fixed order:
   1: TeamFuture
   2: TeamRobot
   3: TeamAI
   4: TeamHUFS
   5: TeamAlien
   6: TeamClone
   7: TeamGoat
   8: TeamPupil
   9: TeamHuman
*/

int main() {
    League league;
    league.addTeam(new Team("TeamFuture"));
    league.addTeam(new Team("TeamRobot"));
    league.addTeam(new Team("TeamAI"));
    league.addTeam(new Team("TeamHUFS"));
    league.addTeam(new Team("TeamAlien"));
    league.addTeam(new Team("TeamClone"));
    league.addTeam(new Team("TeamGoat"));
    league.addTeam(new Team("TeamPupil"));
    league.addTeam(new Team("TeamHuman"));

    int choice = 0;
    do {
        std::cout << "\n=== FUTURE SOCCER LEAGUE MENU ===\n";
        std::cout << "1) Simulate entire league\n";
        std::cout << "2) Show standings & champion\n";
        std::cout << "3) Show team details (enter team number)\n";
        std::cout << "4) Simulate a 1v1 match between two teams (by team number)\n";
        std::cout << "5) Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        if (choice == 1) {
            league.simulateLeague();
            std::cout << "League simulation completed.\n";
        }
        else if (choice == 2) {
            league.showStandings();
        }
        else if (choice == 3) {
            std::cout << "Enter team number (1-" << league.getTeamCount() << "): ";
            int tnum;
            std::cin >> tnum;
            league.showTeam(tnum);
        }
        else if (choice == 4) {
            std::cout << "Enter first team number (1-" << league.getTeamCount() << "): ";
            int t1;
            std::cin >> t1;
            std::cout << "Enter second team number (1-" << league.getTeamCount() << "): ";
            int t2;
            std::cin >> t2;
            league.oneOnOneMatch(t1, t2);
        }
        else if (choice == 5) {
            std::cout << "Exiting...\n";
        }
        else {
            std::cout << "Invalid choice.\n";
        }
    } while (choice != 5);

    return 0;
}
