13#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct Q{int l,r,idx,blk;};

// jonna hard hagun..
int main(int argc, char *argv[]){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin>>N;
    vector<int>A(N);
    for(int i=0;i<N;i++)cin>>A[i];
    int M;
    cin>>M;
    int B=max(1,int(sqrt(N)));
    vector<Q>qs(M);
    for(int i=0;i<M;i++){
        cin>>qs[i].l>>qs[i].r;
        --qs[i].l;--qs[i].r;
        qs[i].idx=i;
        qs[i].blk=qs[i].l/B;
    }
    sort(qs.begin(),qs.end(),[](const Q&a,const Q&b){
        if(a.blk!=b.blk)return a.blk<b.blk;
        return (a.blk&1)?a.r>b.r:a.r<b.r;
    });
    vector<int>fv(100001),fc(N+1),ans(M);
    int curL=0,curR=-1,curMax=0;
    auto add=[&](int p){
        int v=A[p];
        int o=fv[v]++;
        if(o>0)fc[o]--;
        fc[o+1]++;
        if(o+1>curMax)curMax=o+1;
    };
    auto rem=[&](int p){
        int v=A[p];
        int o=fv[v]--;
        fc[o]--;
        if(o-1>0)fc[o-1]++;
        if(fc[curMax]==0)curMax--;
    };
    for(auto&q:qs){
        while(curL>q.l)add(--curL);
        while(curR<q.r)add(++curR);
        while(curL<q.l)rem(curL++);
        while(curR>q.r)rem(curR--);
        ans[q.idx]=curMax;
    }
    for(int x:ans)cout<<x<<'\n';
    return 0;
}