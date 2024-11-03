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
    if ((n & 1) != 0)
    {
        cout << "Kosuke\n";
    }
    else
    {
        cout << "Sakurako\n";
    }
}
void solve2()
{
    int n;
    cin >> n;

    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> a[i][j];
        }
    }
    int ans = 0;
    for (int d = 1 - n; d < n; ++d)
    {
        int maxi = 9999999;
        bool flag = false;

        for (int row = 0; row < n; ++row)
        {
            int col = row - d;
            if (col >= 0 && col < n)
            {
                if (a[row][col] < 0)
                {
                    maxi = min(maxi, a[row][col]);
                    flag = true;
                }
            }
        }

        if (flag)
        {
            ans += maxi;
        }
    }
    cout << -ans << "\n";
}
int countConsecutivePairs(const vector<int> &arr)
{
    int cnt = 0;
    for (int i = 0; i < arr.size() - 1; i++)
    {
        if (arr[i] == arr[i + 1])
        {
            cnt++;
        }
    }
    return cnt;
}
void solve3()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &it : a)
        cin >> it;
    for (int i = 1; i < n; i++)
    {
        if (a[i] == a[i - 1])
        {
            vector<int> swapWithCurrent = a;
            vector<int> swapWithPrevious = a;
            swap(swapWithCurrent[i], swapWithCurrent[n - i - 1]);
            swap(swapWithPrevious[i - 1], swapWithPrevious[n - i - 1]);
            int currentSwapPairs = countConsecutivePairs(swapWithCurrent);
            int previousSwapPairs = countConsecutivePairs(swapWithPrevious);
            if (currentSwapPairs < previousSwapPairs)
            {
                swap(a[i], a[n - i - 1]);
            }
            else
            {
                swap(a[i - 1], a[n - i - 1]);
            }
        }
    }
    int cnt = 0;
    for (int i = 0; i < n - 1; i++)
    {
        if (a[i] == a[i + 1])
        {
            cnt++;
        }
    }
    cout << cnt << "\n";
}
void solve4()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i];
    }
    unordered_map<ll, ll> mp;
    mp[0]++;
    ll curr = 0;
    ll cnt = 0;
    for (int i = 0; i < n; i++)
    {
        curr += a[i];
        if (mp[curr] > 0)
        {
            cnt++;
            mp.clear();
            mp[0]++;
            curr = 0;
        }
        else
        {
            mp[curr]++;
        }
    }
    cout << cnt << "\n";
}

void d()
{
    int n;
    cin >> n;
    vector<string> s(n);
    vector<long long> bi(n, 0), bj(n, 0);
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
        for (int j = 0; j < n; j++)
        {
            if (s[i][j] == 'o')
            {
                bi[i]++;
                bj[j]++;
            }
        }
    }

    long long res = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (s[i][j] == 'o')
            {
                res += (bi[i] - 1) * (bj[j] - 1);
            }
        }
    }
    cout << res << "\n";
}

int main()
{
    fast_io;
    int t;
    t = 1;
    while (t--)
    {
        d();
    }
    return 0;
}

