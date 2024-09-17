#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;

int L, N, Q;
vector<vector<int>> Board;
unordered_map<int, vector<int>> sirs;
unordered_map<int, int> damage;
vector<pair<int, int>> order;

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

// 한글 주석: 기사의 좌표를 얻는 함수
void get_xy(const vector<int>& arr, vector<pair<int, int>>& temp) {
    int r = arr[0], c = arr[1], h = arr[2], w = arr[3];
    for (int x = r; x < r + h; ++x) {
        for (int y = c; y < c + w; ++y) {
            temp.push_back({x, y});
        }
    }
}

// 한글 주석: 체스판 내부인지 확인하는 함수
bool is_board(int x, int y) {
    return 0 <= x && x < L && 0 <= y && y < L;
}

// 한글 주석: 기사 이동 함수
unordered_set<int> move_sirs(int i, int d) {
    // 한글 주석: 체스판에서 삭제된 기사 이동 명령
    if (sirs.find(i) == sirs.end()) return {};

    unordered_map<int, vector<pair<int, int>>> states;
    for (const auto& kv : sirs) {
        vector<pair<int, int>> temp;
        get_xy(kv.second, temp);
        states[kv.first] = temp;
    }

    queue<pair<int, int>> q;
    unordered_set<int> moved_sir;
    get_xy(sirs[i], vector<pair<int, int>>(q));
    moved_sir.insert(i);

    while (!q.empty()) {
        int x = q.front().first, y = q.front().second;
        q.pop();
        int nx = x + dx[d], ny = y + dy[d];

        if (!is_board(nx, ny)) return {};

        for (const auto& kv : states) {
            if (find(kv.second.begin(), kv.second.end(), make_pair(nx, ny)) != kv.second.end() &&
                moved_sir.find(kv.first) == moved_sir.end()) {
                moved_sir.insert(kv.first);
                get_xy(sirs[kv.first], vector<pair<int, int>>(q));
            }
        }

        if (Board[nx][ny] == 2) return {};
    }

    for (int idx : moved_sir) {
        sirs[idx][0] += dx[d];
        sirs[idx][1] += dy[d];
    }

    return moved_sir;
}

// 한글 주석: 데미지 계산 함수
void get_damage(const unordered_set<int>& moved_sir, int id) {
    if (moved_sir.empty()) return;

    unordered_map<int, vector<pair<int, int>>> states;
    for (int idx : moved_sir) {
        vector<pair<int, int>> temp;
        get_xy(sirs[idx], temp);
        states[idx] = temp;
    }

    for (const auto& kv : states) {
        int cnt = 0;
        for (const auto& pos : kv.second) {
            if (Board[pos.first][pos.second] == 1) ++cnt;
        }

        if (cnt >= sirs[kv.first][4]) {
            damage[kv.first] = 0;
            sirs.erase(kv.first);
        } else {
            sirs[kv.first][4] -= cnt;
            damage[kv.first] += cnt;
        }
    }
}

int main() {
    cin >> L >> N >> Q;
    Board.resize(L, vector<int>(L));
    for (int i = 0; i < L; ++i) {
        for (int j = 0; j < L; ++j) {
            cin >> Board[i][j];
        }
    }

    for (int i = 1; i <= N; ++i) {
        int r, c, h, w, k;
        cin >> r >> c >> h >> w >> k;
        sirs[i] = {r-1, c-1, h, w, k};
        damage[i] = 0;
    }

    for (int i = 0; i < Q; ++i) {
        int knight, direction;
        cin >> knight >> direction;
        order.push_back({knight, direction-1});
    }

    for (const auto& cmd : order) {
        unordered_set<int> moved_sir = move_sirs(cmd.first, cmd.second);
        if (!moved_sir.empty()) {
            moved_sir.erase(cmd.first);
            get_damage(moved_sir, cmd.first);
        }
    }

    int total_damage = 0;
    for (const auto& kv : damage) {
        total_damage += kv.second;
    }
    cout << total_damage << endl;

    return 0;
}