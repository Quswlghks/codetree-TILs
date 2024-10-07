#include <iostream>
using namespace std;


int n,t;
int Map[400];

void rotateMap(){
    int temp = Map[2*n-1];
    for(int i=2*n-1;i>=1;i--){
        Map[i]=Map[i-1];
    }
    Map[0] = temp;
}

int main() {
    cin >> n>>t;
    for(int i=0;i<2*n;i++)cin>>Map[i];
    //0~n-1, n~2n-1
    for(int i=0;i<t;i++){
        rotateMap();
    }
    for(int i=0;i<n;i++)cout<<Map[i]<<" ";
    cout<<"\n";
    for(int i=n;i<2*n;i++)cout<<Map[i]<<" ";
    return 0;
}