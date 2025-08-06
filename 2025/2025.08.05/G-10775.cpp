#include <iostream>
#include <vector>
using namespace std;
int findRoot(vector<int>& p, int x) {
    return p[x] == x ? x : p[x] = findRoot(p, p[x]);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int G, P;
    cin >> G >> P;
    vector<int> parent(G + 1);
    for (int i = 0; i <= G; i++) parent[i] = i;
    int ans = 0;
    while (P--) {
        int g;
        cin >> g;
        int r = findRoot(parent, g);
        if (r == 0) break;
        ans++;
        parent[r] = r - 1;
    }
    cout << ans;
    return 0;
}