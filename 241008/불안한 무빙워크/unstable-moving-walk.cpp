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

    for(int i=n-1;i>=1;i--) man[i]=man[i-1];
    man[0]=false;
    if(man[n-1]) man[n-1]=false; 
}

void move(){
    for(int i=n-2;i>=0;i--){
        if(man[i] && !man[i+1] && safe[i+1]>0){
            man[i]=false;
            man[i+1]=true;
            safe[i+1]--;
        }
    }
    if(man[n-1]) man[n-1]=false; // n번 칸에 도달한 사람은 내려야 함
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
    int result = 0;
    while(1){
        result++; 
        rotate(); //printStatus();
        move(); //printStatus();
        if(!isSafe()) break;
        takeOne(); //printStatus(); 
        if(!isSafe()) break;
        //cout<<"iterated!\n\n";
    }
    //printStatus();
    cout<<result;
}



int main() {
    Input();
    Solve();
    return 0;
}