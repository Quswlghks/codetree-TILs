#include <iostream>
#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;

int n;
int Gigu[20][20];

struct Student{
    int id;
    int love[4];
};

Student student[401]; // ID를 인덱스로 사용하기 위해 크기를 401로 설정

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

void Input(){
    cin >> n;
    for(int i = 0; i < n * n; i++){
        int n0, n1, n2, n3, n4;
        cin >> n0 >> n1 >> n2 >> n3 >> n4;
        student[i].id = n0;
        student[i].love[0] = n1;
        student[i].love[1] = n2;
        student[i].love[2] = n3;
        student[i].love[3] = n4;
    }
}

bool isIn(int x, int y){
    return x >= 0 && y >= 0 && x < n && y < n;
}

void place(int k){
    int Sid = student[k].id;
    int l1 = student[k].love[0];
    int l2 = student[k].love[1];
    int l3 = student[k].love[2];
    int l4 = student[k].love[3];

    vector<tuple<int, int, int, int>> infoList; // (numLove, numBin, x, y)

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(Gigu[i][j] != 0) continue;
            int nLove = 0;
            int nBin = 0;
            for(int z = 0; z < 4; z++){
                int nx = i + dx[z];
                int ny = j + dy[z];
                if(!isIn(nx, ny)) continue;
                if(Gigu[nx][ny] == l1 || Gigu[nx][ny] == l2 || Gigu[nx][ny] == l3 || Gigu[nx][ny] == l4)
                    nLove++;
                if(Gigu[nx][ny] == 0)
                    nBin++;
            }
            infoList.push_back(make_tuple(-nLove, -nBin, i, j)); // 음수로 저장하여 최대값을 우선하도록
        }
    }

    sort(infoList.begin(), infoList.end());

    int x = get<2>(infoList[0]);
    int y = get<3>(infoList[0]);
    Gigu[x][y] = Sid;
}

int calScore(){
    int result = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            int Sid = Gigu[i][j];
            int temp;
            for(int z=0;z<n*n;z++){
                if(student[z].id == Sid)  {temp = z;break;}
            }
            int numLove = 0;
            for(int z = 0; z < 4; z++){
                int nx = i + dx[z];
                int ny = j + dy[z];
                if(!isIn(nx, ny)) continue;
                int neighbor = Gigu[nx][ny];
                if(neighbor == student[temp].love[0] || neighbor == student[temp].love[1] ||
                   neighbor == student[temp].love[2] || neighbor == student[temp].love[3])
                    numLove++;
            }
            if(numLove == 0)
                result += 0;
            else if(numLove == 1)
                result += 1;
            else if(numLove == 2)
                result += 10;
            else if(numLove == 3)
                result += 100;
            else if(numLove == 4)
                result += 1000;
        }
    }
    return result;
}

void Solve(){
    for(int i = 0; i < n * n; i++){
        place(i);
    }
    cout << calScore();
}

int main() {
    Input();
    Solve();
    return 0;
}