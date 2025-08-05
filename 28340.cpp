#include <iostream>
#include <vector>
#include <queue>
#include <functional>
using namespace std;
using ll = long long;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int N, K;
        cin >> N >> K;
        vector<ll> freq(N);
        for (int i = 0; i < N; i++) cin >> freq[i];
        priority_queue<ll, vector<ll>, greater<ll>> pq(freq.begin(), freq.end());
        int mod = (N - 1) % (K - 1);
        int dummies = (K - 1 - mod) % (K - 1);
        for (int i = 0; i < dummies; i++) pq.push(0);
        ll total_cost = 0;
        while (pq.size() > 1) {
            ll sum = 0;
            for (int i = 0; i < K; i++) {
                sum += pq.top();
                pq.pop();
            }
            total_cost += sum;
            pq.push(sum);
        }
        cout << total_cost << "\n";
    }
    return 0;
}