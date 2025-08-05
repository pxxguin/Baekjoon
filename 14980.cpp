#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Job{int idx; int T; int S;};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    if(!(cin>>N)) return 0;
    vector<Job> a;
    a.reserve(N);
    for(int i=1;i<=N;i++){
        int T,S;
        cin>>T>>S;
        a.push_back({i,T,S});
    }
    sort(a.begin(), a.end(), [](const Job &x, const Job &y){
        long long lhs = (long long)x.S * y.T;
        long long rhs = (long long)y.S * x.T;
        if(lhs != rhs) return lhs > rhs;
        return x.idx < y.idx;
    });
    for(int i=0;i<N;i++){
        if(i) cout << ' ';
        cout << a[i].idx;
    }
    cout << "\n";
    return 0;
}