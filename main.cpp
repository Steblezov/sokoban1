#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h>
using namespace std;

int n, m;
vector<vector<char>> level(50, vector<char>(50));
vector<vector<char>> boxes(50, vector<char>(50));

int x;
int y;
fstream fs("map.txt");


void chtenie() {
    char ch;
    fs >> n;
    fs >> m;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            fs >> ch;
            switch (ch) {
            case 'n':
                level[i][j] = ' ';
                boxes[i][j] = 'n';
                break;
            case '#':
                level[i][j] = '#';
                boxes[i][j] = ' ';
                break;
            case '+':
                level[i][j] = '+';
                boxes[i][j] = ' ';
                break;
            case '.':
                level[i][j] = ' ';
                boxes[i][j] = ' ';
                break;
            case 'a':
                boxes[i][j] = ' ';
                level[i][j] = ' ';
                x = j;
                y = i;
                break;
            }
        }
        cout << endl;
    }
}

void redraw() {
    system("CLS");
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (x == j && y == i) {
                cout << 'a';
                continue;
            }
            if (boxes[i][j] == 'n') {
                cout << boxes[i][j];
            }
            else {
                cout << level[i][j];
            }
        }
        cout << endl;
    }
}
void move(char ch) {
    switch (ch) {
    case 'a':
        if (level[y][x] != '#') {
            if (boxes[y][x - 1] != 'n') {
                x--;
            }
            else {
                if (level[y][x - 2] != '#') {
                    boxes[y][x - 2] = 'n';
                    boxes[y][x - 1] = ' ';
                }
            }
        }
        break;
    case 'd':
        if (level[y][x + 1] != '#') {
            if (boxes[y][x + 1] != 'n') {
                x++;
            }
            else {
                if (level[y][x + 2] != '#') {
                    boxes[y][x + 2] = 'n';
                    boxes[y][x + 1] = ' ';
                }
            }
        }
        break;
    case 'w':
        if (level[y - 1][x] != '#') {
            if (boxes[y - 1][x] != 'n') {
                y--;
            }
            else {
                if (level[y - 2][x] != '#') {
                    boxes[y - 2][x] = 'n';
                    boxes[y - 1][x] = ' ';
                }
            }
        }
        break;
    case 's':
        if (level[y + 1][x] != '#') {
            if (boxes[y + 1][x] != 'n') {
                y++;
            }
            else {
                if (level[y + 2][x] != '#') {
                    boxes[y + 2][x] = 'n';
                    boxes[y + 1][x] = ' ';
                }
            }
        }
        break;
    }
}

int level_check() {
    int check = 1;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (boxes[i][j] == 'n' && level[i][j] != '+') {
                check = 0;
            }
        }
    }
    return check;
}

int main() {
    char ch;
    do {
        system("CLS");
        chtenie();
        redraw();
        ch = _getch();
        move(ch);
        if (level_check() == 1) {
            cout << "WIN" << endl;
        }

    } while (ch != 'q' && level_check() != 1);
    fs.close();
}