#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
#include <climits>

using namespace std;

// 게임 관련 전역 변수들
int N, M, P, C, D;
int rx, ry; // 루돌프 위치
vector<vector<int>> map; // 게임 보드: 0(빈 칸), 양수(산타 번호), -1(루돌프)

// 산타 클래스 정의
class Santa {
public:
    int x, y;
    Santa(int x = 0, int y = 0) : x(x), y(y) {}
};

vector<Santa> santa;
vector<int> stun; // 산타의 기절 상태
vector<bool> dead; // 산타의 탈락 상태
vector<int> score; // 산타의 점수

// 루돌프와 산타의 이동 벡터 (상우하좌 순서)
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

// 두 점 사이의 거리 계산 함수
int calDistance(int r1, int c1, int r2, int c2) {
    return (r1-r2)*(r1-r2) + (c1-c2)*(c1-c2);
}

// 게임 보드 출력 함수 (디버깅용)
void printBoard() {
    cout << "보드 : \n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << map[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

// 범위 체크 함수
bool isRange(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < N;
}

// 루돌프 이동 함수
void moveRudolph() {
    int minDist = INT_MAX;
    int targetX = -1, targetY = -1, targetId = -1;

    // 가장 가까운 산타 찾기
    for (int i = 1; i <= P; i++) {
        if (dead[i]) continue;
        int dist = calDistance(rx, ry, santa[i].x, santa[i].y);
        if (dist < minDist || (dist == minDist && santa[i].x > targetX) ||
            (dist == minDist && santa[i].x == targetX && santa[i].y > targetY)) {
            minDist = dist;
            targetX = santa[i].x;
            targetY = santa[i].y;
            targetId = i;
        }
    }

    // 루돌프 이동 방향 결정
    int moveX = (targetX > rx) ? 1 : (targetX < rx) ? -1 : 0;
    int moveY = (targetY > ry) ? 1 : (targetY < ry) ? -1 : 0;

    map[rx][ry] = 0;
    rx += moveX;
    ry += moveY;

    // 충돌 처리
    if (rx == targetX && ry == targetY) {
        stun[targetId] = 2;
        score[targetId] += C;

        int nx = targetX + moveX * C;
        int ny = targetY + moveY * C;

        // 연쇄 충돌 처리
        queue<pair<int, pair<int, int>>> q;
        q.push({targetId, {nx, ny}});

        while (!q.empty()) {
            int currId = q.front().first;
            int currX = q.front().second.first;
            int currY = q.front().second.second;
            q.pop();

            if (!isRange(currX, currY)) {
                dead[currId] = true;
                map[santa[currId].x][santa[currId].y] = 0;
            } else if (map[currX][currY] > 0) {
                q.push({map[currX][currY], {currX + moveX, currY + moveY}});
                santa[currId].x = currX;
                santa[currId].y = currY;
                map[currX][currY] = currId;
            } else {
                santa[currId].x = currX;
                santa[currId].y = currY;
                map[currX][currY] = currId;
            }
        }
    }

    map[rx][ry] = -1;
}

// 산타 이동 함수
void moveSanta() {
    for (int i = 1; i <= P; i++) {
        if (dead[i] || stun[i] > 0) continue;

        int minDist = calDistance(santa[i].x, santa[i].y, rx, ry);
        int moveDir = -1;

        for (int d = 0; d < 4; d++) {
            int nx = santa[i].x + dx[d];
            int ny = santa[i].y + dy[d];

            if (!isRange(nx, ny) || map[nx][ny] > 0) continue;

            int dist = calDistance(nx, ny, rx, ry);
            if (dist < minDist) {
                minDist = dist;
                moveDir = d;
            }
        }

        if (moveDir != -1) {
            int nx = santa[i].x + dx[moveDir];
            int ny = santa[i].y + dy[moveDir];

            if (nx == rx && ny == ry) { // 루돌프와 충돌
                stun[i] = 2;
                score[i] += D;

                int moveX = -dx[moveDir];
                int moveY = -dy[moveDir];
                int nx = rx + moveX * D;
                int ny = ry + moveY * D;

                // 연쇄 충돌 처리
                queue<pair<int, pair<int, int>>> q;
                q.push({i, {nx, ny}});

                while (!q.empty()) {
                    int currId = q.front().first;
                    int currX = q.front().second.first;
                    int currY = q.front().second.second;
                    q.pop();

                    if (!isRange(currX, currY)) {
                        dead[currId] = true;
                        map[santa[currId].x][santa[currId].y] = 0;
                    } else if (map[currX][currY] > 0) {
                        q.push({map[currX][currY], {currX + moveX, currY + moveY}});
                        santa[currId].x = currX;
                        santa[currId].y = currY;
                        map[currX][currY] = currId;
                    } else {
                        santa[currId].x = currX;
                        santa[currId].y = currY;
                        map[currX][currY] = currId;
                    }
                }
            } else { // 일반 이동
                map[santa[i].x][santa[i].y] = 0;
                santa[i].x = nx;
                santa[i].y = ny;
                map[nx][ny] = i;
            }
        }
    }
}

// 게임 실행 함수
void runGame() {
    for (int turn = 1; turn <= M; turn++) {
        moveRudolph();
        moveSanta();

        // 살아있는 산타 점수 증가
        for (int i = 1; i <= P; i++) {
            if (!dead[i]) score[i]++;
        }

        // 기절 턴 감소
        for (int i = 1; i <= P; i++) {
            if (stun[i] > 0) stun[i]--;
        }

        // 모든 산타가 탈락했는지 확인
        bool allDead = true;
        for (int i = 1; i <= P; i++) {
            if (!dead[i]) {
                allDead = false;
                break;
            }
        }
        if (allDead) break;
    }

    // 최종 점수 출력
    for (int i = 1; i <= P; i++) {
        cout << score[i] << " ";
    }
    cout << "\n";
}

int main() {
    cin >> N >> M >> P >> C >> D;
    cin >> rx >> ry;
    rx--; ry--; // 0-based 인덱스로 변환

    map.resize(N, vector<int>(N, 0));
    santa.resize(P + 1);
    stun.resize(P + 1, 0);
    dead.resize(P + 1, false);
    score.resize(P + 1, 0);

    map[rx][ry] = -1;

    for (int i = 0; i < P; i++) {
        int num, x, y;
        cin >> num >> x >> y;
        x--; y--; // 0-based 인덱스로 변환
        santa[num] = Santa(x, y);
        map[x][y] = num;
    }

    runGame();

    return 0;
}