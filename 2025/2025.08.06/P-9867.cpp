#include <iostream>
#include <vector>
#include <limits>
using namespace std;
using ll = long long;
const ll NINF = numeric_limits<ll>::min() / 2;
struct Node { ll m[2][2]; };
int N, D;
vector<Node> seg;
Node combine(const Node &A, const Node &B) {
    Node C;
    for(int i=0;i<2;i++) for(int j=0;j<2;j++){
        ll v = NINF;
        for(int k=0;k<2;k++){
            v = max(v, A.m[i][k] + B.m[k][j]);
        }
        C.m[i][j] = v;
    }
    return C;
}
void build(int idx, int l, int r, const vector<ll> &a) {
    if(l==r){
        ll v = a[l];
        seg[idx].m[0][0]=0;    seg[idx].m[0][1]=v;
        seg[idx].m[1][0]=0;    seg[idx].m[1][1]=NINF;
    } else {
        int m=(l+r)/2;
        build(idx*2,l,m,a);
        build(idx*2+1,m+1,r,a);
        seg[idx]=combine(seg[idx*2],seg[idx*2+1]);
    }
}
void update(int idx, int l, int r, int pos, ll v){
    if(l==r){
        seg[idx].m[0][0]=0;    seg[idx].m[0][1]=v;
        seg[idx].m[1][0]=0;    seg[idx].m[1][1]=NINF;
    } else {
        int m=(l+r)/2;
        if(pos<=m) update(idx*2,l,m,pos,v);
        else update(idx*2+1,m+1,r,pos,v);
        seg[idx]=combine(seg[idx*2],seg[idx*2+1]);
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>N>>D;
    vector<ll> a(N+1);
    for(int i=1;i<=N;i++) cin>>a[i];
    seg.assign(4*(N+1),Node());
    build(1,1,N,a);
    ll total=0;
    for(int d=0;d<D;d++){
        int i; ll m;
        cin>>i>>m;
        update(1,1,N,i,m);
        Node &root = seg[1];
        total += max(root.m[0][0], root.m[0][1]);
    }
    cout<<total;
    return 0;
}