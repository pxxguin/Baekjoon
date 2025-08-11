#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N,Q;
    if(!(cin>>N>>Q)) return 0;
    vector<unordered_set<int>> S(N+1);
    for(int i=1;i<=N;i++){
        int c; cin>>c;
        S[i].reserve(c*2+1);
        for(int j=0;j<c;j++){
            int x; cin>>x;
            S[i].insert(x);
        }
    }
    while(Q--){
        int op; cin>>op;
        if(op==1){
            int a,b; cin>>a>>b;
            if(a==b) continue;
            if(S[a].size()<S[b].size()) swap(S[a],S[b]);
            if(!S[b].empty()){
                if(S[a].bucket_count() < S[a].size()+S[b].size()) S[a].rehash((S[a].size()+S[b].size())*2+1);
                for(const int& x: S[b]) S[a].insert(x);
                S[b].clear();
            }
        }else{
            int a; cin>>a;
            cout<<S[a].size()<<"\n";
        }
    }
    return 0;
}