#include <iostream>
#include <vector>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const long long MOD=1000000007LL;
    int N,M,K;
    if(!(cin>>N>>M>>K)) return 0;
    int Q=M+K;
    int size=1;
    while(size<N) size<<=1;
    vector<long long> t(2*size,1);
    for(int i=1;i<=N;i++){
        long long x; cin>>x;
        t[size+i-1]=x%MOD;
    }
    for(int i=size-1;i>=1;i--) t[i]=(t[i<<1]*t[i<<1|1])%MOD;
    while(Q--){
        int a; long long b,c; cin>>a>>b>>c;
        if(a==1){
            int i=size+(int)b-1;
            t[i]=c%MOD;
            i>>=1;
            while(i){
                t[i]=(t[i<<1]*t[i<<1|1])%MOD;
                i>>=1;
            }
        }else{
            int l=(int)b, r=(int)c;
            if(l>r) swap(l,r);
            long long res=1;
            l+=size-1; r+=size-1;
            while(l<=r){
                if(l&1) res=(res*t[l++])%MOD;
                if(!(r&1)) res=(res*t[r--])%MOD;
                l>>=1; r>>=1;
            }
            cout<<res<<"\n";
        }
    }
    return 0;
}