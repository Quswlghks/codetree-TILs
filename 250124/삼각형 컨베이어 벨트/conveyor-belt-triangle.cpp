#include <iostream>

using namespace std;

int n, t;
int o[600];

int l[200];
int r[200];
int d[200];

int main() {
    cin >> n >> t;

    for (int i = 0; i < 3*n; i++) cin >> o[i];

    t=t%(3*n);

    for (int i = 0; i < n; i++) l[i]=o[(3*n)-t+i >= 3*n ? ((3*n)-t+i)%(3*n) : (3*n)-t+i];
    for (int i = 0; i < n; i++) r[i]=o[(4*n)-t+i >= 3*n ? ((4*n)-t+i)%(3*n) : (4*n)-t+i];
    for (int i = 0; i < n; i++) d[i]=o[(5*n)-t+i >= 3*n ? ((5*n)-t+i)%(3*n) : (5*n)-t+i];

    for (int i = 0; i < n; i++) cout << l[i] <<" ";
    cout<<"\n";
    for (int i = 0; i < n; i++) cout << r[i]<<" ";
    cout<<"\n";
    for (int i = 0; i < n; i++) cout << d[i]<<" ";
    return 0;
}
