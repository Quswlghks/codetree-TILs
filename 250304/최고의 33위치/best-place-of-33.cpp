#include <iostream>

using namespace std;

int N;
int grid[20][20];

int main() {
    cin >> N;
    int result=-1;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> grid[i][j];
        }
    }

    for (int i = 0; i < N-3; i++) {
        for (int j = 0; j < N-3; j++) {
            int temp=0;
            for(int a=0;a<3;a++){
                for(int b=0;b<3;b++){
                    if(grid[i+a][j+b]) temp++;
                }
            }
            if(result<temp) result=temp;
        }
    }
    cout<<result;
    return 0;
}
