#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    random_device rd;
    mt19937 gen(rd());
    vector<int> vals(10000);
    iota(vals.begin(), vals.end(), 1);
    int A = 0, B = 0, resp;
    shuffle(vals.begin(), vals.end(), gen);
    for (int x : vals) {
        cout << "? A " << x << "\n" << flush;
        if (!(cin >> resp)) return 0;
        if (resp == 1) { A = x; break; }
    }
    shuffle(vals.begin(), vals.end(), gen);
    for (int x : vals) {
        cout << "? B " << x << "\n" << flush;
        if (!(cin >> resp)) return 0;
        if (resp == 1) { B = x; break; }
    }
    cout << "! " << (A + B) << "\n" << flush;
    return 0;
}