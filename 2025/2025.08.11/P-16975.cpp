#include <iostream>
#include <vector>
using namespace std;

struct BIT{
    int n; vector<long long> t;
    BIT(int n):n(n),t(n+2,0){}
    void add(int i,long long v){ for(; i<=n; i+=i&-i) t[i]+=v; }
    long long sum(int i){ long long s=0; for(; i>0; i-=i&-i) s+=t[i]; return s; }
};

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N; 
    if(!(cin>>N)) return 0;
    vector<long long> A(N+1);
    for(int i=1;i<=N;i++) cin>>A[i];
    int M; cin>>M;
    BIT bit(N);
    while(M--){
        int type; cin>>type;
        if(type==1){
            int i,j; long long k; cin>>i>>j>>k;
            bit.add(i,k);
            if(j+1<=N) bit.add(j+1,-k);
        }else{
            int x; cin>>x;
            cout<<A[x]+bit.sum(x)<<"\n";
        }
    }
    return 0;
}