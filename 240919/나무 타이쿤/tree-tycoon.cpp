#include <iostream>
#include <vector>
#include <utility>
using namespace std;

const int MAX_N = 15;
const int MAX_M = 100;

int n, m;
int Board[MAX_N][MAX_N];
bool tonicBoard[MAX_N][MAX_N];
pair<int,int> moveInfo[MAX_M];

const int dx[8] = {0,-1,-1,-1,0,1,1,1};
const int dy[8] = {1,1,0,-1,-1,-1,0,1};

const int dxMore[4] = {-1,-1,1,1};
const int dyMore[4] = {1,-1,1,-1};

void Input() {
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> Board[i][j];
            tonicBoard[i][j] = false;
        }
    }
    tonicBoard[n-2][0] = tonicBoard[n-2][1] = tonicBoard[n-1][0] = tonicBoard[n-1][1] = true;

    for(int i = 0; i < m; i++) cin >> moveInfo[i].first >> moveInfo[i].second;
}

void moveTonic(int year) {
    int d = moveInfo[year].first - 1;
    int p = moveInfo[year].second;

    vector<pair<int, int>> newPositions;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(tonicBoard[i][j]) {
                int nx = (i + dx[d] * p % n + n) % n;
                int ny = (j + dy[d] * p % n + n) % n;
                newPositions.emplace_back(nx, ny);
                tonicBoard[i][j] = false;
            }
        }
    }
    for(const auto &pos : newPositions) {
        tonicBoard[pos.first][pos.second] = true;
    }
}

void applyTonic() {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(tonicBoard[i][j]) {
                Board[i][j]++;
                int moreGrow = 0;
                for(int z = 0; z < 4; z++) {
                    int nx = i + dxMore[z], ny = j + dyMore[z];
                    if(nx >= 0 && nx < n && ny >= 0 && ny < n && Board[nx][ny] >= 1) moreGrow++;
                }
                Board[i][j] += moreGrow;
            }
        }
    }
}

void buyTonic() {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(!tonicBoard[i][j] && Board[i][j] >= 2) {
                Board[i][j] -= 2;
                tonicBoard[i][j] = true;
            }
        }
    }
}

int Solve() {
    for(int i = 0; i < m; i++) {
        moveTonic(i);
        applyTonic();
        buyTonic();
    }
    int result = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            result += Board[i][j];
        }
    }
    return result;
}

int main() {
    Input();
    cout << Solve() << endl;
    return 0;
}