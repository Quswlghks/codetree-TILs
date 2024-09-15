#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// 상우하좌
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

int N, M, P, C, D;
int rx, ry; // 루돌프의 위치

vector<vector<int>> map; // 산타와 루돌프의 위치 저장 (산타 번호, 루돌프 -1)

struct Santa {
    int x, y;
    Santa(int x = 0, int y = 0) : x(x), y(y) {}
};

vector<Santa> santa;
vector<int> stun; // 산타가 기절했는지 확인
vector<bool> dead; // 산타가 죽었는지 확인
vector<int> score; // 산타가 얻은 점수 저장

struct Distance {
    int d, x, y;
    Distance(int d = 0, int x = 0, int y = 0) : d(d), x(x), y(y) {}
    bool operator<(const Distance& o) const {
        if (d != o.d) return d < o.d;
        if (x != o.x) return x > o.x;
        return y > o.y;
    }
};

bool isRange(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < N;
}

void moveRudolph(int x, int y, int id) {
    int moveX = 0;
    if (x > rx) moveX = 1;
    else if (x < rx) moveX = -1;
    
    int moveY = 0;
    if (y > ry) moveY = 1;
    else if (y < ry) moveY = -1;
    
    map[rx][ry] = 0; // 기존에 루돌프가 있던 위치는 빈칸으로 만들어줌
    
    // 가장 가까운 산타 쪽으로 움직임
    rx += moveX;
    ry += moveY;
    
    // 루돌프가 움직여서 산타와 충돌한 경우
    if (rx == x && ry == y) {
        // 루돌프가 이동해온 방향으로 C칸 움직임
        int firstX = x + moveX * C;
        int firstY = y + moveY * C;
        
        // 충돌이 일어나서 상호작용이 일어날 수도 있기 때문에 저장해두는 것
        int lastX = firstX;
        int lastY = firstY;
        
        stun[id] = 2; // 충돌이 일어났으니까 기절시킴
        
        // 격자 범위 안이고, 다른 산타가 있는 경우 연쇄적으로 충돌이 일어남
        while (isRange(lastX, lastY) && map[lastX][lastY] > 0) {
            // 루돌프가 이동한 방향으로 계속 한 칸씩 움직임
            lastX += moveX;
            lastY += moveY;
        }
        
        // 연쇄적으로 충돌이 일어난 마지막 위치에서부터 시작해서 산타를 이동시킴
        while (!(lastX == firstX && lastY == firstY)) {
            // map[prevX][prevY]에 있던 산타가 map[lastX][lastY]로 이동하기 때문에 prevX, prevY 구해줌
            int prevX = lastX - moveX;
            int prevY = lastY - moveY;
            
            // 범위를 벗어나는 경우 종료
            if (!isRange(prevX, prevY)) {
                break;
            }
            
            int idx = map[prevX][prevY];
            
            if (isRange(lastX, lastY)) {
                // 격자 안인 경우 이전 칸에 있던 산타를 현재 칸으로 옮겨줌
                map[lastX][lastY] = idx;
                santa[idx] = Santa(lastX, lastY);
            } else {
                dead[idx] = true; // 격자 밖을 벗어나는 경우 죽은 표시 해줌
            }
            
            lastX = prevX;
            lastY = prevY;
        }
        
        // 해당 산타 점수 증가시키고 위치 옮김
        score[id] += C;
        
        if (isRange(firstX, firstY)) {
            map[firstX][firstY] = id;
            santa[id] = Santa(firstX, firstY);
        } else {
            dead[id] = true;
        }
    }
    
    map[rx][ry] = -1; // 루돌프 위치 옮김
}

void moveSanta() {
    for (int i = 1; i <= P; i++) {
        // 격자 밖을 벗어난 산타일 경우 다음으로 넘어감
        if (dead[i] || stun[i] > 0) {
            continue;
        }
        
        int minDist = pow(santa[i].x - rx, 2) + pow(santa[i].y - ry, 2);
        int moveDir = -1;
        
        // 방향 우선순위에 따라 상우하좌 4방향 이동해보면서 루돌프와 가장 가까운 방향 찾음
        for (int d = 0; d < 4; d++) {
            int nx = santa[i].x + dx[d];
            int ny = santa[i].y + dy[d];
            
            // 격자 밖이거나 다른 산타가 있는 경우 다음으로 넘어감
            if (!isRange(nx, ny) || map[nx][ny] > 0) {
                continue;
            }
            
            int dist = pow(nx - rx, 2) + pow(ny - ry, 2);
            
            if (dist < minDist) {
                minDist = dist;
                moveDir = d;
            }
        }
        
        if (moveDir != -1) {
            // 다음 이동위치 구함
            int nx = santa[i].x + dx[moveDir];
            int ny = santa[i].y + dy[moveDir];
            
            if (nx == rx && ny == ry) { // 이동한 산타가 루돌프와 충돌한 경우
                stun[i] = 2;
                
                // 충돌한 경우에는 해당 산타가 이동한 방향의 반대 방향으로 밀려나기 때문에 - 붙여줌
                int moveX = -dx[moveDir];
                int moveY = -dy[moveDir];
                
                int firstX = nx + moveX * D;
                int firstY = ny + moveY * D;
                
                int lastX = firstX;
                int lastY = firstY;
                
                if (D == 1) { // 밀려나는 칸이 한 칸인 경우
                    // 루돌프와 충돌하고 자신이 이동해온 방향의 반대 방향으로 이동하면 원래 위치에 그대로 있게 됨 -> 점수만 증가시킴
                    score[i] += D;
                } else {
                    // 격자 안이고 다른 산타가 있는 경우
                    while (isRange(lastX, lastY) && map[lastX][lastY] > 0) {
                        // 한 칸씩 밀려남
                        lastX += moveX;
                        lastY += moveY;
                    }
                    
                    // 연쇄적으로 충돌이 일어난 마지막 위치에서부터 시작해서 산타를 이동시킴
                    while (!(lastX == firstX && lastY == firstY)) {
                        // map[prevX][prevY]에 있던 산타가 map[lastX][lastY]로 이동하기 때문에 prevX, prevY 구해줌
                        int prevX = lastX - moveX;
                        int prevY = lastY - moveY;
                        
                        // 범위를 벗어나는 경우 종료
                        if (!isRange(prevX, prevY)) {
                            break;
                        }
                        
                        int idx = map[prevX][prevY];
                        
                        if (isRange(lastX, lastY)) {
                            // 격자 안인 경우 이전 칸에 있던 산타를 현재 칸으로 옮겨줌
                            map[lastX][lastY] = idx;
                            santa[idx] = Santa(lastX, lastY);
                        } else {
                            dead[idx] = true; // 격자 밖을 벗어나는 경우 죽은 표시 해줌
                        }
                        
                        lastX = prevX;
                        lastY = prevY;
                    }
                    
                    // 해당 산타 점수 증가시키고 위치 옮김
                    score[i] += D;
                    
                    map[santa[i].x][santa[i].y] = 0;
                    
                    if (isRange(firstX, firstY)) {
                        map[firstX][firstY] = i;
                        santa[i] = Santa(firstX, firstY);
                    } else {
                        dead[i] = true;
                    }
                }
                
            } else { // 충돌하지 않은 경우
                map[santa[i].x][santa[i].y] = 0; // 원래 산타가 있던 위치는 빈칸으로 만듦
                
                // 해당 산타 위치 갱신
                santa[i] = Santa(nx, ny);
                map[nx][ny] = i;
            }
        }
    }
}

void getScore() {
    for (int i = 1; i <= P; i++) {
        if (!dead[i]) {
            score[i]++;
        }
    }
}

void decreaseTurn() {
    for (int i = 1; i <= P; i++) {
        if (stun[i] > 0) {
            stun[i]--;
        }
    }
}

int main() {
    cin >> N >> M >> P >> C >> D;
    
    map.resize(N, vector<int>(N, 0));
    santa.resize(P + 1);
    stun.resize(P + 1, 0);
    dead.resize(P + 1, false);
    score.resize(P + 1, 0);
    
    cin >> rx >> ry;
    rx--; ry--; // 0-based 인덱스로 변환
    
    map[rx][ry] = -1;
    
    for (int i = 0; i < P; i++) {
        int num, x, y;
        cin >> num >> x >> y;
        x--; y--; // 0-based 인덱스로 변환
        santa[num] = Santa(x, y);
        map[x][y] = num;
    }
    
    // 게임 턴 수만큼 반복
    while (M-- > 0) {
        int minX = 10000;
        int minY = 10000;
        int minId = 0;
        
        // 1. 가장 가까운 산타 찾음
        for (int i = 1; i <= P; i++) {
            // 격자 밖을 벗어난 산타일 경우 다음으로 넘어감
            if (dead[i]) {
                continue;
            }
            
            Distance min(pow(minX - rx, 2) + pow(minY - ry, 2), minX, minY);
            Distance cur(pow(santa[i].x - rx, 2) + pow(santa[i].y - ry, 2), santa[i].x, santa[i].y);
            
            if (cur < min) {
                minX = cur.x;
                minY = cur.y;
                minId = i;
            }
        }
        
        // 2. 루돌프가 가장 가까운 산타를 향해 돌진
        if (minId != 0) {
            moveRudolph(minX, minY, minId);
        }
        
        // 3. 산타가 루돌프와 가장 가까운 방향으로 움직임
        moveSanta();
        
        // 4. 죽지 않은 산타의 점수 증가시킴
        getScore();
        
        // 5. 기절한 산타의 턴 수를 감소시킴
        decreaseTurn();
    }
    
    // 산타가 얻은 최종점수 출력
    for (int i = 1; i <= P; i++) {
        cout << score[i] << " ";
    }
    
    return 0;
}