#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int maxProfit(int n, vector<pair<int, int>>& jobs) {
    vector<int> dp(n + 1, 0);

    for (int i = n - 1; i >= 0; i--) {
        if (i + jobs[i].first > n) {
            dp[i] = dp[i + 1];
        } else {
            dp[i] = max(dp[i + 1], jobs[i].second + dp[i + jobs[i].first]);
        }
    }

    return dp[0];
}

int main() {
    int n;
    cin >> n;

    vector<pair<int, int>> jobs(n);
    for (int i = 0; i < n; i++) {
        cin >> jobs[i].first >> jobs[i].second;
    }

    cout << maxProfit(n, jobs) << endl;

    return 0;
}