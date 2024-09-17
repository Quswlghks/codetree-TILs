#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll, ll> pll;
typedef tuple<int,int,int> tiii;
const int INF=1e9+1;
int dx[]={-1,0,1,0};
int dy[]={0,1,0,-1};

struct knight {
    int r, c;
    int h, w;
    int k; // 체력
    int dmg=0; // 기사가 받은 피해
};

int L, N, Q;
vector<vector<int>> board(41, vector<int>(41));
knight Knights[31];

bool possible(int s, int d) {
    // s번째 기사가 d 방향으로 움직일 수 있는지 리턴
    auto [r,c,h,w,k,dmg]=Knights[s];
    for(int x=r;x<r+h;x++) {
        for(int y=c;y<c+w;y++) {
            int nx=x+dx[d], ny=y+dy[d];
            // 격자 밖으로 나가거나 벽이 있는 경우 false를 리턴한다
            if(!(nx>=1 && nx<=L && ny>=1 && ny<=L)) return false;
            if(board[nx][ny]==2) return false;
        }
    }
    return true;
}

vector<int> move(int s, int d) {
    // 기사를 움직이는 함수
    vector<int> moved; // 연쇄적으로 움직이게 되는 기사 번호
    if(!Knights[s].k) return moved; // 사라진 기사는 명령을 내릴 수 없다
    vector<vector<int>> tmp(L+1, vector<int>(L+1));
    for(int i=1;i<=N;i++) {
        auto [r,c,h,w,k,dmg]=Knights[i];
        if(!k) continue;
        for(int x=r;x<r+h;x++) {
            for(int y=c;y<c+w;y++) tmp[x][y]=i;
        }
    }
    // 연쇄적으로 움직이게 될 기사를 체크
    queue<int> q;
    q.push(s);
    if(!possible(s,d)) return moved; // 본인이 움직일 수 없는 경우
    moved.push_back(s);
    while(!q.empty()) {
        int ns=q.front(); q.pop();
        auto [r,c,h,w,k,dmg]=Knights[ns];
        for(int x=r;x<r+h;x++) {
            for(int y=c;y<c+w;y++) {
                int nx=x+dx[d], ny=y+dy[d];
                if(nx>=1 && nx<=L && ny>=1 && ny<=L) {
                    if(!tmp[nx][ny]) continue;
                    if(tmp[nx][ny]!=ns) {
                        if(possible(tmp[nx][ny],d)) {
                            q.push(tmp[nx][ny]);
                            if(find(moved.begin(),moved.end(),tmp[nx][ny])==moved.end()) {
                                // moved 벡터에 같은 번호가 중복되지 않게 한다
                                moved.push_back(tmp[nx][ny]);
                            }
                        }
                        else {
                            moved.clear();
                            return moved;
                        }
                    }
                }
            }
        }
    }
    // moved에 포함된 기사들을 d방향으로 움직인다
    for(auto it : moved) Knights[it].r+=dx[d], Knights[it].c+=dy[d];
    return moved;
}

void trap_cnt(vector<int>& moved, int s, int d) {
    // 움직이게 된 기사들에게 피해를 주는 함수
    if(moved.empty()) return;
    for(auto idx : moved) {
        if(idx==s) continue; // 본인 제외
        auto [r,c,h,w,k,dmg]=Knights[idx];
        int damaged=0;
        for(int x=r;x<r+h;x++) {
            for(int y=c;y<c+w;y++) {
                if(board[x][y]==1) damaged++;
            }
        }
        if(damaged>=k) {
            Knights[idx].k=0;
        }
        else {
            Knights[idx].k-=damaged;
            Knights[idx].dmg+=damaged;
        }
    }
}

int main() {
    //freopen("input.txt","r",stdin);
    cin>>L>>N>>Q;
    for(int i=1;i<=L;i++) {
        for(int j=1;j<=L;j++) cin>>board[i][j];
    }
    for(int i=1;i<=N;i++) {
        cin>>Knights[i].r>>Knights[i].c>>Knights[i].h>>Knights[i].w>>Knights[i].k;
    }
    while(Q--) {
        int s, d; cin>>s>>d;
        vector<int> moved=move(s,d);
        trap_cnt(moved,s,d);
    }
    int ret=0;
    for(int i=1;i<=N;i++) {
        if(Knights[i].k) ret+=Knights[i].dmg;
    }
    cout<<ret;
    return 0;
}