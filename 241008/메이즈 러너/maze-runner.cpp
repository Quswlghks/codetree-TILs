#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n, m, k;
int Map[10][10];

int x_exit, y_exit;

int dx[4] = {-1, 1, 0, 0}; // 상하좌우
int dy[4] = {0, 0, -1, 1};

int totalMove = 0;

// 참가자의 위치를 저장하는 벡터
vector<pair<int, int>> participants;

void Input() {
    cin >> n >> m >> k;
    // 맵 입력
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> Map[i][j];
        }
    }
    // 참가자 위치 입력
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        participants.push_back({x, y});
    }
    // 출구 위치 입력
    cin >> x_exit >> y_exit;
    x_exit--;
    y_exit--;
    Map[x_exit][y_exit] = 10; // 출구를 10으로 표시
}

// 출구까지의 맨해튼 거리 계산
int calDist(int x1, int y1) {
    return abs(x1 - x_exit) + abs(y1 - y_exit);
}

// 모든 참가자가 탈출했는지 확인
bool isExitAll() {
    return participants.empty();
}

void move() {
    vector<pair<int, int>> newParticipants; // 이동 후 참가자들의 위치를 저장할 벡터
    for (auto &p : participants) {
        int x = p.first;
        int y = p.second;
        int minDist = calDist(x, y);
        int bestDir = -1;
        // 이동 가능한 칸 중에서 출구에 가까워지는 칸 찾기
        for (int dir = 0; dir < 4; dir++) {
            int tx = x + dx[dir];
            int ty = y + dy[dir];
            // 맵 범위를 벗어나거나 벽이면 패스
            if (tx < 0 || ty < 0 || tx >= n || ty >= n)
                continue;
            if (Map[tx][ty] >= 1 && Map[tx][ty] <= 9)
                continue; // 벽인 경우 이동 불가
            int dist = calDist(tx, ty);
            if (dist < minDist) {
                minDist = dist;
                bestDir = dir;
            } else if (dist == minDist) {
                // 수직 방향 우선
                if (dx[dir] != 0 && (bestDir == -1 || dx[bestDir] == 0)) {
                    bestDir = dir;
                }
            }
        }
        if (bestDir != -1) {
            // 이동할 수 있는 경우
            int tx = x + dx[bestDir];
            int ty = y + dy[bestDir];
            totalMove++; // 이동 거리 증가
            if (Map[tx][ty] == 10) {
                // 출구에 도달하면 참가자 제거 (newParticipants에 추가하지 않음)
                continue;
            } else {
                newParticipants.push_back({tx, ty});
            }
        } else {
            // 이동할 수 없는 경우 제자리
            newParticipants.push_back({x, y});
        }
    }
    participants = newParticipants; // 참가자 위치 업데이트
}

void rotate() {
    // 가장 작은 정사각형 찾기
    int minSize = n + 1;
    int sx = -1, sy = -1;
    for (int size = 2; size <= n; size++) { // 최소 크기 2부터 시작
        bool found = false;
        for (int i = 0; i <= n - size; i++) {
            for (int j = 0; j <= n - size; j++) {
                bool hasExit = false;
                bool hasParticipant = false;
                // 사각형 내부에 출구와 참가자가 있는지 확인
                if (x_exit >= i && x_exit < i + size && y_exit >= j && y_exit < j + size)
                    hasExit = true;
                for (auto &p : participants) {
                    int px = p.first;
                    int py = p.second;
                    if (px >= i && px < i + size && py >= j && py < j + size) {
                        hasParticipant = true;
                        break;
                    }
                }
                if (hasExit && hasParticipant) {
                    // 조건을 만족하는 가장 작은 사각형 갱신
                    if (size < minSize || (size == minSize && (i < sx || (i == sx && j < sy)))) {
                        minSize = size;
                        sx = i;
                        sy = j;
                    }
                    found = true;
                }
            }
        }
        if (found)
            break; // 가장 작은 크기를 찾았으므로 종료
    }

    // 회전 수행
    int size = minSize;
    int temp[10][10];
    // 회전된 결과를 임시 맵에 저장
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int srcX = sx + i;
            int srcY = sy + j;
            int destX = sx + j;
            int destY = sy + size - 1 - i;
            temp[destX][destY] = Map[srcX][srcY];
            // 벽의 내구도 감소
            if (temp[destX][destY] >= 1 && temp[destX][destY] <= 9)
                temp[destX][destY] = max(0, temp[destX][destY] - 1);
        }
    }
    // 회전된 결과를 맵에 반영
    for (int i = sx; i < sx + size; i++) {
        for (int j = sy; j < sy + size; j++) {
            Map[i][j] = temp[i][j];
        }
    }

    // 참가자 위치 업데이트 (회전된 위치로)
    for (auto &p : participants) {
        int x = p.first;
        int y = p.second;
        if (x >= sx && x < sx + size && y >= sy && y < sy + size) {
            int nx = sx + (y - sy);
            int ny = sy + size - 1 - (x - sx);
            p.first = nx;
            p.second = ny;
        }
    }

    // 출구 위치 업데이트
    if (x_exit >= sx && x_exit < sx + size && y_exit >= sy && y_exit < sy + size) {
        int nx = sx + (y_exit - sy);
        int ny = sy + size - 1 - (x_exit - sx);
        x_exit = nx;
        y_exit = ny;
    }
}

void Solve() {
    for (int time = 0; time < k; time++) {
        move(); // 참가자 이동
        if (isExitAll())
            break; // 모든 참가자가 탈출하면 종료
        rotate(); // 미로 회전
    }
    cout << totalMove << "\n"; // 참가자들의 이동 거리 합 출력
    cout << x_exit + 1 << " " << y_exit + 1 << "\n"; // 출구 좌표 출력
}

int main() {
    Input();
    Solve();
    return 0;
}