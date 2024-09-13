#include <iostream>

using namespace std;

int n;
pair<int,int> tp[15];
int isUsed[15];
int result=0;

void Input(){
    cin >> n;
    for(int i =0 ; i<n;i++){
        cin >> tp[i].first >>tp[i].second;
    }
}

int isVal(const int isUsed[]){
    //유효한지 확인하고 그렇다면 얼마나 돈주는지.
    int temp[15]; int result =0;
    for(int i =0;i<15;i++) temp[i] =0;
    for(int i=0;i<n;i++){
        if(isUsed[i]==1){ //일하면 i~i+tp[i].first-1까지 1을 더해
            for(int j = i; j<i+tp[i].first; j++) temp[j]++;
        }
    }

    for(int i=0;i<n;i++){ //겹치는거 존재
        if(temp[i]>1) return -1;
    }

    for(int i =0;i<n;i++){
        //cout<<"\ntemp: "<<temp[i]<<"\n";
        switch(temp[i]){
            case 0:
                //아무일도 안함.
            break;
            case 1://i~i+tp[i].first-1까지 일하고 tp[i].second 돈 받음
                result+=tp[i].second;
                i = i+tp[i].first;
            break;
        }
    }
    //cout<<"\nresult : "<<result<<"\n";

    return result;
}

void backtracking(int i, int what, const int isUsed[]){
    int tempUsed[15];
    for(int i=0;i<15;i++) tempUsed[i]=isUsed[i];
    tempUsed[i] = what;

    if(i==n-1){
        for(int asdf =0; asdf <= i; asdf++){
            //cout << tempUsed[asdf]<<" ";
        }
        if(isVal(tempUsed) > result){
             result = isVal(tempUsed);
             return;
        }
        return;
    }
    
    backtracking(i+1, 0, tempUsed);
    backtracking(i+1, 1, tempUsed);
}

void Solve(){
    backtracking(0, 0, isUsed);
    backtracking(0, 1, isUsed);

    cout<<result;
}

int main() {
    Input();
    Solve();
}