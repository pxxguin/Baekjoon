#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int find_set(int x, vector<int>& p, vector<ll>& w){
    if(p[x]==x) return x;
    int r = find_set(p[x], p, w);
    w[x] += w[p[x]];
    return p[x] = r;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while(true){
        int N, M;
        if(!(cin>>N>>M)) return 0;
        if(N==0 && M==0) break;
        vector<int> p(N+1);
        vector<ll> w(N+1, 0);
        for(int i=1;i<=N;i++) p[i]=i;
        for(int i=0;i<M;i++){
            char op;
            cin>>op;
            if(op=='!'){
                int a,b; ll d;
                cin>>a>>b>>d;
                int ra = find_set(a, p, w);
                int rb = find_set(b, p, w);
                if(ra!=rb){
                    ll da = w[a];
                    ll db = w[b];
                    p[rb] = ra;
                    w[rb] = d + da - db;
                }
            }else{
                int a,b;
                cin>>a>>b;
                int ra = find_set(a, p, w);
                int rb = find_set(b, p, w);
                if(ra!=rb) cout<<"UNKNOWN\n";
                else cout<< (w[b] - w[a]) <<"\n";
            }
        }
    }
    return 0;
}