#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int L, N, Q;
int Board[40][40];
int knightBoard[40][40];
pair<int,int> order[100];

// 방향을 나타내는 배열 (상, 우, 하, 좌)
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

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
        r=pr; c=pc; h=ph; w=pw; k=pk;
        for(int i = r; i < r+h; i++){
            for(int j=c;j<c+w;j++){
                knightBoard[i][j] = index;
            }
        }
    }
    void update(int newKnightBoard[40][40]){
        // 새로운 나이트보드 기반 업데이트
        for(int i=0;i<L;i++){
            for(int j=0;j<L;j++){
                if(newKnightBoard[i][j]==this->index){
                    this->r = i; this->c = j;
                    return; // 위치를 찾았으므로 함수 종료
                }
            }
        }
    }
};
Knight knight[30];

class Case{
public:
    bool isvalid = true;
    int knightBoard[40][40];
    Knight knight[30];

    // BFS 함수 구현
    void BFS(int x, int y, int d){
        queue<pair<int, int>> q;
        vector<vector<bool>> visited(L, vector<bool>(L, false));
        q.push({x, y});
        visited[x][y] = true;

        while(!q.empty()){
            int cx = q.front().first;
            int cy = q.front().second;
            q.pop();

            int nx = cx + dx[d];
            int ny = cy + dy[d];

            if(nx < 0 || nx >= L || ny < 0 || ny >= L || Board[nx][ny] == 2){
                // 이동 불가능한 경우
                isvalid = false;
                return;
            }

            if(knightBoard[nx][ny] != -1 && !visited[nx][ny]){
                // 다른 기사가 있는 경우, 연쇄 이동
                q.push({nx, ny});
                visited[nx][ny] = true;
            }

            // 기사 이동
            knightBoard[nx][ny] = knightBoard[cx][cy];
            knightBoard[cx][cy] = -1;
        }
    }

    Case(int i, int d){
        for(int i=0;i<40;i++){
            for(int j=0;j<40;j++){
                this->knightBoard[i][j]=-1;
            }
        }//나이트 보드 -1로 초기화
        for(int index=0;index<N;index++){
            this->knight[index] = ::knight[index];
        }//나이트 초기화
        for(int index=0;index<N;index++){
            int r = knight[index].r;
            int c = knight[index].c;
            int h = knight[index].h;
            int w = knight[index].w;
            for(int i = r; i < r+h; i++){
                for(int j=c;j<c+w;j++){
                    this->knightBoard[i][j] = index;
                }
            }
        }//나이트에 따른 나이트보드 초기화

        // 명령을 받은 기사가 살아있는지 확인
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

            // 대미지 계산 및 적용
            for(int index=0;index<N;index++){
                if(index != i && this->knight[index].islive){ // 명령 받은 기사는 제외
                    int trapCount = 0;
                    for(int r = this->knight[index].r; r < this->knight[index].r + this->knight[index].h; r++){
                        for(int c = this->knight[index].c; c < this->knight[index].c + this->knight[index].w; c++){
                            if(Board[r][c] == 1) trapCount++;
                        }
                    }
                    this->knight[index].damage += trapCount;
                    this->knight[index].k -= trapCount;
                    if(this->knight[index].k <= 0){
                        this->knight[index].islive = false;
                        // 죽은 기사 제거
                        for(int r = this->knight[index].r; r < this->knight[index].r + this->knight[index].h; r++){
                            for(int c = this->knight[index].c; c < this->knight[index].c + this->knight[index].w; c++){
                                this->knightBoard[r][c] = -1;
                            }
                        }
                    }
                }
            }
        }
    }
};

void applyCase(Case now){
    for(int i=0;i<L;i++){
        for(int j=0;j<L;j++){
            knightBoard[i][j]=now.knightBoard[i][j];
        }
    }
    for(int i=0;i<N;i++){knight[i] = now.knight[i];}
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
        knight[i].init(r-1,c-1,h,w,k,i);  // 0-based 인덱스로 변환
    }
    for(int index=0;index<Q;index++){
        int i, d;
        cin >> i >> d;
        order[index].first = i-1; order[index].second = d-1;  // 0-based 인덱스로 변환
    }
}

void Solve(){
    for(int i=0;i<Q;i++){
        Case now(order[i].first, order[i].second);
        if(now.isvalid) applyCase(now);
    }
    int result = 0;
    for(int i=0;i<N;i++){
        if(knight[i].islive){//살아있는 기사들의
            result+=knight[i].damage;//데미지 누적
        }
    }
    cout << result;
}

int main() {
    Input();
    Solve();
    return 0;
}