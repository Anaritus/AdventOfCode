#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

int main () {
    ifstream fin;
    fin.open("2.in");

    string s;
    int game = 0;
    int answer;
    int color_number = 0;
    map<char, int> checks = {
        {'r', 12},
        {'g', 13},
        {'b', 14}
    };
    bool adding = false;
    while (fin >> s) {
        if (s == "Game") {
            answer += adding ? game : 0;
            game++;
            adding = true;
            continue;
        }
        if (s[s.size() - 1] == ':') continue;
        if (checks.find(s[0]) == checks.end()) {
            color_number = stoi(s);
        }
        else if(checks[s[0]] < color_number) adding = false;
    }
    cout << answer << endl;
}
