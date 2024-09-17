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

// 한글 주석: 기사의 이동 가능 여부를 확인하는 함수 추가
bool canMove(int knightIndex, int d) {
    Knight& k = knight[knightIndex];
    for(int i = k.r; i < k.r + k.h; i++) {
        for(int j = k.c; j < k.c + k.w; j++) {
            int ni = i + dx[d], nj = j + dy[d];
            if(!checkIsIn(ni, nj) || Board[ni][nj] == 2) return false;
        }
    }
    return true;
}

// 한글 주석: 기사를 이동시키는 함수 추가
void moveKnight(int knightIndex, int d) {
    Knight& k = knight[knightIndex];
    // 한글 주석: 기존 위치의 knightBoard 초기화
    for(int i = k.r; i < k.r + k.h; i++) {
        for(int j = k.c; j < k.c + k.w; j++) {
            knightBoard[i][j] = -1;
        }
    }
    // 한글 주석: 새 위치로 기사 이동
    k.r += dx[d]; k.c += dy[d];
    for(int i = k.r; i < k.r + k.h; i++) {
        for(int j = k.c; j < k.c + k.w; j++) {
            knightBoard[i][j] = knightIndex;
        }
    }
}

class Case{
public:
    bool isvalid = true;
    int knightBoard[40][40];
    Knight knight[30];

    // 한글 주석: BFS 대신 직접 이동 로직 구현
    void moveKnights(int startKnight, int d) {
        vector<int> toMove;
        vector<bool> checked(N, false);
        toMove.push_back(startKnight);
        checked[startKnight] = true;

        for(int i = 0; i < toMove.size(); i++) {
            int current = toMove[i];
            Knight& k = knight[current];
            for(int r = k.r; r < k.r + k.h; r++) {
                for(int c = k.c; c < k.c + k.w; c++) {
                    int nr = r + dx[d], nc = c + dy[d];
                    if(checkIsIn(nr, nc) && knightBoard[nr][nc] != -1 && !checked[knightBoard[nr][nc]]) {
                        toMove.push_back(knightBoard[nr][nc]);
                        checked[knightBoard[nr][nc]] = true;
                    }
                }
            }
        }

        // 한글 주석: 이동 가능 여부 확인
        for(int i : toMove) {
            if(!canMove(i, d)) {
                isvalid = false;
                return;
            }
        }

        // 한글 주석: 실제 이동 수행
        for(int i = toMove.size() - 1; i >= 0; i--) {
            moveKnight(toMove[i], d);
        }
    }

    Case(int i, int d){
        memcpy(knightBoard, ::knightBoard, sizeof(knightBoard));
        for(int index=0;index<N;index++){
            this->knight[index] = ::knight[index];
        }

        // 한글 주석: 기사가 이미 죽었거나 체스판에서 사라졌다면 명령 무시
        if(!this->knight[i].islive){
            isvalid = false;
            return;
        }

        // 한글 주석: 기사들 이동
        moveKnights(i, d);

        if(isvalid){
            // 한글 주석: 데미지 계산 및 적용
            for(int index=0;index<N;index++){
                if(index != i && this->knight[index].islive){  // 명령받은 기사는 제외
                    int newDamage = 0;
                    for(int x = this->knight[index].r; x < this->knight[index].r + this->knight[index].h; x++){
                        for(int y = this->knight[index].c; y < this->knight[index].c + this->knight[index].w; y++){
                            if(Board[x][y] == 1) newDamage++;
                        }
                    }
                    this->knight[index].k -= newDamage;
                    this->knight[index].damage += newDamage;
                    if(this->knight[index].k <= 0){
                        this->knight[index].islive = false;
                        // 한글 주석: 죽은 기사 제거
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