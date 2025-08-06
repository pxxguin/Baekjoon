#include <iostream>
#include <vector>
using namespace std;

struct DSU {
    vector<int> p;
    DSU(int n): p(n+1) { for(int i = 1; i <= n; i++) p[i] = i; }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a != b) p[b] = a;
    }
};

struct Op { int t, u, v; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;
    vector<int> par(N+1);
    for (int i = 2; i <= N; i++) {
        cin >> par[i];
    }

    vector<Op> ops(N - 1 + Q);
    for (int i = 0; i < N - 1 + Q; i++) {
        int x;
        cin >> x;
        if (x == 0) {
            int b;
            cin >> b;
            ops[i] = {0, b, 0};
        } else {
            int c, d;
            cin >> c >> d;
            ops[i] = {1, c, d};
        }
    }

    DSU dsu(N);
    vector<bool> ans;
    for (int i = N - 1 + Q - 1; i >= 0; i--) {
        if (ops[i].t == 0) {
            dsu.unite(par[ops[i].u], ops[i].u);
        } else {
            ans.push_back(dsu.find(ops[i].u) == dsu.find(ops[i].v));
        }
    }

    for (int i = ans.size() - 1; i >= 0; i--) {
        cout << (ans[i] ? "YES\n" : "NO\n");
    }

    return 0;
}