#include <iostream>
#include <vector>
#include <set>
using namespace std;

int n, m;
int Board[15][15];
vector<pair<int,int>> medi;
set<pair<int,int>> visited;
pair<int,int> moveInfo[100];

int dx[8] = {0,-1,-1,-1,0,1,1,1};
int dy[8] = {1,1,0,-1,-1,-1,0,1};

int dxMore[4]={1,1,-1,-1};
int dyMore[4]={1,-1,-1,1};

void Input(){
    cin >> n >> m;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> Board[i][j];
        }
    }
    medi = {{n-1,0}, {n-2,0}, {n-1,1}, {n-2,1}};
    for(int i=0; i<m; i++) cin >> moveInfo[i].first >> moveInfo[i].second;
}

void moveMedi(int year){
    int d = moveInfo[year].first-1; int p = moveInfo[year].second;
    for(auto& pos : medi){
        pos.first = (pos.first + dx[d] * p + n * 1000) % n;
        pos.second = (pos.second + dy[d] * p + n * 1000) % n;
    }
}

void grow(){
    visited.clear();
    for(auto& pos : medi){
        Board[pos.first][pos.second]++;
        visited.insert(pos);
    }
    
    vector<int> growAmount(medi.size(), 0);
    for(int i = 0; i < medi.size(); i++){
        int r = medi[i].first, c = medi[i].second;
        for(int j = 0; j < 4; j++){
            int nr = r + dxMore[j], nc = c + dyMore[j];
            if(nr >= 0 && nr < n && nc >= 0 && nc < n && Board[nr][nc] > 0){
                growAmount[i]++;
            }
        }
    }
    
    for(int i = 0; i < medi.size(); i++){
        Board[medi[i].first][medi[i].second] += growAmount[i];
    }
}

void makeNewMedi(){
    vector<pair<int,int>> newMedi;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(Board[i][j] >= 2 && visited.find({i,j}) == visited.end()){
                Board[i][j] -= 2;
                newMedi.push_back({i,j});
            }
        }
    }
    medi = newMedi;
}

void Solve(){
    for(int i=0; i<m; i++){
        moveMedi(i);
        grow();
        makeNewMedi();
    }
    int result = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            result += Board[i][j];
        }
    }
    cout << result;
}

int main() {
    Input();
    Solve();
    return 0;
}