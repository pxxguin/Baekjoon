#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <cstdint>

using namespace std;
using u64 = uint64_t;

u64 mulmod(u64 a, u64 b, u64 m) {
    __uint128_t r = (__uint128_t)a * b;
    return (u64)(r % m);
}

u64 powmod(u64 a, u64 e, u64 m) {
    u64 r = 1;
    while (e) {
        if (e & 1) r = mulmod(r, a, m);
        a = mulmod(a, a, m);
        e >>= 1;
    }
    return r;
}

bool isPrime(u64 n) {
    if (n < 2) return false;
    for (u64 p : {2ULL,3ULL,5ULL,7ULL,11ULL,13ULL,17ULL,19ULL,23ULL,29ULL,31ULL,37ULL})
        if (n % p == 0) return n == p;
    u64 d = n - 1, s = 0;
    while ((d & 1) == 0) { d >>= 1; s++; }
    for (u64 a : {2ULL,325ULL,9375ULL,28178ULL,450775ULL,9780504ULL,1795265022ULL}) {
        if (a % n == 0) continue;
        u64 x = powmod(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool comp = true;
        for (u64 r = 1; r < s; r++) {
            x = mulmod(x, x, n);
            if (x == n - 1) { comp = false; break; }
        }
        if (comp) return false;
    }
    return true;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

u64 pollards_rho(u64 n) {
    if (n % 2 == 0) return 2;
    if (n % 3 == 0) return 3;
    u64 c = uniform_int_distribution<u64>(1, n - 1)(rng);
    u64 x = uniform_int_distribution<u64>(0, n - 1)(rng);
    u64 y = x, d = 1;
    while (d == 1) {
        x = (mulmod(x, x, n) + c) % n;
        y = (mulmod(y, y, n) + c) % n;
        y = (mulmod(y, y, n) + c) % n;
        d = gcd<u64>(x > y ? x - y : y - x, n);
        if (d == n) return pollards_rho(n);
    }
    return d;
}

void factor(u64 n, vector<u64>& f) {
    if (n == 1) return;
    if (isPrime(n)) { f.push_back(n); return; }
    u64 d = pollards_rho(n);
    factor(d, f);
    factor(n / d, f);
}

int main() {
    u64 n;
    cin >> n;
    vector<u64> f;
    factor(n, f);
    sort(f.begin(), f.end());
    for (u64 p : f) cout << p << "\n";
    return 0;
}