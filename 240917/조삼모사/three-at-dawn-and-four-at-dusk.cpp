#include <algorithm>
#include <iostream>
#include <cstdlib>
using namespace std;

int n;
int P[20][20];
int result = 1000000;

void Input(){
    cin >> n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin >> P[i][j];
        }
    }
}
void Solve();
int cal(bool* day);
void recur(bool* day, int index);
int main() {
    Input();
    Solve();
    return 0;
}

int cal(bool* day){
    //day cal
    int dayVal = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(day[i]&&day[j]){
                dayVal+=P[i][j];
            }
        }
    }
    //night cal
    int nightVal = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if((!day[i])&&(!day[j])){
                nightVal+=P[i][j];
            }
        }
    }
    return abs(dayVal-nightVal);
}

void recur(bool* day, int index){
    if(index==n-1){
        int dayNum =0;
        for(int i=0;i<n;i++){if(day[i]) dayNum++;}
        if(dayNum!=n/2) return;
        result=min(result, cal(day)); return;
        }
    day[index] = true;
    recur(day, index+1);
    day[index] = false;
    recur(day, index+1);
    return;
}

void Solve(){
    bool day[20] = {true};
    recur(day, 0);
    cout << result;
    return;
}