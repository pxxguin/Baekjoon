#include <iostream>
#include <vector>
using namespace std;

struct BIT{
    int n; vector<int> t;
    BIT(int n):n(n),t(n+2,0){}
    void add(int i,int v){ for(;i<=n;i+=i&-i) t[i]+=v; }
    int kth(int k){
        int idx=0, step=1;
        while((step<<1)<=n) step<<=1;
        for(;step;step>>=1){
            int nxt=idx+step;
            if(nxt<=n && t[nxt]<k){ k-=t[nxt]; idx=nxt; }
        }
        return idx+1;
    }
};

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const int MAXV=2000000;
    int N; 
    if(!(cin>>N)) return 0;
    BIT bit(MAXV);
    while(N--){
        int T; int X; 
        cin>>T>>X;
        if(T==1) bit.add(X,1);
        else{
            int v=bit.kth(X);
            cout<<v<<"\n";
            bit.add(v,-1);
        }
    }
    return 0;
}