#include <iostream>
#include <queue>
#include <vector>
#include <functional>
using namespace std;
using ll = long long;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int K;
        cin >> K;
        priority_queue<ll, vector<ll>, greater<ll>> pq;
        for (int i = 0; i < K; i++) {
            ll x;
            cin >> x;
            pq.push(x);
        }
        ll res = 0;
        while (pq.size() > 1) {
            ll a = pq.top(); pq.pop();
            ll b = pq.top(); pq.pop();
            ll s = a + b;
            res += s;
            pq.push(s);
        }
        cout << res << "\n";
    }
    return 0;
}