#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
using ll = long long;

struct DSU {
    vector<int> p, sz;
    vector<map<int,int>> cnt;
    vector<int> distinct;
    DSU(int n, const vector<int>& color): p(n+1), sz(n+1,1), cnt(n+1), distinct(n+1,0) {
        for(int i=1;i<=n;i++){
            p[i]=i;
            cnt[i][color[i]] = 1;
            distinct[i] = 1;
        }
    }
    int find(int x){
        return p[x]==x?x:p[x]=find(p[x]);
    }
    void unite(int a, int b){
        a = find(a);
        b = find(b);
        if(a==b) return;
        if(sz[a] < sz[b]) swap(a,b);
        for(auto &kv: cnt[b]){
            int col = kv.first;
            int c = kv.second;
            auto it = cnt[a].find(col);
            if(it==cnt[a].end()){
                cnt[a][col] = c;
                distinct[a]++;
            } else {
                it->second += c;
            }
        }
        cnt[b].clear();
        p[b] = a;
        sz[a] += sz[b];
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;
    vector<int> parent(N+1);
    for(int i=2;i<=N;i++) cin >> parent[i];
    vector<int> color(N+1);
    for(int i=1;i<=N;i++) cin >> color[i];
    int totalQ = N + Q - 1;
    vector<pair<int,int>> query(totalQ);
    for(int i=0;i<totalQ;i++){
        cin >> query[i].first >> query[i].second;
    }
    DSU dsu(N, color);
    vector<int> answers;
    answers.reserve(Q);
    for(int i=totalQ-1;i>=0;i--){
        int tp = query[i].first;
        int a = query[i].second;
        if(tp == 2){
            int r = dsu.find(a);
            answers.push_back(dsu.distinct[r]);
        } else {
            int p = parent[a];
            dsu.unite(a, p);
        }
    }
    for(int i=Q-1;i>=0;i--){
        cout << answers[i] << "\n";
    }
    return 0;
}