#include <iostream>
using namespace std;

int n;
int Map[20][20];
int Max = -1;

int main() {
    cin >> n;
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) cin>>Map[i][j];
    for(int i=1;i<=n-2;i++) {for(int j=1;j<=n-2;j++) {
        int temp = Map[i-1][j-1]+Map[i-1][j]+Map[i-1][j+1]+
        Map[i][j-1]+Map[i][j]+Map[i][j+1]+
        Map[i+1][j-1]+Map[i+1][j]+Map[i+1][j+1];
        if(temp > Max) Max = temp;
    }}
    cout << Max;
    return 0;
}