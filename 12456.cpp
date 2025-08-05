#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
using ll = long long;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin>>T;
    for(int tc=1;tc<=T;tc++){
        int N;
        ll K;
        cin>>N>>K;
        struct Coffee{ ll t,s,c; };
        vector<Coffee> v(N);
        for(int i=0;i<N;i++){
            cin>>v[i].c>>v[i].t>>v[i].s;
        }
        sort(v.begin(), v.end(), [](auto &a, auto &b){
            return a.t > b.t;
        });
        ll prev = K;
        ll D_rem = K;
        priority_queue<pair<ll,ll>> pq;
        ll total = 0;
        bool done = false;
        for(int i=0;i<N;i++){
            ll d = v[i].t;
            ll L = prev - d;
            if(L > 0 && !pq.empty()){
                L = min(L, D_rem);
                while(L > 0 && !pq.empty()){
                    auto [s, cnt] = pq.top(); pq.pop();
                    ll r = cnt < L ? cnt : L;
                    total += s * r;
                    D_rem -= r;
                    L -= r;
                    if(cnt > r) pq.push({s, cnt - r});
                }
                if(D_rem == 0){
                    done = true;
                    break;
                }
            }
            prev = d;
            if(v[i].c > 0) pq.push({v[i].s, v[i].c});
        }
        if(!done && D_rem > 0){
            ll L = prev;
            L = min(L, D_rem);
            while(L > 0 && !pq.empty()){
                auto [s, cnt] = pq.top(); pq.pop();
                ll r = cnt < L ? cnt : L;
                total += s * r;
                D_rem -= r;
                L -= r;
                if(cnt > r) pq.push({s, cnt - r});
            }
        }
        cout<<"Case #"<<tc<<": "<<total;
        if(tc < T) cout<<"\n";
    }
    return 0;
}