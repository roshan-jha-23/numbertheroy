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
    int n;
    cin >> n;
    vector<int> v(2 * n, 0);
    queue<int> q1;
    queue<int> q0;
    queue<int> q11;
    queue<int> q10;
    for (int i = 0; i < 2 * n; i++)
    {
        cin >> v[i];
        if (v[i] == 0)
        {
            q0.push(0);
            q10.push(0);
        }
        else
        {
            q1.push(1);
            q11.push(1);
        }
    }
    // for min
    while (q10.size() > 1)
    {
        q10.pop();
        q10.pop();
    }
    while (q11.size() > 1)
    {
        q11.pop();
        q11.pop();
    }
    cout << q10.size() << " ";
    // for max
    int cnt = 0;
    while (!q1.empty() && !q0.empty())
    {
        q1.pop();
        q0.pop();
        cnt++;
    }
    cout << cnt << " \n";
}
ll medi(ll sp, ll ep)
{
    ll mid = (sp + ep) / 2;
    return mid;
}
void median()
{
    ll n, k;
    cin >> n >> k;
    if (medi(1, n) == k)
    {
        cout << 1 << "\n";
        cout << 1 << "\n";
        return;
    }
    else
    {
        cout << -1 << "\n";
    }
}
void trinity()
{
    ll n;
    cin >> n;
    vector<ll> a(n, 0);
    for (ll i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    
}
int main()
{
    fast_io;
    int t;
    cin >> t;
    while (t--)
    {
        trinity();
    }
    return 0;
}