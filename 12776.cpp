#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<ll> a(n), b(n);
    for(int i = 0; i < n; i++) cin >> a[i] >> b[i];
    vector<int> S, T;
    for(int i = 0; i < n; i++){
        if (b[i] >= a[i]) S.push_back(i);
        else T.push_back(i);
    }
    sort(S.begin(), S.end(), [&](int i, int j){ return a[i] < a[j]; });
    sort(T.begin(), T.end(), [&](int i, int j){ return b[i] > b[j]; });
    ll G = 0, R = 0;
    for(int i : S){
        R = max(R, a[i] - G);
        G += b[i] - a[i];
    }
    for(int i : T){
        R = max(R, a[i] - G);
        G += b[i] - a[i];
    }
    cout << (R < 0 ? 0 : R);
    return 0;
}