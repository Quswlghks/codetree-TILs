#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

int L, N, Q;
int Board[40][40];
int knightBoard[40][40];
pair<int,int> order[100];

int dx[] = {-1,0,1,0};  // 위, 오른쪽, 아래, 왼쪽 순서로 변경
int dy[] = {0,1,0,-1};

class Knight{
public:
    int index;
    int r,c;
    int h,w;
    int k;
    bool islive = true;
    int damage = 0;
    Knight(){}
    void init(int pr, int pc,int ph,int pw,int pk,int i){
        this->index = i;
        r=pr-1; c=pc-1; h=ph; w=pw; k=pk;  // 0-based 인덱스로 변경
        for(int i = r; i < r+h; i++){
            for(int j=c;j<c+w;j++){
                knightBoard[i][j] = index;
            }
        }
    }
    void update(int newKnightBoard[40][40]){
        for(int i=0;i<L;i++){
            for(int j=0;j<L;j++){
                if(newKnightBoard[i][j]==this->index){
                    this->r = i; this->c = j;
                    return;  // 위치를 찾았으면 바로 종료
                }
            }
        }
    }
};
Knight knight[30];

// 주어진 위치가 체스판 내부인지 확인하는 함수
bool checkIsIn(int x, int y){
    return x >= 0 && x < L && y >= 0 && y < L;
}

// BFS를 위한 구조체 정의
struct Position {
    int x, y;
    Position(int x, int y) : x(x), y(y) {}
};

class Case{
public:
    bool isvalid = true;
    int knightBoard[40][40];
    Knight knight[30];

    // BFS 함수 구현
    void BFS(int startX, int startY, int d){
        queue<Position> q;
        vector<Position> moved;
        bool visited[40][40] = {false};

        q.push(Position(startX, startY));
        visited[startX][startY] = true;

        while(!q.empty()){
            Position current = q.front();
            q.pop();

            int nx = current.x + dx[d];
            int ny = current.y + dy[d];

            if(!checkIsIn(nx, ny) || Board[nx][ny] == 2){
                isvalid = false;
                return;
            }

            if(knightBoard[nx][ny] != -1 && !visited[nx][ny]){
                q.push(Position(nx, ny));
                visited[nx][ny] = true;
            }

            moved.push_back(current);
        }

        // 기사들을 이동시킴
        for(auto pos : moved){
            int nx = pos.x + dx[d];
            int ny = pos.y + dy[d];
            knightBoard[nx][ny] = knightBoard[pos.x][pos.y];
            knightBoard[pos.x][pos.y] = -1;
        }
    }

    Case(int i, int d){
        memset(knightBoard, -1, sizeof(knightBoard));
        for(int index=0;index<N;index++){
            this->knight[index] = ::knight[index];
            int r = knight[index].r;
            int c = knight[index].c;
            int h = knight[index].h;
            int w = knight[index].w;
            for(int i = r; i < r+h; i++){
                for(int j=c;j<c+w;j++){
                    this->knightBoard[i][j] = index;
                }
            }
        }

        // 기사가 이미 죽었거나 체스판에서 사라졌다면 명령 무시
        if(!this->knight[i].islive){
            isvalid = false;
            return;
        }

        // BFS 실행
        BFS(this->knight[i].r, this->knight[i].c, d);

        if(isvalid){
            // 기사들의 위치 업데이트
            for(int index=0;index<N;index++){
                this->knight[index].update(this->knightBoard);
            }

            // 함정에 의한 데미지 계산
            for(int index=0;index<N;index++){
                if(index != i && this->knight[index].islive){  // 명령받은 기사는 제외
                    int damage = 0;
                    for(int x = this->knight[index].r; x < this->knight[index].r + this->knight[index].h; x++){
                        for(int y = this->knight[index].c; y < this->knight[index].c + this->knight[index].w; y++){
                            if(Board[x][y] == 1) damage++;
                        }
                    }
                    this->knight[index].k -= damage;
                    this->knight[index].damage += damage;
                    if(this->knight[index].k <= 0){
                        this->knight[index].islive = false;
                        // 죽은 기사 제거
                        for(int x = this->knight[index].r; x < this->knight[index].r + this->knight[index].h; x++){
                            for(int y = this->knight[index].c; y < this->knight[index].c + this->knight[index].w; y++){
                                this->knightBoard[x][y] = -1;
                            }
                        }
                    }
                }
            }
        }
    }
};

void applyCase(Case now){
    memcpy(knightBoard, now.knightBoard, sizeof(knightBoard));
    for(int i=0;i<N;i++){
        knight[i] = now.knight[i];
    }
}

void Input(){
    cin >> L >> N >> Q;
    for(int i=0;i<L;i++){
        for(int j=0;j<L;j++){
            cin >> Board[i][j];
        }
    }
    for(int i=0;i<N;i++){
        int r,c,h,w,k;
        cin >> r >> c >> h >> w >> k;
        knight[i].init(r,c,h,w,k,i);
    }
    for(int index=0;index<Q;index++){
        int i, d;
        cin >> i >> d;
        order[index].first = i-1; order[index].second = d-1;  // 0-based 인덱스로 변경
    }
}

void Solve(){
    for(int i=0;i<Q;i++){
        Case now(order[i].first, order[i].second);
        if(now.isvalid) applyCase(now);
    }
    int result = 0;
    for(int i=0;i<N;i++){
        if(knight[i].islive){
            result += knight[i].damage;
        }
    }
    cout << result;
}

int main() {
    Input();
    Solve();
    return 0;
}