#include <iostream>
#include <vector>
using namespace std;

int N;
vector<int> A;
int add, sub, multi, divide;

int Max = -1000000000;
int Min = 1000000000;

void Input() {
    cin >> N;
    A.resize(N);
    for(int i = 0; i < N; i++) cin >> A[i];
    cin >> add >> sub >> multi >> divide;
}

void Solve(int index, int result) {
    if (index == N) {
        Max = max(Max, result);
        Min = min(Min, result);
        return;
    }

    if (add > 0) {
        add--;
        Solve(index + 1, result + A[index]);
        add++;
    }
    if (sub > 0) {
        sub--;
        Solve(index + 1, result - A[index]);
        sub++;
    }
    if (multi > 0) {
        multi--;
        Solve(index + 1, result * A[index]);
        multi++;
    }
    if (divide > 0) {
        divide--;
        // C++14 기준 나눗셈 처리
        int divided = result < 0 ? -(-result / A[index]) : result / A[index];
        Solve(index + 1, divided);
        divide++;
    }
}

int main() {
    Input();
    Solve(1, A[0]);  // 첫 번째 숫자를 결과값으로 시작
    cout << Min << " " << Max;
    return 0;
}