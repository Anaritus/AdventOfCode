#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool assert_digit (char s) {
    int si = s - '0';
    return si < 10 && si >= 0;
}

int main() {
    ifstream fin;
    fin.open("1.in");

    string s;
    int answer;
    while (fin >> s) {
        int first, last;
        bool flag = true;
        for (auto t: s) {
            if (!assert_digit(t)) {
                continue;
            }
            if (first) {
                first = t - '0';
                flag = false;
            }
            last = t - '0';
        }
        answer += 10 * first + last;
    }
    cout << answer << endl;
}
