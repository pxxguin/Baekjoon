#include <iostream>
#include <vector>
#include <stack>
#include <utility>
#include <tuple>
#include <algorithm>
using namespace std;
using ll = long long;

int findp(int x, vector<int>& p) {
    return p[x] == x ? x : p[x] = findp(p[x], p);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> p(n+1), sz(n+1, 1), grp(n+1);
    for (int i = 1; i <= n; i++) {
        p[i] = i;
        grp[i] = i;
    }
    int next_id = n;
    vector<pair<int,ll>> events;
    vector<ll> personal(n+1, 0);
    vector<vector<int>> children(2*n + 2);

    for (int _ = 0; _ < m; _++) {
        int t; cin >> t;
        if (t == 1) {
            int x, y; cin >> x >> y;
            int u = findp(x, p), v = findp(y, p);
            next_id++;
            children[next_id].push_back(grp[u]);
            children[next_id].push_back(grp[v]);
            p[v] = u;
            sz[u] += sz[v];
            grp[u] = next_id;
        } else {
            int x; ll c; cin >> x >> c;
            int u = findp(x, p);
            int gid = grp[u];
            ll share = c / sz[u];
            personal[x] += c;
            events.emplace_back(gid, share);
        }
    }

    int root = grp[findp(1, p)];
    int total_nodes = next_id;
    vector<int> in(total_nodes+2), out(total_nodes+2);
    int timer = 1;
    stack<pair<int,int>> st;
    st.push({root, 0});
    while (!st.empty()) {
        int node = st.top().first;
        int &idx = st.top().second;
        if (idx == 0) in[node] = timer++;
        if (idx < (int)children[node].size()) {
            int c = children[node][idx++];
            st.push({c, 0});
        } else {
            out[node] = timer - 1;
            st.pop();
        }
    }

    vector<ll> diff(timer+2, 0);
    for (auto &e : events) {
        int id = e.first;
        ll s = e.second;
        diff[in[id]]   -= s;
        diff[out[id]+1] += s;
    }
    for (int i = 1; i <= timer; i++) {
        diff[i] += diff[i-1];
    }

    vector<pair<ll,int>> pos, neg;
    for (int i = 1; i <= n; i++) {
        ll net = personal[i] + diff[in[i]];
        if (net > 0) pos.emplace_back(net, i);
        else if (net < 0) neg.emplace_back(-net, i);
    }

    vector<tuple<int,int,ll>> ops;
    int i = 0, j = 0;
    while (i < (int)neg.size() && j < (int)pos.size()) {
        ll d = min(neg[i].first, pos[j].first);
        ops.emplace_back(neg[i].second, pos[j].second, d);
        neg[i].first -= d;
        pos[j].first -= d;
        if (neg[i].first == 0) i++;
        if (pos[j].first == 0) j++;
    }

    if ((int)ops.size() > n) {
        cout << -1 << "\n";
    } else {
        cout << ops.size() << "\n";
        for (auto &o : ops) {
            int x, y; ll c;
            tie(x, y, c) = o;
            cout << x << " " << y << " " << c << "\n";
        }
    }
    return 0;
}