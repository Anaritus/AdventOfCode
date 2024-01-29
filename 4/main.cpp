#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int getWin(vector<int> first, vector<int> second) {
    int f_i = 0, s_i = 0;
    int win = 0;
    sort(first.begin(), first.end());
    sort(second.begin(), second.end());
    while (f_i < first.size() && s_i < second.size()) {
        if (first[f_i] == second[s_i]) {
            win++;
            f_i++;
            s_i++;
        }
        else if (first[f_i] < second[s_i]) f_i++;
        else if (first[f_i] > second[s_i]) s_i++;
    }

    return win;
}

void initNewCard(bool & game, bool & first) {
    game = false;
    first = true;
}

void processCopies(
        vector<int> & copies, int & card_number,
        vector<int> & first, vector<int> & second) {
    int win = getWin(first, second);

    while (copies.size() < card_number + win + 1) {
        copies.push_back(1);
    }
    for (int i = card_number + 1; i < win + card_number + 1; i++) {
        copies[i] += copies[card_number];
    }

    card_number++;
    first.erase(first.begin(), first.end());
    second.erase(second.begin(), second.end());
}

int sum(vector<int> v) {
    int s = 0;
    for (auto t: v) {
        s += t;
    }
    return s;
}

void debug_out(vector<int> copies) {
    for (auto t: copies) {
        cout << t << " ";
    }
    cout << endl;
}

int main () {
    ifstream fin;
    fin.open("test.in");

    string s;
    bool game;
    bool first;
    vector<int> first_cards,second_cards; // Карты для сравнения
    vector<int> copies(1, 0); // Копии карточек
    int card_number = 0;
    while (fin >> s) {
        if (s == "Card") {
            initNewCard(game, first);
            processCopies(copies, card_number, first_cards, second_cards);
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
    processCopies(copies, card_number, first_cards, second_cards);
    cout << sum(copies) << endl;
    return 0;
}
