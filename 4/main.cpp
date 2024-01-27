#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int getWin(vector<int> first, vector<int> second) {
    int f_i = 0, s_i = 0;
    int win = 1;
    while (f_i < first.size() && s_i < second.size()) {
        if (first[f_i] == second[s_i]) {
            win <<= 1;
            f_i++;
            s_i++;
        }
        else if (first[f_i] < second[s_i]) f_i++;
        else if (first[f_i] > second[s_i]) s_i++;
    }

    return win >> 1;
}

int main () {
    ifstream fin;
    fin.open("test.in");

    string s;
    bool game;
    bool first;
    vector<int> first_cards,second_cards;
    int answer = 0;
    while (fin >> s) {
        if (s == "Card") {
            game = false;
            first = true;
            sort(first_cards.begin(), first_cards.end());
            sort(second_cards.begin(), second_cards.end());
            answer += getWin(first_cards, second_cards);
            first_cards.erase(first_cards.begin(), first_cards.end());
            second_cards.erase(second_cards.begin(), second_cards.end());
            continue;
        }
        if (s[s.length() - 1] == ':') {
            game = true;
            continue;
        }
        if (s == "|") {
            first = false;
            continue;
        }
        if (first) first_cards.push_back(stoi(s));
        else second_cards.push_back(stoi(s));
    }
    cout << answer << endl;
    return 0;
}
