#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

struct DSU{
    int n; vector<int> p, r;
    DSU(int n):n(n),p(n+1),r(n+1,0){ for(int i=0;i<=n;i++) p[i]=i; }
    int find(int x){ return p[x]==x?x:p[x]=find(p[x]); }
    void unite(int a,int b){ a=find(a); b=find(b); if(a==b) return; if(r[a]<r[b]) swap(a,b); p[b]=a; if(r[a]==r[b]) r[a]++; }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    if(!(cin>>n)) return 0;
    cin>>m;
    DSU dsu(n);
    vector<vector<int>> enemies(n+1);
    for(int i=0;i<m;i++){
        char t; int p,q;
        cin>>t>>p>>q;
        if(t=='F') dsu.unite(p,q);
        else { enemies[p].push_back(q); enemies[q].push_back(p); }
    }
    for(int i=1;i<=n;i++){
        if(enemies[i].size()>=2){
            int base=enemies[i][0];
            for(size_t k=1;k<enemies[i].size();k++) dsu.unite(base,enemies[i][k]);
        }
    }
    unordered_set<int> roots;
    for(int i=1;i<=n;i++) roots.insert(dsu.find(i));
    cout<<roots.size()<<"\n";
    return 0;
}