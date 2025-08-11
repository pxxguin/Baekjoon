#include <iostream>
#include <vector>
using namespace std;

struct BIT{
    int n; vector<int> t;
    BIT(int n):n(n),t(n+1,0){}
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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N,K;
    if(!(cin>>N>>K)) return 0;
    BIT bit(N);
    for(int i=1;i<=N;i++) bit.add(i,1);
    int remain=N, idx=0;
    cout<<'<';
    for(int c=0;c<N;c++){
        idx=(idx+K-1)%remain;
        int pos=bit.kth(idx+1);
        cout<<pos;
        bit.add(pos,-1);
        remain--;
        if(c!=N-1) cout<<", ";
    }
    cout<<">\n";
    return 0;
}