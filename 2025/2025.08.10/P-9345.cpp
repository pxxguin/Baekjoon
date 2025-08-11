#include <iostream>
#include <vector>
#include <utility>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; 
    if(!(cin>>T)) return 0;
    while(T--){
        int N,K; cin>>N>>K;
        int size=1; while(size<N) size<<=1;
        vector<pair<int,int>> seg(2*size, {1000000007,-1000000007});
        for(int i=0;i<N;i++) seg[size+i]={i,i};
        for(int i=size-1;i>=1;i--){
            auto L=seg[i<<1], R=seg[i<<1|1];
            seg[i]={min(L.first,R.first), max(L.second,R.second)};
        }
        auto set_pos = [&](int pos, int val){
            int i=size+pos;
            seg[i]={val,val};
            for(i>>=1;i;i>>=1){
                auto L=seg[i<<1], R=seg[i<<1|1];
                seg[i]={min(L.first,R.first), max(L.second,R.second)};
            }
        };
        auto get = [&](int l, int r){
            l+=size; r+=size;
            int mn=1000000007, mx=-1000000007;
            while(l<=r){
                if(l&1){ mn=min(mn,seg[l].first); mx=max(mx,seg[l].second); l++; }
                if(!(r&1)){ mn=min(mn,seg[r].first); mx=max(mx,seg[r].second); r--; }
                l>>=1; r>>=1;
            }
            return pair<int,int>(mn,mx);
        };
        while(K--){
            int Q,A,B; cin>>Q>>A>>B;
            if(Q==0){
                int va=seg[size+A].first, vb=seg[size+B].first;
                set_pos(A,vb);
                set_pos(B,va);
            }else{
                auto p=get(A,B);
                cout<<(p.first==A && p.second==B ? "YES\n" : "NO\n");
            }
        }
    }
    return 0;
}