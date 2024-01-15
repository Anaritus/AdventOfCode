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
    int color_number = 0;
    map<char, int> colors = {
        {'r', 0},
        {'g', 0},
        {'b', 0}
    };
    int last_number;
    int total_power = 0;
    while (fin >> s) {
        if (s == "Game") {
            last_number = 0;
            total_power += colors['r'] * colors['b'] * colors['g'];
            colors = {
                {'r', 0},
                {'g', 0},
                {'b', 0}
            };
            continue;
        }
        if (s[s.size() - 1] == ':') continue;
        if (colors.find(s[0]) == colors.end()) {
            last_number = stoi(s);
        } else if (last_number > colors[s[0]]){
            colors[s[0]] = last_number;
        }
    }
    total_power += colors['r'] * colors['b'] * colors['g'];
    cout << total_power << endl;
}
