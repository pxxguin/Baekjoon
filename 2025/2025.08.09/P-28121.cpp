#include <iostream>
#include <vector>
using namespace std;

struct DSU {
    int n;
    vector<int> p, sz, par, bad;
    long long badsum;
    DSU(int n): n(n), p(n+1), sz(n+1,1), par(n+1,0), bad(n+1,0), badsum(0) { for(int i=1;i<=n;i++) p[i]=i; }
    pair<int,int> findp(int x){
        if(p[x]==x) return {x,0};
        auto pr = findp(p[x]);
        p[x]=pr.first;
        par[x] ^= pr.second;
        return {p[x], par[x]};
    }
    void unite(int u, int v){
        auto A=findp(u), B=findp(v);
        int ru=A.first, rv=B.first;
        int pu=A.second, pv=B.second;
        if(ru==rv){
            if((pu^pv)==0 && !bad[ru]){
                bad[ru]=1;
                badsum+=sz[ru];
            }
            return;
        }
        if(sz[ru]<sz[rv]){ swap(ru,rv); swap(pu,pv); }
        long long old = (bad[ru]?sz[ru]:0) + (bad[rv]?sz[rv]:0);
        p[rv]=ru;
        par[rv]=pu^pv^1;
        sz[ru]+=sz[rv];
        bad[ru] = bad[ru] | bad[rv];
        long long neu = bad[ru]?sz[ru]:0;
        badsum += neu - old;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N,Q;
    if(!(cin>>N>>Q)) return 0;
    DSU dsu(N);
    while(Q--){
        int a,b; cin>>a>>b;
        dsu.unite(a,b);
        cout<<dsu.badsum<<"\n";
    }
    return 0;
}