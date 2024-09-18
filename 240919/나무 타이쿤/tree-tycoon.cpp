#include <iostream>
using namespace std;

int n,m;
int Board[15][15];
bool tonicBoard[15][15] = {false};
pair<int,int> moveInfo[100];

int dx[8] = {0,-1,-1,-1,0,1,1,1};
int dy[8] = {1,1,0,-1,-1,-1,0,1};

int dxMore[4]={-1,-1,1,1};
int dyMore[4]={1,-1,1,-1};

void Input(){
    cin >> n >> m;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin >> Board[i][j];
        }
    }
    // 초기 특수 영양제 위치 설정
    tonicBoard[n-2][0] = true;
    tonicBoard[n-2][1] = true;
    tonicBoard[n-1][0] = true;
    tonicBoard[n-1][1] = true;

    for(int i=0;i<m;i++) cin >> moveInfo[i].first >> moveInfo[i].second;
}

void moveTonic(int year){
    int d = moveInfo[year].first-1; int p = moveInfo[year].second;

    bool tonicBoardResult[15][15] = {false};
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(tonicBoard[i][j]){
                // 수정: 음수 처리를 위해 n을 더하고 모듈러 연산
                int nx = (i + dx[d] * p % n + n) % n;
                int ny = (j + dy[d] * p % n + n) % n;
                tonicBoardResult[nx][ny]=true;
            }
        }
    }
    // 결과를 원래 배열로 복사
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            tonicBoard[i][j] = tonicBoardResult[i][j];
        }
    }
}

void applyTonic(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(tonicBoard[i][j]){
                // 기본 성장
                Board[i][j]++;
                
                // 대각선 방향 추가 성장 계산
                int moreGrow = 0;
                for(int z=0;z<4;z++){
                    int nx = i+dxMore[z]; int ny = j+dyMore[z];
                    if(nx<0||nx>=n||ny<0||ny>=n) continue;
                    if(Board[nx][ny]>=1) moreGrow++;
                }
                Board[i][j] += moreGrow;
            }
        }
    }
}

void buyTonic(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            // 수정: 이전에 영양제를 받지 않은 위치만 고려
            if(!tonicBoard[i][j] && Board[i][j]>=2){
                Board[i][j]-=2;
                tonicBoard[i][j]=true;
            }
        }
    }
    tonicBoard[15][15] = {false};
}

void Solve(){
    for(int i=0; i<m; i++){
        moveTonic(i);
        applyTonic();
        buyTonic();
    }
    int result = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            result+=Board[i][j];
        }
    }
    cout<<result;
}

int main() {
    Input();
    Solve();
    return 0;
}