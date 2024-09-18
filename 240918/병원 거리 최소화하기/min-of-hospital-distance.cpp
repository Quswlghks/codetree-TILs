#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int Map[51][51];
// 빈칸0, 사람1, 병원2
int n,m;
vector<pair<int,int>> pointHospital;
vector<pair<int,int>> pointHuman;
vector<bool> selectHospital;
int result = 1000000;

void Input(){
    cin >> n >> m;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin >> Map[i][j];
            if(Map[i][j]==2){
                pointHospital.push_back({i,j});
            }else if(Map[i][j]==1){
                pointHuman.push_back({i,j});
            }
        }
    }
}

int calDistance(int x1, int y1, int x2, int y2){return abs(x2-x1) + abs(y2-y1);}

int calAllDistance(vector<bool> PselectHospital){
    int returnresult = 0;
    int minDis = 10000000;
    //cout<<"start!!\n";
    for(int i=0;i<pointHuman.size();i++){
        int x1 = pointHuman[i].first;
        int y1 = pointHuman[i].second;
        for(int j=0;j<pointHospital.size();j++){
            int x2 = pointHospital[j].first;
            int y2 = pointHospital[j].second;
            //cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<"\n";
            int temp = calDistance(x1,y1,x2,y2);
            if(temp < minDis) minDis = temp;
        }returnresult+=minDis;
    }return returnresult;
}

void Backtracking(vector<bool> PselectHospital){
    if(PselectHospital.size()==m){
        //for(int i=0;i<PselectHospital.size();i++)cout<<PselectHospital[i]<<" ";
        bool checkM = false;
        int counttemp=0;
        for(int i=0;i<PselectHospital.size();i++){
            if(PselectHospital[i])counttemp++;
        }
        if(counttemp==m) checkM=true;
        if(checkM)
        {int temp = calAllDistance(PselectHospital);//cout<<temp<<"\n";
        if(result > temp) {result = temp;return;}}
        return; 
    }
    PselectHospital.push_back(true);
    Backtracking(PselectHospital);
    PselectHospital.pop_back();PselectHospital.push_back(false);
    Backtracking(PselectHospital); return;
}

void Solve(){
    Backtracking(selectHospital);
    cout << result;
}

int main() {
    Input();
    Solve();
    return 0;
}