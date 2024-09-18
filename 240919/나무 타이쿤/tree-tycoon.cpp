#include <iostream>
#include<vector>
using namespace std;

int n,m;
int Board[15][15];
bool tonicBoard[15][15] = {false};
pair<int,int> moveInfo[100];

// 이동 방향 배열 수정
int dx[8] = {0,-1,-1,-1,0,1,1,1};
int dy[8] = {1,1,0,-1,-1,-1,0,1};

// 대각선 방향 배열 수정
int dxMore[4]={1,1,-1,-1};
int dyMore[4]={1,-1,-1,1};

void debug(){
    cout<<"현재 보드 상태:\n";
    for(int i=0;i<n;i++) {for(int j=0;j<n;j++) {cout<<Board[i][j]<<" ";}cout<<"\n";}
    cout<<"\n현재 토닉 상태:\n";
    for(int i=0;i<n;i++) {for(int j=0;j<n;j++) {cout<<tonicBoard[i][j]<<" ";}cout<<"\n";}cout<<"\n";
}

void Input(){
    cin >> n >> m;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin >> Board[i][j];
        }
    }
    // 초기 특수 영양제 위치 설정
    tonicBoard[n-1][0] = true;
    tonicBoard[n-2][0] = true;
    tonicBoard[n-1][1] = true;
    tonicBoard[n-2][1] = true;

    for(int i=0;i<m;i++) cin >> moveInfo[i].first >> moveInfo[i].second;
}

void moveTonic(int year){
    int d = moveInfo[year].first-1; int p = moveInfo[year].second;

    bool tonicBoardResult[15][15];
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            tonicBoardResult[i][j] = false;
            
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(tonicBoard[i][j]){
                // 수정: 음수 처리를 위해 n을 더하고 모듈러 연산
                int nx = (i + dx[d] * p + n * p) % n;
                int ny = (j + dy[d] * p + n * p) % n;
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
            if(tonicBoard[i][j]) Board[i][j]++;
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(tonicBoard[i][j]){
                // 대각선 방향 추가 성장 계산
                
                int moreGrow = 0;
                for(int z=0;z<4;z++){
                    int nx = i+dxMore[z]; int ny = j+dyMore[z];
                    if(nx<0||nx>=n||ny<0||ny>=n) continue;
                    if(Board[nx][ny]>=1) {moreGrow++;}
                }
                Board[i][j] += (moreGrow);
            }
        }
    }
}

void buyTonic(){
    vector<pair<int,int>> oldTonicPoint;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(tonicBoard[i][j]){
                oldTonicPoint.push_back({i,j});
            }
        }
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            // 수정: 이전에 영양제를 받지 않은 위치만 고려
            if(!tonicBoard[i][j] && Board[i][j]>=2){
                Board[i][j]-=2;
                tonicBoard[i][j]=true;
            }
        }
    }
    
    for(int i=0;i<oldTonicPoint.size();i++){
        int x = oldTonicPoint[i].first; int y = oldTonicPoint[i].second;
        tonicBoard[x][y]=false;
    }
}

void Solve(){
    for(int i=0; i<m; i++){
        //cout<<i+1<<"년째\n";debug();
        moveTonic(i);//cout<<"토닉 이동 후\n";debug();
        applyTonic();//cout<<"토닉 적용 후\n";debug();
        buyTonic();//cout<<"토닉 구매 후\n";debug();cout<<"\n";
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