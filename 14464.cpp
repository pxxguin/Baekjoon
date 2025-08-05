#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
struct Cow { int a, b; };
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int C, N;
    cin >> C >> N;
    multiset<int> chickens;
    for (int i = 0, t; i < C; i++) {
        cin >> t;
        chickens.insert(t);
    }
    vector<Cow> cows(N);
    for (int i = 0; i < N; i++) {
        cin >> cows[i].a >> cows[i].b;
    }
    sort(cows.begin(), cows.end(), [](const Cow &x, const Cow &y) {
        return x.b < y.b;
    });
    int ans = 0;
    for (const auto &cow : cows) {
        auto it = chickens.lower_bound(cow.a);
        if (it != chickens.end() && *it <= cow.b) {
            ++ans;
            chickens.erase(it);
        }
    }
    cout << ans;
    return 0;
}