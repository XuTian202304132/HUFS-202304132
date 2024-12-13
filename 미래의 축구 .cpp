#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

struct Player {
    string name;
    int attack;
    int defense;
};

struct Team {
    string name;
    vector<Player> players;

    int getTeamAttack(int count = 11) const {
        int num = (int)players.size() < count ? (int)players.size() : count;
        if (num == 0) return 0;
        int totalAttack = 0;
        for (int i = 0; i < num; i++) {
            totalAttack += players[i].attack;
        }
        return totalAttack / num;
    }

    int getTeamDefense(int count = 11) const {
        int num = (int)players.size() < count ? (int)players.size() : count;
        if (num == 0) return 0;
        int totalDefense = 0;
        for (int i = 0; i < num; i++) {
            totalDefense += players[i].defense;
        }
        return totalDefense / num;
    }
};

struct MatchResult {
    string date;
    string team1;
    string team2;
    int score1;
    int score2;
};

struct League {
    vector<Team> teams;
    vector<MatchResult> results;
};

const string TEAM_LIST_FILE = "teams.txt";
const string RESULT_FILE = "results.txt";

// Load teams and their players
vector<Team> loadTeamsAndPlayers(const string& teamListFile) {
    vector<Team> teams;
    ifstream fin(teamListFile);
    if (!fin.is_open()) {
        cerr << "Failed to open " << teamListFile << endl;
        return teams;
    }
    string teamName;
    while (fin >> teamName) {
        Team t;
        t.name = teamName;
        string playerFile = "players_" + teamName + ".txt";
        ifstream pfin(playerFile);
        if (!pfin.is_open()) {
            cerr << "Warning: Could not open " << playerFile << " for team " << teamName << endl;
        }
        else {
            Player pl;
            while (pfin >> pl.name >> pl.attack >> pl.defense) {
                t.players.push_back(pl);
            }
            pfin.close();
        }
        teams.push_back(t);
    }
    fin.close();
    return teams;
}

string getCurrentDate() {
    // Simple fixed date for demonstration
    return "2024-12-13";
}

MatchResult simulateMatch(const Team& t1, const Team& t2) {
    int t1Attack = t1.getTeamAttack();
    int t1Defense = t1.getTeamDefense();
    int t2Attack = t2.getTeamAttack();
    int t2Defense = t2.getTeamDefense();

    int maxScore1 = max(0, t1Attack / 10 - t2Defense / 20);
    int maxScore2 = max(0, t2Attack / 10 - t1Defense / 20);

    int score1 = rand() % (maxScore1 + 1);
    int score2 = rand() % (maxScore2 + 1);

    MatchResult mr;
    mr.date = getCurrentDate();
    mr.team1 = t1.name;
    mr.team2 = t2.name;
    mr.score1 = score1;
    mr.score2 = score2;
    return mr;
}

void saveResult(const MatchResult& mr) {
    ofstream fout(RESULT_FILE, ios::app);
    if (!fout.is_open()) {
        cerr << "Failed to open " << RESULT_FILE << " for writing." << endl;
        return;
    }
    fout << mr.date << " " << mr.team1 << " " << mr.team2 << " " << mr.score1 << " " << mr.score2 << "\n";
    fout.close();
}

void showTeams(const vector<Team>& teams) {
    cout << "Teams List:" << endl;
    for (size_t i = 0; i < teams.size(); i++) {
        cout << i + 1 << ". " << teams[i].name << endl;
    }
}

void showTeamPlayers(const vector<Team>& teams) {
    if (teams.empty()) {
        cout << "No teams loaded." << endl;
        return;
    }
    showTeams(teams);
    cout << "Select a team number to view its players: ";
    int idx;
    cin >> idx;
    if (idx < 1 || (size_t)idx > teams.size()) {
        cout << "Invalid choice." << endl;
        return;
    }
    const Team& t = teams[idx - 1];
    cout << "Players of " << t.name << ":" << endl;
    if (t.players.empty()) {
        cout << "No players found for this team." << endl;
        return;
    }
    for (auto& p : t.players) {
        cout << p.name << " (Attack: " << p.attack << ", Defense: " << p.defense << ")" << endl;
    }
}

MatchResult simulateSingleMatch(vector<Team>& teams) {
    if (teams.size() < 2) {
        cout << "Not enough teams to simulate a match." << endl;
        return {};
    }
    showTeams(teams);
    cout << "Select the first team number: ";
    int t1Index, t2Index;
    cin >> t1Index;
    cout << "Select the second team number: ";
    cin >> t2Index;

    if (t1Index < 1 || (size_t)t1Index > teams.size() ||
        t2Index < 1 || (size_t)t2Index > teams.size() || t1Index == t2Index) {
        cout << "Invalid selection." << endl;
        return {};
    }

    Team t1 = teams[t1Index - 1];
    Team t2 = teams[t2Index - 1];
    MatchResult mr = simulateMatch(t1, t2);
    cout << "Match Date: " << mr.date << endl;
    cout << mr.team1 << " vs " << mr.team2 << " : " << mr.score1 << "-" << mr.score2 << endl;
    saveResult(mr);
    return mr;
}

void simulateLeague(League& league) {
    // Round-robin: each pair of teams plays once
    if (league.teams.size() < 2) {
        cout << "Not enough teams to simulate a league." << endl;
        return;
    }

    for (size_t i = 0; i < league.teams.size(); i++) {
        for (size_t j = i + 1; j < league.teams.size(); j++) {
            MatchResult mr = simulateMatch(league.teams[i], league.teams[j]);
            league.results.push_back(mr);
            saveResult(mr);
        }
    }
    cout << "League simulation completed. All results are saved." << endl;
}

void printLeagueTable(const League& league) {
    if (league.teams.empty()) {
        cout << "No teams loaded." << endl;
        return;
    }

    struct TableEntry {
        string teamName;
        int points;
        int scored;
        int conceded;
    };

    vector<TableEntry> table;
    for (auto& t : league.teams) {
        TableEntry te;
        te.teamName = t.name;
        te.points = 0;
        te.scored = 0;
        te.conceded = 0;
        table.push_back(te);
    }

    auto findTeamInTable = [&](const string& name) {
        return find_if(table.begin(), table.end(), [&](const TableEntry& e) { return e.teamName == name; });
        };

    for (auto& r : league.results) {
        auto it1 = findTeamInTable(r.team1);
        auto it2 = findTeamInTable(r.team2);
        it1->scored += r.score1;
        it1->conceded += r.score2;
        it2->scored += r.score2;
        it2->conceded += r.score1;

        if (r.score1 > r.score2) {
            it1->points += 3;
        }
        else if (r.score1 < r.score2) {
            it2->points += 3;
        }
        else {
            it1->points += 1;
            it2->points += 1;
        }
    }

    sort(table.begin(), table.end(), [](const TableEntry& a, const TableEntry& b) {
        if (a.points != b.points) return a.points > b.points;
        int gdA = a.scored - a.conceded;
        int gdB = b.scored - b.conceded;
        return gdA > gdB;
        });

    cout << "League Table:" << endl;
    cout << "Pos | Team         | Points | Scored | Conceded" << endl;
    cout << "---------------------------------------------" << endl;
    for (size_t i = 0; i < table.size(); i++) {
        cout << (i + 1) << "   | " << table[i].teamName
            << " | " << table[i].points
            << "      | " << table[i].scored
            << "      | " << table[i].conceded << endl;
    }
}

int main() {
    srand((unsigned)time(NULL));
    vector<Team> teams = loadTeamsAndPlayers(TEAM_LIST_FILE);
    League league;
    league.teams = teams;

    // Load previously saved results (optional)
    // If we want to incorporate past results:
    // Not implemented here for simplicity, but could be done similarly to load data and push into league.results.

    while (true) {
        cout << "\n======= Future Football Program Menu =======" << endl;
        cout << "1. Show team list" << endl;
        cout << "2. Show team players" << endl;
        cout << "3. Simulate a single match" << endl;
        cout << "4. Simulate a league" << endl;
        cout << "5. Print league table" << endl;
        cout << "6. Exit" << endl;
        cout << "Select an option: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            showTeams(league.teams);
        }
        else if (choice == 2) {
            showTeamPlayers(league.teams);
        }
        else if (choice == 3) {
            {
                MatchResult mr = simulateSingleMatch(league.teams);
                if (!mr.team1.empty()) league.results.push_back(mr);
            }
        }
        else if (choice == 4) {
            simulateLeague(league);
        }
        else if (choice == 5) {
            printLeagueTable(league);
        }
        else if (choice == 6) {
            cout << "Exiting program." << endl;
            break;
        }
        else {
            cout << "Invalid selection. Please try again." << endl;
        }
    }

    return 0;
}
