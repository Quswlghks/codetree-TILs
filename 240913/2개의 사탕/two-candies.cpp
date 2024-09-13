#include <iostream>
#include <queue>
using namespace std;

int Board[10][10];
int N,M;

typedef struct Point{
    int x;
    int y;
}Point;

Point Red;
Point Blue;
Point Goal;

typedef struct Case{
    int Board[10][10];
    Point Red;
    Point Blue;
    Point Goal;
    int num;
}Case;

Point move(Case& c, Point p, int dx, int dy) {
    while (true) {
        int nx = p.x + dx, ny = p.y + dy;
        if (c.Board[nx][ny] == 2) break; // 벽이면 멈춤
        if (nx == c.Goal.x && ny == c.Goal.y) return {nx, ny}; // 구멍에 도달하면 반환
        if (c.Board[nx][ny] != 1 && !(nx == c.Red.x && ny == c.Red.y) && !(nx == c.Blue.x && ny == c.Blue.y)) break; // 다른 구슬이나 장애물이면 멈춤
        p.x = nx;
        p.y = ny;
    }
    c.Board[p.x][p.y] = 1;
    return p;
}

Case moveBoard(Case temp, int what){
    Case result = temp;
    int dx[] = {-1, 1, 0, 0}; // 상, 하, 좌, 우
    int dy[] = {0, 0, -1, 1};
    
    // 먼저 움직일 구슬 결정
    bool redFirst = (what == 1 && result.Red.x < result.Blue.x) ||
                    (what == 2 && result.Red.x > result.Blue.x) ||
                    (what == 3 && result.Red.y < result.Blue.y) ||
                    (what == 4 && result.Red.y > result.Blue.y);

    if (redFirst) {
        result.Red = move(result, result.Red, dx[what-1], dy[what-1]);
        result.Blue = move(result, result.Blue, dx[what-1], dy[what-1]);
    } else {
        result.Blue = move(result, result.Blue, dx[what-1], dy[what-1]);
        result.Red = move(result, result.Red, dx[what-1], dy[what-1]);
    }

    // 보드 상태 업데이트
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (result.Board[i][j] == 3 || result.Board[i][j] == 4) {
                result.Board[i][j] = 1; // 빈 칸으로 만듦
            }
        }
    }
    if (!(result.Red.x == result.Goal.x && result.Red.y == result.Goal.y)) {
        result.Board[result.Red.x][result.Red.y] = 4;
    }
    if (!(result.Blue.x == result.Goal.x && result.Blue.y == result.Goal.y)) {
        result.Board[result.Blue.x][result.Blue.y] = 3;
    }

    result.num += 1;
    return result;
}

int main() {
    char temp;
    cin >> N >> M;
    for(int i = 0 ; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> temp;
            if(temp == '.'){
                Board[i][j] = 1;
            }else if(temp == '#'){
                Board[i][j] = 2;
            }else if(temp=='B'){
                Board[i][j] = 3;
                Blue.x = i; Blue.y=j;
            }else if(temp=='R'){
                Board[i][j] = 4;
                Red.x = i; Red.y=j;
            }else if(temp=='O'){
                Board[i][j] = 5;
                Goal.x=i;Goal.y=j;
            }
        }
    }

    Case first;
    for(int i = 0 ; i < N; i++){
        for(int j = 0; j < M; j++){
            first.Board[i][j] = Board[i][j];
        }
    }
    first.Red = Red;first.Blue = Blue; first.Goal = Goal;
    first.num=0;

    queue<Case> q;
    q.push(first);

    int result = -1;

    while(!q.empty()){
        Case temp = q.front(); q.pop();

        if(temp.num > 10){
            cout<<"-1";return 0;
        }
        if(temp.Red.x == temp.Goal.x && temp.Red.y == temp.Goal.y){
            if(!(temp.Blue.x == temp.Goal.x && temp.Blue.y == temp.Goal.y)){
                result = temp.num+1;
                break;
            }
            continue; // 파란 구슬도 구멍에 들어갔으면 실패
        }

        for(int i = 1; i <= 4; i++) {
            q.push(moveBoard(temp, i));
        }
    }

    cout << result;

    return 0;
}