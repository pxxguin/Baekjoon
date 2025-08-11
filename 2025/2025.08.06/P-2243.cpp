#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    const int MAXV = 1000000;
    vector<ll> bit(MAXV + 1, 0);

    auto update = [&](int i, ll v){
        for(; i <= MAXV; i += i & -i) bit[i] += v;
    };

    auto find_k = [&](ll k){
        int idx = 0;
        int bitmask = 1 << 20;
        if(bitmask > MAXV) bitmask >>= 1;
        for(int d = bitmask; d > 0; d >>= 1){
            int nxt = idx + d;
            if(nxt <= MAXV && bit[nxt] < k){
                k -= bit[nxt];
                idx = nxt;
            }
        }
        return idx + 1;
    };

    while(n--){
        int A;
        cin >> A;
        if(A == 1){
            ll k;
            cin >> k;
            int res = find_k(k);
            cout << res << "\n";
            update(res, -1);
        } else {
            int b;
            ll c;
            cin >> b >> c;
            update(b, c);
        }
    }
    return 0;
}