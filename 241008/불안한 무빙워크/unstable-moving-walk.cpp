#include <iostream>
using namespace std;

int n,k;
int safe[200];
bool man[101];

void Input(){
    cin >> n >> k;
    for(int i=0;i<2*n;i++) cin >> safe[i];
}

void rotate(){
    int temp = safe[2*n-1];
    for(int i=2*n-1;i>=1;i--) safe[i]=safe[i-1];
    safe[0]=temp;

    for(int i=0;i<n;i++){
        if(man[i]){
            man[i]=false;
            if((i+1)!=n){man[i+1]=true; i++;}
        }
    }
}

void move(){
    for(int i=0;i<n;i++){
        if(man[i]){
            if(safe[i+1]==0) continue;
            if(man[i+1]) continue;
            if(i+1==n) man[i]=false;
            man[i]=false;
            man[i+1]=true;
            safe[i+1]--;
        }
    }
}

void takeOne(){
    if(man[0]==false && safe[0]!=0){
        man[0]=true;
        safe[0]--;
    }
}

bool isSafe(){
    int countNonSafe = 0;
    for(int i=0;i<2*n;i++){
        if(safe[i]==0) countNonSafe++;
    }
    if(countNonSafe>=k) return false;
    return true;
}

void printStatus(){
    for(int i=0;i<n;i++) cout<<man[i]<<" ";
    cout<<"\nsafe 0~n-1\n";
    for(int i=0;i<n;i++) cout<<safe[i]<<" ";
    cout<<"\nsafe n~2n-1\n";
    for(int i=2*n-1;i>=n;i--) cout<<safe[i]<<" ";
    cout<<"\n\n";
}

void Solve(){
    int result = 1;
    while(1){
        rotate();
        move(); if(!isSafe()) break;
        takeOne(); if(!isSafe()) break;
        result++; 
    }
    cout<<result;
}



int main() {
    Input();
    Solve();
    return 0;
}