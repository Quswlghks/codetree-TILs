#include <iostream>
#include <vector>

using namespace std;

long long n;
vector<long long> arr;
long long temp;

long long boss;
long long team;

long long result;

int main() {
    cin >> n;
    for(int i =0;i<n;i++){
        cin >> temp;
        arr.push_back(temp);
    }
    cin >> boss >> team;

    result+=n;

    for(int i =0;i<n;i++){
        arr[i]-=boss;
        if(arr[i]<=0) continue;
        if(arr[i]%team == 0){
            result+=arr[i]/team;
        }else{
            result+=(arr[i]/team+1);
        }
    }

    cout << result;


    return 0;
}