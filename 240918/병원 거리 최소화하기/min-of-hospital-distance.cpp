#include <iostream>
#include <cmath>
#include <vector>
#include <climits> // INT_MAX를 사용하기 위해 추가

using namespace std;

int Map[51][51];
// 빈칸0, 사람1, 병원2
int n,m;
vector<pair<int,int>> pointHospital;
vector<pair<int,int>> pointHuman;
int result = INT_MAX; // 수정: 초기값을 INT_MAX로 변경

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

int calAllDistance(const vector<bool>& PselectHospital){
    int returnresult = 0;
    for(int i=0;i<pointHuman.size();i++){
        int minDis = INT_MAX; // 수정: 각 사람마다 최소 거리를 INT_MAX로 초기화
        int x1 = pointHuman[i].first;
        int y1 = pointHuman[i].second;
        for(int j=0;j<pointHospital.size();j++){
            if(PselectHospital[j]){
                int x2 = pointHospital[j].first;
                int y2 = pointHospital[j].second;
                int temp = calDistance(x1,y1,x2,y2);
                if(temp < minDis) minDis = temp;
            }
        }
        returnresult += minDis; // 수정: 각 사람의 최소 거리를 더함
    }
    return returnresult;
}

void Backtracking(int index, int count, vector<bool>& PselectHospital){
    // 수정: 백트래킹 함수의 매개변수와 종료 조건 변경
    if(count == m){
        int temp = calAllDistance(PselectHospital);
        if(result > temp) result = temp;
        return;
    }
    if(index >= pointHospital.size()) return; // 수정: 모든 병원을 고려했을 때 종료

    // 현재 병원 선택
    PselectHospital[index] = true;
    Backtracking(index + 1, count + 1, PselectHospital);
    
    // 현재 병원 선택하지 않음
    PselectHospital[index] = false;
    Backtracking(index + 1, count, PselectHospital);
}

void Solve(){
    vector<bool> selectHospital(pointHospital.size(), false);
    Backtracking(0, 0, selectHospital); // 수정: 백트래킹 함수 호출 방식 변경
    cout << result;
}

int main() {
    Input();
    Solve();
    return 0;
}