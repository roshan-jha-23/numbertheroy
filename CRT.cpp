#include <bits/stdc++.h>
using namespace std;

#define fast_io                  \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr)
#define ll long long
#define ull unsigned long long
#define pb push_back
#define mp make_pair
#define all(v) v.begin(), v.end()
#define sz(v) ((int)(v).size())
#define rep(i, a, b) for (int i = a; i < b; ++i)
#define rrep(i, a, b) for (int i = a; i >= b; --i)
#define endl '\n'
const int INF = 1e9, MOD = 1e9 + 7, N = 1e5;
vector<ll> fact(N), invfact(N);

// GCD and LCM
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }

// Modular exponentiation
ll power(ll a, ll b, ll m)
{
    ll res = 1;
    a %= m;
    while (b)
    {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

// Modular inverse
ll modularInverse(ll a, int mod) { return power(a, mod - 2, mod); }

// Precompute factorials and inverse factorials
void precompute()
{
    fact[0] = 1;
    rep(i, 1, N) fact[i] = fact[i - 1] * i % MOD;
    invfact[N - 1] = power(fact[N - 1], MOD - 2, MOD);
    rrep(i, N - 2, 0) invfact[i] = invfact[i + 1] * (i + 1) % MOD;
}

// nCr modulo MOD
ll ncr(int n, int r)
{
    if (r > n || n < 0 || r < 0)
        return 0;
    return fact[n] * invfact[r] % MOD * invfact[n - r] % MOD;
}

// Max subarray length with sum <= k
int maxSubarrayLenWithSumLessThanOrEqualToK(vector<int> &arr, int k)
{
    int l = 0, sum = 0, maxLen = 0;
    rep(r, 0, sz(arr))
    {
        sum += arr[r];
        while (sum > k)
            sum -= arr[l++];
        maxLen = max(maxLen, r - l + 1);
    }
    return maxLen;
}
vector<int> smallestPrimeFactor(int n)
{
    vector<int> spf(n + 1);
    for (int i = 0; i <= n; i++)
    {
        spf[i] = i;
    }
    for (int i = 2; i * i <= n; i++)
    {
        if (spf[i] == i)
        {
            for (int j = i * i; j <= n; j += i)
            {
                if (spf[j] == j)
                {
                    spf[j] = i;
                }
            }
        }
    }
    return spf;
}

// Sieve of Eratosthenes
vector<bool> sieve(int n)
{
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= n; ++i)
        if (is_prime[i])
            for (int j = i * i; j <= n; j += i)
                is_prime[j] = false;
    return is_prime;
}

void solve()
{
    ll n;
    cin >> n;
    vector<int64_t> a(n, 0);
    ll mini = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        mini = min(mini, a[i]);
    }
    bool isSame = false;
    for (int i = 1; i < n; i++)
    {
        if (a[i] == a[i - 1])
        {
            isSame = true;
            break;
        }
    }
    if (isSame)
    {
        cout << "NO\n";
    }
    else
    {
        for (int x = 0; x < mini; x++)
        {
            bool isTrue = true;
            for (int i = 0; i < n; i++)
            {
                for (int j = i + 1; j < n; j++)
                {
                    if (gcd(a[i] + x, a[j] + x) != 1)
                    {
                        isTrue = false;
                    }
                }
            }
            if (isTrue)
            {
                cout << "YES\n";
                break;
            }
        }
    }
}
int main()
{
    fast_io;
    int t;
    cin >> t;
    while (t--)
    {

        solve();
    }
    return 0;
}