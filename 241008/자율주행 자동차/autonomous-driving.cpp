#include <iostream>
using namespace std;
int n,m;
int x,y,d; //북쪽, 동쪽, 남쪽, 서쪽 0~3
int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};
int Map[50][50];

void Input(){
    cin >> n>> m;
    cin>>x>>y>>d;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>Map[i][j];
        }
    }
}

void turnLeft(){
    if(d==0){
        d=3;
    }else{
        d--;
    }return;
}

bool canGo(int d){
    int nx = x+dx[d]; int ny=y+dy[d];
    if(Map[nx][ny]==0) return true;
    else return false;
}

bool canGoBack(int d){
    int nx = x+dx[d]; int ny=y+dy[d];
    if(Map[nx][ny]==1) return false;
    else return true;
}

void move(){
    int nx = x+dx[d]; int ny=y+dy[d];
    Map[nx][ny] = 2;
    x=nx;y=ny;
    return;
}

int calResult(){
    int result=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(Map[i][j]==2) result++;
        }
    }
    return result;
}

void printMap(){
    cout<<"\n\n";
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cout<<Map[i][j]<<" ";
        }cout<<"\n";
    }cout<<"\n\n";
}

void Solve(){
    Map[x][y]=2;
    while(1){
        int temp=0;
        while(1){
            if(temp>=4) break;
            turnLeft();
            if(canGo(d)){
                move(); temp=0; //printMap();
            }else{
                //cout<<"d: "<<d<<"\n";
                temp++;
            }
        }
        switch(d){
            case 0:
                if(!canGoBack(2)){
                    cout<<calResult(); return;
                }else{
                    x++; //printMap(); 
                    break;
                }
            case 1:
                if(!canGoBack(3)){
                    cout<<calResult(); 
                    return;
                }else{
                    y--; //printMap(); 
                    break;
                }
            case 2:
                if(!canGoBack(0)){
                    cout<<calResult(); return;
                }else{
                    x--; //printMap();
                    break;
                }
            case 3:
                if(!canGoBack(1)){
                    cout<<calResult(); return;
                }else{
                    y++; //printMap();
                    break;
                }
        }
    }
}

int main() {
    Input();
    Solve();
    return 0;
}