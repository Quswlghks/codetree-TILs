#include <iostream>

using namespace std;

int n, m, q;
int a[100][100];

void printa(){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cout << a[i][j] << " ";
        }cout<<"\n";
    }cout<<"\n";
}

void move(int r, bool d){
    if(!d){//R
        int temp = a[r][0];
        for(int i=0; i<m-1; i++){
            a[r][i] = a[r][i+1];
        }
        a[r][m-1]=temp;
    }else{//L
        int temp = a[r][m-1];
        for(int i=m-1; i>0; i--){
            a[r][i] = a[r][i-1];
        }
        a[r][0]=temp;
    }
}

bool checkVal(int aa, int bb){
    for(int i=0;i<m;i++){
        if(a[aa][i]==a[bb][i]) return true;
    }return false;
}

void wind(int r, bool d){
    r -= 1;
    move(r, d);
    bool flag = d;
    int originr = r;
    while(1){
        if(r==0) break;
        if(!checkVal(r,r-1)) break;
        d=!d;
        move(r-1,d);r-=1;
    }
    d=flag; r=originr;
    while(1){
        if(r==n-1) break;
        if(!checkVal(r,r+1)) break;
        d=!d;
        move(r+1,d);r+=1;
    }
}

int main() {
    cin >> n >> m >> q;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }

    for (int i = 0; i < q; i++) {
        int r;
        char d;
        cin >> r >> d;
        bool dir = false;
        if(d=='L') dir=true; else dir=false;
        wind(r,dir);
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cout << a[i][j] << " ";
        }cout<<"\n";
    }

    return 0;
}
