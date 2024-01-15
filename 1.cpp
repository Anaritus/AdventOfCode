#include <array>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool assert_digit (char s) {
    int si = s - '0';
    return si < 10 && si > 0;
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
    if (assert_digit(s[start_i])) return s[start_i] - '0';
    Node current = root;
    for (int i = start_i; i < s.length(); i++) {
        char a = s[i];
        if (current.number) return current.number;
        if (assert_digit(a) || !current.next[a - 'a']) return 0;
        current = *current.next[a - 'a'];
    }
    return current.number;
}

int main() {
    ifstream fin;
    fin.open("1.in");

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
        for (int i = 0; i < s.length(); i++) {
            char t = s[i];
            int number = get(root, s, i);
            if (number) {
                if (flag) {
                    flag = false;
                    first = number;
                }
                last = number;
            }
        }
        answer += 10 * first + last;
    }
    cout << answer << endl;
}
