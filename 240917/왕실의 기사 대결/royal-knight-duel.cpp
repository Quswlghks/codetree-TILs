#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

int L, N, Q;
int Board[40][40];
int knightBoard[40][40];
pair<int,int> order[100];

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
        for(int i=0;i<L;i++){
            for(int j=0;j<L;j++){
                if(newKnightBoard[i][j]==this->index){
                    this->r = i; this->c = j;
                    return;
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

    // 수정된 부분: BFS 함수를 vector<pair<int, int>>를 반환하도록 변경
    vector<pair<int, int>> BFS(int x, int y, int d){
        vector<pair<int, int>> moved;
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
                isvalid = false;
                return moved;
            }

            moved.push_back({cx, cy});

            if(knightBoard[nx][ny] != -1 && !visited[nx][ny]){
                q.push({nx, ny});
                visited[nx][ny] = true;
            }
        }
        return moved;
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

        if(!this->knight[i].islive){
            isvalid = false;
            return;
        }

        // 수정된 부분: BFS 결과를 vector로 받아 처리
        vector<pair<int, int>> moved = BFS(this->knight[i].r, this->knight[i].c, d);

        if(isvalid){
            // 기사 이동 처리
            for(int j = moved.size() - 1; j >= 0; j--){
                int cx = moved[j].first;
                int cy = moved[j].second;
                int nx = cx + dx[d];
                int ny = cy + dy[d];
                knightBoard[nx][ny] = knightBoard[cx][cy];
                knightBoard[cx][cy] = -1;
            }

            // 기사 위치 및 대미지 업데이트
            for(int index=0;index<N;index++){
                this->knight[index].update(this->knightBoard);
                if(index != i && this->knight[index].islive){
                    int trapCount = 0;
                    for(int r = this->knight[index].r; r < this->knight[index].r + this->knight[index].h; r++){
                        for(int c = this->knight[index].c; c < this->knight[index].c + this->knight[index].w; c++){
                            if(Board[r][c] == 1) trapCount++;
                        }
                    }
                    if(trapCount > 0) {  // 수정된 부분: 함정에 걸렸을 때만 대미지 적용
                        this->knight[index].damage += trapCount;
                        this->knight[index].k -= trapCount;
                        if(this->knight[index].k <= 0){
                            this->knight[index].islive = false;
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
    }
};

void applyCase(Case now){
    memcpy(knightBoard, now.knightBoard, sizeof(knightBoard));
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
        knight[i].init(r-1,c-1,h,w,k,i);
    }
    for(int index=0;index<Q;index++){
        int i, d;
        cin >> i >> d;
        order[index].first = i-1; order[index].second = d-1;
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
            result+=knight[i].damage;
        }
    }
    cout << result;
}

int main() {
    Input();
    Solve();
    return 0;
}