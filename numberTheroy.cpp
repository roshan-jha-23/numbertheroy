#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <bits/stdc++.h>
using namespace std;
#define fast_io                  \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr)

typedef long long ll;
const ll mod = 1ll * 1e9 + 7;
const int N = 2000000;
const int MOD = 1000000007;

ll fact[N], invfact[N];

// Calculate (a^b) % m using modular exponentiation
ll power(ll a, ll b, ll m)
{
    ll res = 1;
    a %= m; // Ensure `a` is within `m`
    while (b)
    {
        if (b & 1) // If `b` is odd
            res = res * a % m;
        a = a * a % m; // Square `a`
        b >>= 1;       // Divide `b` by 2
    }
    return res;
}

// Modular inverse using Fermat's Little Theorem: a^(MOD-2) % MOD
ll modularInverse(ll a, int mod)
{
    return power(a, mod - 2, mod);
}

// Precompute factorials and inverse factorials modulo MOD
void precompute()
{
    fact[0] = 1;
    for (int i = 1; i < N; i++)
    {
        fact[i] = fact[i - 1] * i % MOD;
    }

    // Compute the inverse of factorial[N-1]
    invfact[N - 1] = modularInverse(fact[N - 1], MOD);

    // Compute inverse factorials in reverse order
    for (int i = N - 2; i >= 0; i--)
    {
        invfact[i] = invfact[i + 1] * (i + 1) % MOD;
    }
}

// Calculate nCr % MOD
ll ncr(int n, int r)
{
    if (r > n || n < 0 || r < 0) // Invalid cases
        return 0;
    return fact[n] * invfact[r] % MOD * invfact[n - r] % MOD;
}
ll gcd(ll a, ll b)
{
    while (b != 0)
    {
        ll temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
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
void rowGCD()
{
    int n, m;
    cin >> n >> m;
    ll fNo;
    cin >> fNo;
    ll gcdn = 0;

    for (int i = 1; i < n; i++)
    {
        ll currNo;
        cin >> currNo;
        gcdn = gcd(gcdn, abs(currNo - fNo));
    }

    for (int i = 0; i < m; i++)
    {
        ll q;
        cin >> q;
        cout << gcd(q + fNo, gcdn) << " ";
    }
    cout << "\n";
}

vector<bool> sieve()
{
    vector<bool> isPrime(1000001, true);
    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i * i <= 1000000; i++)
    {
        if (isPrime[i])
        {
            for (int j = i * i; j <= 1000000; j += i)
            {
                isPrime[j] = false;
            }
        }
    }
    return isPrime;
}

void tPrime()
{
    vector<bool> isPrime = sieve();
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        ll x;
        cin >> x;
        ll sq = sqrt(x);
        if (sq * sq == x)
        {
            if (isPrime[sq])
            {
                cout << "YES" << "\n";
            }
            else
            {
                cout << "NO" << "\n";
            }
        }
        else
        {
            cout << "NO\n";
        }
    }
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
void prime()
{
    ll n, x;
    cin >> n >> x;

    vector<ll> v(n);
    for (auto &it : v)
        cin >> it;

    auto sum = [](pair<ll, ll> a, pair<ll, ll> b)
    {
        ll ansU = ((a.first * b.second) % mod + (b.first * a.second) % mod) % mod;
        ll ansD = (a.second * b.second) % mod;

        return make_pair(ansU, ansD);
    };

    pair<ll, ll> pr = {0, 1};
    for (int i = 0; i < n; i++)
    {
        pr = sum(pr, {1, power(x, v[i], mod)});
    }

    cout << gcd(pr.first, pr.second) << "\n";
}
void primeAttempt2()
{
    ll n, x;
    cin >> n >> x;
    vector<ll> nums(n);
    ll sum = 0;

    for (ll i = 0; i < n; ++i)
    {
        cin >> nums[i];
        sum += nums[i];
    }

    sort(nums.begin(), nums.end());
    ll ans = sum - nums[n - 1];
    ll count = 1;

    for (ll i = n - 1; i >= 0; --i)
    {
        if (nums[i] < nums[n - 1])
            break;
        if (count % x != 0)
            break;
        count /= x;
        ++ans;
    }

    cout << power(x, ans, mod) << "\n";
}
void primeAttempts3()
{
    ll n, x;
    cin >> n >> x;
    ll sum = 0;
    vector<int64_t> a(n);
    map<ll, int64_t> cnt;
    for (ll i = 1; i <= n; ++i)
    {
        int x;
        cin >> x;
        a[i - 1] = x;
        sum += x;
    }
    for (int i = 0; i < n; i++)
    {
        cnt[sum - a[i]]++;
    }
    ll curr = sum - a[n - 1];
    while (cnt[curr] % x == 0)
    {
        cnt[curr + 1] += cnt[curr] / x;
        cnt[curr] = 0;
        curr++;
    }
    cout << power(x, curr, mod) << "\n";
}
int cnt[2];
int target;
inline bool read(){
    return (cin>>cnt[0]>>cnt[1]>>target);
}
int validlyTheBearAndBeautifulStrings()
{
    if(cnt[1]==0){
        return cnt[0]%2!=target;
    }
    if(cnt[0]==0){
        return cnt[1]>1?target==0:target==1;
    }

    int answer = 0;
    for (int i = 0; i <= cnt[0]; i++)
    {
        int total = cnt[0] + cnt[1] - 1 - i;
        if ((i % 2 == target && total > 0) || (i % 2 != target && total <= 0))
        {
            answer = (answer + ncr(total, cnt[1] - 1)) % mod;
        }
    }
    return answer;
}

int main()
{
    fast_io;

    // Call the functions here based on your requirements
    // For example:
    // rowGCD();
    // tPrime();
    // prime();
    primeAttempts3();
    return 0;
}
