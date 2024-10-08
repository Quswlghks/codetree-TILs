#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

int R,C;
int K;
int c[1001];
int d[1001];

int result;

// 0,1,2,3은 북, 동, 남, 서
int dx[] = {-1,0,1,0};
int dy[] = {0,1,0,-1};

int Board[100][100];

void Input(){
    cin >> R >> C >> K;
    for(int i = 0; i < K; i++){
        cin >> c[i] >> d[i];
    }
}

void printBoard(){
    cout<<"Board : \n";
    for(int i = 3; i <= R+2; i++){
        for(int j = 1; j < C+1; j++){
            cout<<Board[i][j]<<" ";
        }cout<<"\n";
    }
}

void Init(){
    //cout<<"Inint!\n";
    for(int i = 0; i <= R+2; i++){
        for(int j = 0; j < C+1; j++){
            Board[i][j] = 0;
        }
    }
}

int canGo(int x, int y, int dir){
    switch(dir){
        case 0:
            return false;
        break;
        case 1:
            if(y+2<=C&&!Board[x-1][y+1]&&!Board[x][y+2]&&!Board[x+1][y+1]&&!Board[x][y+1]) return true;
            return false;
        break;
        case 2:
            if(x+2<=R+2&&!Board[x+1][y+1]&&!Board[x+1][y-1]&&!Board[x+2][y]&&!Board[x+1][y]) return true;
            return false;
        break;
        case 3:
            if(y-2>=1&&!Board[x-1][y-1]&&!Board[x][y-2]&&!Board[x+1][y-1]&&!Board[x][y-1]) return true;
            return false;
        break;
    }
}

int isComeIn(int cc){
    if(canGo(1,cc,2) && canGo(2,cc,2) && canGo(3,cc,2)) return true;
    if(canGo(1,cc,2) && canGo(2,cc,2) && canGo(3,cc,1)) return true;
    if(canGo(1,cc,2) && canGo(2,cc,2) && canGo(3,cc,3)) return true;
    return false;
}

// pair first 기준 내림차순 정렬
bool compare1(pair<int, int> a, pair<int, int> b) {

	return a.first > b.first;
}

int BFS(int x, int y, int dir){
    int visited[100][100];for(int i = 0; i < 100; i++){for(int j = 0; j < 100; j++){visited[i][j] = 0;}}
    queue<pair<int,int>> q; vector<pair<int,int>> v; 
    visited[x][y]=true;visited[x-1][y]=true;visited[x+1][y]=true;visited[x][y-1]=true;visited[x][y+1]=true;
    q.push({x+dx[dir],y+dy[dir]}); v.push_back({x+dx[dir],y+dy[dir]});
    int qx, qy;
    while(!q.empty()){
        qx = q.front().first; qy = q.front().second; q.pop();
        if(!(qx>=3&&qx<=R+1&&y>=1&&y<=C)) continue;
        //cout<<"qx : "<<qx<<" "<<"qy : "<<qy<<"\n";
        for(int i = 0; i < 4; i++){
            int nx = qx+dx[i]; int ny = qy+dy[i];
            if((Board[nx][ny]==1 || Board[nx][ny]==2) && !visited[nx][ny]){
            visited[nx][ny]=1; 
            q.push({nx,ny});
            v.push_back({nx,ny});//cout<<"change gollem!\n"<<nx<<" "<<ny<<"\n";
            }
        }
    }
    sort(v.begin(),v.end(), compare1);// cout<<"move : "<<v[0].first-2<<" "<<v[0].second<<"\n";
    return v[0].first-2 > x+1-2 ? v[0].first-2 : x+1-2;
}

int Move(int i, int x, int y, int dir){
    if(canGo(x,y,2)) {return Move(i,x+1,y,dir);}
    if(canGo(x,y,3)&&canGo(x,y-1,2)) {return Move(i,x+1,y-1,dir==0 ? 3 : dir-1);}
    if(canGo(x,y,1)&&canGo(x,y+1,2)) {return Move(i,x+1,y+1,dir==3 ? 0 : dir+1);}
    //update
    Board[x][y]=1;
    Board[x+1][y]=1;
    Board[x][y+1]=1;
    Board[x-1][y]=1;
    Board[x][y-1]=1;
    Board[x+dx[dir]][y+dy[dir]]=2;

    //search
    return BFS(x,y, dir);
}

void Solve(){
    for(int i = 0; i < K; i++){
        if(!isComeIn(c[i])){Init(); continue;}
        int temp = Move(i,1,c[i],d[i]);
        result+= temp;
        //printBoard();
        //cout<<"move : "<<temp-1<<"\n";
    }
    cout<<result;
}


int main() {
    Input();
    Solve();
    return 0;
}