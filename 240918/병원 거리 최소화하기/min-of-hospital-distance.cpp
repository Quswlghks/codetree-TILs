#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

const int MAX_N = 50;
const int MAX_M = 13;

int n, m;
vector<pair<int, int>> hospitals, people;
int dist[MAX_N * MAX_N][MAX_M];
int result = INT_MAX;

void input() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x;
            cin >> x;
            if (x == 1) people.push_back({i, j});
            else if (x == 2) hospitals.push_back({i, j});
        }
    }
}

int manhattan_distance(pair<int, int> a, pair<int, int> b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

void precalculate_distances() {
    for (int i = 0; i < people.size(); i++) {
        for (int j = 0; j < hospitals.size(); j++) {
            dist[i][j] = manhattan_distance(people[i], hospitals[j]);
        }
    }
}

void solve(int idx, int count, vector<int>& selected) {
    if (count == m) {
        int total_dist = 0;
        for (int i = 0; i < people.size(); i++) {
            int min_dist = INT_MAX;
            for (int j : selected) {
                min_dist = min(min_dist, dist[i][j]);
            }
            total_dist += min_dist;
        }
        result = min(result, total_dist);
        return;
    }
    
    if (idx >= hospitals.size()) return;
    
    // 현재 병원 선택
    selected.push_back(idx);
    solve(idx + 1, count + 1, selected);
    selected.pop_back();
    
    // 현재 병원 선택하지 않음
    solve(idx + 1, count, selected);
}

int main() {
    input();
    precalculate_distances();
    
    vector<int> selected;
    solve(0, 0, selected);
    
    cout << result << endl;
    return 0;
}