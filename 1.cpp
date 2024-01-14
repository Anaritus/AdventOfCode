#include <__errc>
#include <array>
#include <ios>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool assert_digit (char s) {
    int si = s - '0';
    return si < 10 && si >= 0;
}

struct Node{
    int number = 0;
    array<Node *, 26> next;
};

void fill(Node *root, string s, int number) {
    Node* current = root;
    for (auto a: s) {
        if (!current->next[a - 'a']) current->next[a - 'a'] = new Node;
        current = current->next[a - 'a'];
    }
    current->number = number;
}

int get(Node root, string s, int start_i) {
    Node current = root;
    for (int i = start_i; i < s.length(); i++) {
        char a = s[i];
        if (current.number) return current.number;
        if (!current.next[a - 'a']) return 0;
        current = *current.next[a - 'a'];
    }
    return 0;
}

int main() {
    ifstream fin;
    fin.open("test.in");

    Node root;
    string numbers[9] = {
        "one",
        "two",
        "three",
        "four",
        "five",
        "six",
        "seven",
        "eight",
        "nine"
    };
    for (int i = 0; i < 9; i++) {
        fill(&root, numbers[i], i + 1);
    }

    string s;
    int answer;
    while (fin >> s) {
        int first, last;
        bool flag = true;
        int i = 0;
        for (int i = 0; i < s.length(); i++) {
            char t = s[i];
            cout << i;
            if (assert_digit(t) || get(root, s, i)) {
                if (flag) {
                    flag = false;
                    first = assert_digit(t) ? t - '0' : get(root, s, i);
                }
                last = assert_digit(t) ? t - '0' : get(root, s, i);
            }
        }
        cout << endl << first << last << endl;
        answer += 10 * first + last;
    }
    cout << answer << endl;
}
