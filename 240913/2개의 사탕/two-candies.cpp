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
    Point Red;
    Point Blue;
    int num;
}Case;

Point move(const int board[10][10], Point p, Point other, int dx, int dy) {
    while (true) {
        int nx = p.x + dx, ny = p.y + dy;
        if (board[nx][ny] == 2) break; // 벽이면 멈춤
        if (board[nx][ny] == 5) return {nx, ny}; // 구멍에 도달하면 반환
        if ((nx == other.x && ny == other.y) && board[nx][ny] != 5) break; // 다른 구슬이면 멈춤
        p.x = nx;
        p.y = ny;
    }
    return p;
}

Case moveBoard(const int board[10][10], Case c, int dir){
    Case result = c;
    int dx[] = {-1, 1, 0, 0}; // 상, 하, 좌, 우
    int dy[] = {0, 0, -1, 1};
    
    // 먼저 움직일 구슬 결정
    bool redFirst = (dir == 0 && c.Red.x < c.Blue.x) ||
                    (dir == 1 && c.Red.x > c.Blue.x) ||
                    (dir == 2 && c.Red.y < c.Blue.y) ||
                    (dir == 3 && c.Red.y > c.Blue.y);

    if (redFirst) {
        result.Red = move(board, c.Red, c.Blue, dx[dir], dy[dir]);
        result.Blue = move(board, c.Blue, result.Red, dx[dir], dy[dir]);
    } else {
        result.Blue = move(board, c.Blue, c.Red, dx[dir], dy[dir]);
        result.Red = move(board, c.Red, result.Blue, dx[dir], dy[dir]);
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

    Case first = {Red, Blue, 0};
    queue<Case> q;
    q.push(first);

    int result = -1;

    while(!q.empty()){
        Case c = q.front(); q.pop();

        if(c.num > 10) continue;

        if(Board[c.Red.x][c.Red.y] == 5){
            if(Board[c.Blue.x][c.Blue.y] != 5){
                result = c.num;
                break;
            }
            continue; // 파란 구슬도 구멍에 들어갔으면 실패
        }

        for(int i = 0; i < 4; i++) {
            Case next = moveBoard(Board, c, i);
            if(Board[next.Blue.x][next.Blue.y] != 5) {
                q.push(next);
            }
        }
    }

    cout << result;

    return 0;
}