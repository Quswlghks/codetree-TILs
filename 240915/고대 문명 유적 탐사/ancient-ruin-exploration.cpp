#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int K,M;
int Map[5][5];
int p[300];
int pindex;

typedef struct mapState{
    int value;
    int degree;
    int x, y;
}mapState;

int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};

int roatedMap[5][5];

void printMap(){
    for(int i =0;i<5;i++){
        for(int j=0;j<5;j++){
            cout<<Map[i][j]<< " ";
        }cout<<"\n";
    }
}

bool compare1(mapState a, mapState b){
    if(a.value!=b.value){
        return a.value>b.value;
    }else{
        if(a.degree!=b.degree){
            return a.degree<b.degree;
        }else{
            if(a.y!=b.y){
                return a.y<b.y;
            }else{
                return a.x<b.x;
            }
        }
    }
}

vector<pair<int,int>> v;

int getscore(int Pmap[][5]){
    bool visited[5][5]={false};
    vector<int> numBFS[8];
    queue<pair<int,int>> q; //(x,y)
    v.clear();

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(visited[i][j]) continue; 
            int num = Pmap[i][j]; numBFS[num].push_back(0);
            q.push({i,j}); 
            while(!q.empty()){
                int x = q.front().first; int y = q.front().second; q.pop();
                if(visited[x][y]) continue; visited[x][y]= true;
                numBFS[num][numBFS[num].size()-1]++;// cout<<"plus!!\n";
                if(numBFS[num][numBFS[num].size()-1]==3){v.push_back({x,y});}
                for(int z = 0; z < 4; z++){
                    int nx = x + dx[z];
                    int ny = y + dy[z];
                    // Add boundary check
                    if(nx >= 0 && nx < 5 && ny >= 0 && ny < 5 && Pmap[nx][ny] == num)
                        q.push({nx, ny});
                }
            }
        }
    }

    int result = 0;
    for(int i = 1; i <= 7; i++){
        for(int j = 0; j < numBFS[i].size();j++){
            //cout<<"i, j : "<<i<<" "<<j<<"\n"<<"numBFS : "<<numBFS[i][j]<<"\n";
            if(numBFS[i][j]>=3){
                result+=numBFS[i][j];
            }
        }
    }
    //cout<<"result : "<<result<<"\n";
    return result;
}

void applyZeroMap(){
    getscore(Map);
    bool visited[5][5]={false};
    queue<pair<int,int>> q2; //(x,y)
    for(int i = 0; i < v.size(); i++){
        int x = v[i].first; int y = v[i].second;
        int num = Map[x][y];
        if(visited[x][y]) continue; 
        q2.push({x,y}); 
        while(!q2.empty()){
            int qx = q2.front().first; int qy = q2.front().second; q2.pop();
            if(visited[qx][qy]) continue; visited[qx][qy]= true;
            Map[qx][qy] = 0; 
            for(int z = 0; z < 4; z++){
                int nx = qx + dx[z];
                int ny = qy + dy[z];
                // Add boundary check
                if(nx >= 0 && nx < 5 && ny >= 0 && ny < 5 && Map[nx][ny] == num)
                    q2.push({nx, ny});
            }
        }
    }
}



mapState rotate90(int x, int y) {
    mapState result; 
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            roatedMap[i][j] = Map[i][j];
        }
    }
    for(int i = x-1; i <= x+1; i++) {
        for(int j = y-1; j <= y+1; j++) {
            roatedMap[x+(j-y)][y-(i-x)] = Map[i][j];
        }
    }
    result.value = getscore(roatedMap);
    result.degree = 0;
    result.x = x; result.y = y;
    return result;
}

mapState rotate180(int x, int y) {
    mapState result;
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            roatedMap[i][j] = Map[i][j];
        }
    }
    for(int i = x-1; i <= x+1; i++) {
        for(int j = y-1; j <= y+1; j++) {
            roatedMap[2*x-i][2*y-j] = Map[i][j];
        }
    }
    result.value = getscore(roatedMap);
    result.degree = 1;
    result.x = x; result.y = y;
    return result;
}

mapState rotate270(int x, int y) {
    mapState result;
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            roatedMap[i][j] = Map[i][j];
        }
    }
    for(int i = x-1; i <= x+1; i++) {
        for(int j = y-1; j <= y+1; j++) {
            roatedMap[x-(j-y)][y+(i-x)] = Map[i][j];
        }
    }
    result.value = getscore(roatedMap);
    result.degree = 2;
    result.x = x; result.y = y;
    return result;
}

void applyrotatedMap(mapState map){
    int degree = map.degree;
    int x = map.x; int y = map.y;
    switch(degree){
        case 0:
            rotate90(x,y);
            for(int i = 0; i<5;i++){for(int j=0;j<5;j++){Map[i][j]=roatedMap[i][j];}}
            break;
        case 1:
            rotate180(x,y);
            for(int i = 0; i<5;i++){for(int j=0;j<5;j++){Map[i][j]=roatedMap[i][j];}}
            break;
        case 2:
            rotate270(x,y);
            for(int i = 0; i<5;i++){for(int j=0;j<5;j++){Map[i][j]=roatedMap[i][j];}}
            break;
    }
    return;
}

void rotate(){
    vector<mapState> v;
    //v.push_back(rotate90(2,2));
    
    for(int i = 1; i <= 3; i++){
        for(int j = 1; j <= 3; j++){
            v.push_back(rotate90(i,j));
            v.push_back(rotate180(i,j));
            v.push_back(rotate270(i,j));
        }
    }
    sort(v.begin(), v.end(), compare1); 
    applyrotatedMap(v[0]); //printMap(); 
    return;
}

void setMap(){// cout << "zeroed : \n";printMap();cout<<"\n";
    for(int i = 0; i < 5; i++){
        for(int j = 4; j >= 0; j--){
            if(Map[j][i]==0){
                Map[j][i]=p[pindex++];
            }
        }
    }
}

void Solve(){
    for(int i = 0; i < K; i++){
        int result=0;
        rotate();
        while(1){
            int score = getscore(Map); applyZeroMap(); result+=score; //cout <<score<<" ";
            if(score==0) break;
            setMap(); //cout<<"\n\nFilled:\n"; printMap();
        }
        if(result==0) return;
        cout<<result<<" ";
    }
    return;
}


void Input(){
    cin >> K >> M;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            cin >> Map[i][j];
        }
    }
    for(int i = 0; i < M; i++) cin >> p[i];
}

int main() {
    Input();
    Solve();
    return 0;
}