#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    cin>>n>>m;
    vector<vector<pair<int,int>>> adj(n+1), rev(n+1);
    vector<int> indegree(n+1);
    vector<int> eu(m), ev(m), ew(m);
    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
        rev[v].push_back({u,w});
        indegree[v]++;
        eu[i]=u; ev[i]=v; ew[i]=w;
    }
    int s,t;
    cin>>s>>t;
    queue<int> q;
    for(int i=1;i<=n;i++) if(indegree[i]==0) q.push(i);
    vector<int> topo;
    topo.reserve(n);
    while(!q.empty()){
        int x=q.front(); q.pop();
        topo.push_back(x);
        for(auto &p:adj[x]){
            if(--indegree[p.first]==0) q.push(p.first);
        }
    }
    vector<int> dist1(n+1,-1);
    dist1[s]=0;
    for(int x:topo){
        if(dist1[x]>=0){
            for(auto &p:adj[x]){
                int y=p.first, c=p.second;
                if(dist1[y]<dist1[x]+c) dist1[y]=dist1[x]+c;
            }
        }
    }
    vector<int> dist2(n+1,-1);
    dist2[t]=0;
    for(auto it=topo.rbegin(); it!=topo.rend(); ++it){
        int x=*it;
        if(dist2[x]>=0){
            for(auto &p:rev[x]){
                int y=p.first, c=p.second;
                if(dist2[y]<dist2[x]+c) dist2[y]=dist2[x]+c;
            }
        }
    }
    int answer=dist1[t];
    int count=0;
    for(int i=0;i<m;i++){
        int u=eu[i], v=ev[i], w=ew[i];
        if(dist1[u]>=0 && dist2[v]>=0 && dist1[u]+w+dist2[v]==answer) count++;
    }
    cout<<answer<<"\n"<<count;
    return 0;
}