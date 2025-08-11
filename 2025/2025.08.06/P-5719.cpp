#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;
using ll = long long;
const ll INF = numeric_limits<ll>::max();
struct Edge { int to; int cost; bool removed; };
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (true) {
        int N, M;
        cin >> N >> M;
        if (N == 0 && M == 0) break;
        int S, D;
        cin >> S >> D;
        vector<vector<Edge>> adj(N);
        vector<vector<pair<int,int>>> rev(N);
        for (int i = 0; i < M; i++) {
            int u, v, p;
            cin >> u >> v >> p;
            adj[u].push_back({v, p, false});
            rev[v].push_back({u, p});
        }
        vector<ll> dist(N, INF);
        dist[S] = 0;
        priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;
        pq.push({0, S});
        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d > dist[u]) continue;
            for (auto &e : adj[u]) {
                if (e.removed) continue;
                int v = e.to, w = e.cost;
                if (dist[v] > d + w) {
                    dist[v] = d + w;
                    pq.push({dist[v], v});
                }
            }
        }
        vector<bool> vis(N, false);
        queue<int> q;
        if (dist[D] < INF) {
            vis[D] = true;
            q.push(D);
        }
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (auto &pr : rev[v]) {
                int u = pr.first, w = pr.second;
                if (dist[u] + w == dist[v]) {
                    for (auto &e : adj[u]) {
                        if (e.to == v && e.cost == w && !e.removed) {
                            e.removed = true;
                        }
                    }
                    if (!vis[u]) {
                        vis[u] = true;
                        q.push(u);
                    }
                }
            }
        }
        fill(dist.begin(), dist.end(), INF);
        dist[S] = 0;
        while (!pq.empty()) pq.pop();
        pq.push({0, S});
        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d > dist[u]) continue;
            for (auto &e : adj[u]) {
                if (e.removed) continue;
                int v = e.to, w = e.cost;
                if (dist[v] > d + w) {
                    dist[v] = d + w;
                    pq.push({dist[v], v});
                }
            }
        }
        if (dist[D] == INF) {
            cout << -1 << "\n";
        } else {
            cout << dist[D] << "\n";
        }
    }
    return 0;
}