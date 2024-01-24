#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool assertNumber(char t) {
    return '0' <= t && t <= '9';
}

struct gear {
    int ratios = 1; // ratios
    int counts = 0; // number of ratios
};

bool assertGear(char t) {
    return t == '*';
}

int numberFromPoint(int start, string s) {
    if (!assertNumber(s[start])) throw runtime_error("start index is not a number!");

    int current = start;
    while (current < s.length() && assertNumber(s[current])) {
        current++;
    }

    return current - 1;
}

void getNumber(
        int le,
        int ri,
        int pos,
        vector<string> schematic,
        vector<vector<gear>> *gears) {
    int hope = stoi(
        schematic[pos].substr(le, ri - le + 1)
    );

    for (
            int i = pos - (pos > 0);
            i <= pos + (pos < schematic.size() - 1);
            i++) {
        for (
                int j = le - (le > 0);
                j <= ri + (ri < schematic[i].length() - 1);
                j++) {
            if (assertGear(schematic[i][j])) {
                (*gears)[i][j].ratios *= hope;
                (*gears)[i][j].counts += 1;
            }
        }
    }
}


int main() {
    ifstream fin;
    fin.open("test.in");

    vector<string> schematic;
    string s;
    vector<vector<gear>> gears;
    while (fin >> s) {
        schematic.push_back(s);
        vector<gear> zeroes(s.length());
        gears.push_back(zeroes);
    }

    for (int pos = 0; pos < schematic.size(); pos++) {
        s = schematic[pos];

        int i = 0;
        while (i < s.length()) {
            if (!assertNumber(s[i])) {
                i++;
                continue;
            }

            int end = numberFromPoint(i, s);
            getNumber(i, end, pos, schematic, &gears);
            i = end + 1;
        }
    }

    int answer = 0;
    for (auto row: gears) {
        for (auto gear: row) {
            if (gear.counts == 2) {
                answer += gear.ratios;
            }
        }
    }
    cout << answer << endl;
}
