#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;
const int INF = 1000000000;
const int NEG_INF = numeric_limits<int>::min();
struct SegTree {
    int n;
    vector<int> st;
    SegTree(int _n): n(_n), st(4*_n, NEG_INF) {}
    void build(int p, int l, int r, const vector<int>& a, const vector<bool>& cov) {
        if (l == r) {
            st[p] = cov[l] ? a[l] : NEG_INF;
        } else {
            int m = (l + r) >> 1;
            build(p<<1, l, m, a, cov);
            build(p<<1|1, m+1, r, a, cov);
            st[p] = max(st[p<<1], st[p<<1|1]);
        }
    }
    void update(int p, int l, int r, int i, int v, bool cov) {
        if (l == r) {
            st[p] = cov ? v : NEG_INF;
        } else {
            int m = (l + r) >> 1;
            if (i <= m) update(p<<1, l, m, i, v, cov);
            else update(p<<1|1, m+1, r, i, v, cov);
            st[p] = max(st[p<<1], st[p<<1|1]);
        }
    }
    int query() const { return st[1]; }
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M, Q;
    cin >> N >> M >> Q;
    vector<int> a(N+1);
    for(int i=1;i<=N;i++) cin>>a[i];
    vector<int> L(M), R(M);
    for(int i=0;i<M;i++) cin>>L[i];
    for(int i=0;i<M;i++) cin>>R[i];
    sort(L.begin(), L.end());
    sort(R.begin(), R.end());
    for(int i=0;i<M;i++){
        if(L[i] > R[i]){
            while(Q--){
                cout<<INF<<"\n";
            }
            return 0;
        }
    }
    vector<int> diff(N+2,0);
    for(int i=0;i<M;i++){
        diff[L[i]]++;
        diff[R[i]+1]--;
    }
    vector<bool> cov(N+1,false);
    int cur=0;
    for(int i=1;i<=N;i++){
        cur+=diff[i];
        cov[i]=cur>0;
    }
    SegTree st(N);
    st.build(1,1,N,a,cov);
    while(Q--){
        int x,y;
        cin>>x>>y;
        swap(a[x],a[y]);
        st.update(1,1,N,x,a[x],cov[x]);
        st.update(1,1,N,y,a[y],cov[y]);
        cout<<st.query()<<"\n";
    }
    return 0;
}