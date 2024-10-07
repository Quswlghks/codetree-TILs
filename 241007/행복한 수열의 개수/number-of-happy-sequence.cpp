#include <iostream>
using namespace std;

int n,m;
int Map[100][100]; int result;

int main() {
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin >> Map[i][j];
        }
    }
    for(int i=0;i<n;i++){
        int count = 1;
        for(int j=1;j<n;j++){
            if(count==m) {result++; break;}
            if(Map[i][j]==Map[i][j-1]){ count++; if(count==m) {result++; break;}}
            else count = 1;
        }
    }

    for(int i=0;i<n;i++){
        int count = 1;
        for(int j=1;j<n;j++){
            if(count==m) {result++; break;}
            if(Map[j][i]==Map[j-1][i]){ count++; if(count==m) {result++; break;}}
            else count = 1;
        }
    }
    cout << result;
    return 0;
}