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
const int INF = 1e9, MOD = 1e9 + 7, N = 2e5+20;
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
vector<bool> sieve()
{
    vector<bool> isPrime(2002002, true);
    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i * i <= 2002002; i++)
    {
        if (isPrime[i])
        {
            for (int j = i * i; j <= 2002002; j += i)
            {
                isPrime[j] = false;
            }
        }
    }
    return isPrime;
}

int fxn(vector<ll> &v, int idx, int n, int prev, map<pair<int, int>, int> &dp)
{
    if (idx == n)
    {
        return 0;
    }
    if (dp.find({idx, prev}) != dp.end())
    {
        return dp[{idx, prev}];
    }
    int nt = fxn(v, idx + 1, n, prev, dp);
    int t = 0;
    if (prev == -1 || gcd(prev, v[idx]) > 1)
    {
        t = 1 + fxn(v, idx + 1, n, v[idx], dp);
    }
    return dp[{idx, prev}] = max(t, nt);
}
void solve()
{
    int64_t n;
    cin >> n;
    vector<ll> v(n, 0);
    for (auto &it : v)
        cin >> it;
    map<pair<int, int>, int> dp;
    cout << fxn(v, 0, n, -1, dp) << "\n";
}
void simpleSubset()
{
    int n;
    cin >> n;
    vector<int64_t> a(n, 0);
    int cnt1 = 0;

    for (auto &it : a)
        cin >> it;
    vector<bool> prime = sieve();
    vector<int64_t> odd;
    vector<int64_t> even;

    for (int i = 0; i < n; i++)
    {
        if (a[i] == 1)
            cnt1++;
        else if (a[i] & 1)
        {
            odd.push_back(a[i]);
        }
        else
        {
            even.push_back(a[i]);
        }
    }

    vector<pair<int64_t, int64_t>> v;

    for (auto it : odd)
    {
        for (auto x : even)
        {
            if (prime[it + x])
            {
                v.push_back({it, x});
                break;
            }
        }
    }

    bool flag = false;
    int thate = -1;
    if (cnt1)
    {
        for (auto it : even)
        {
            if (prime[it + 1])
            {
                flag = true;
                thate = it;
                break;
            }
        }
    }
    if (flag == false && cnt1 > 2)
    {
        cout << cnt1 << "\n";
        for (int i = 0; i < cnt1; i++)
            cout << 1 << " ";
        cout << "\n";
    }
    else if (flag && cnt1 == 1)
    {
        cout << 2 << "\n";
        cout << thate << " " << 1 << "\n";
    }
    else if (flag && cnt1 > 1)
    {
        cout << (1 + cnt1) << "\n";
        cout << thate << " ";
        for (int i = 0; i < cnt1; i++)
            cout << 1 << " ";
        cout << "\n";
    }
    else if (!v.empty())
    {
        cout << 2 << "\n";
        cout << v[0].first << " " << v[0].second << "\n";
    }
    else
    {
        cout << 1 << "\n";
        cout << a[0] << "\n";
    }
}

ll cnt = 0;
map<pair<int, ll>, ll> memo;

ll fxn(vector<ll> &a, int i, ll currentGCD, ll n)
{
    if (i == n)
    {
        return (currentGCD == 1) ? 1 : 0;
    }
    if (memo.count({i, currentGCD}))
        return memo[{i, currentGCD}];
    ll withoutCurrent = fxn(a, i + 1, currentGCD, n);
    ll withCurrent = fxn(a, i + 1, gcd(currentGCD, a[i]), n);
    return memo[{i, currentGCD}] = (withoutCurrent + withCurrent) % MOD;
}

void coprimeSubsequences()
{
    ll n;
    cin >> n;
    vector<ll> a(n);

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    cnt = fxn(a, 0, 0, n);
    cout << cnt << "\n";
    memo.clear();
}
void someOtherMethod()
{
    ll n;
    cin >> n;
    vector<ll> a(n);
    for (auto &it : a)
        cin >> it;

    const int LIMIT = 1e5 + 20;
    vector<ll> cnt(LIMIT, 0);

    for (auto it : a)
    {
        for (int i = 1; i * i <= it; i++)
        {
            if (it % i == 0)
            {
                cnt[i]++;
                if (i != it / i)
                {
                    cnt[it / i]++;
                }
            }
        }
    }

    vector<ll> res(LIMIT, 0);
    for (int i = 1; i < LIMIT; i++)
    {
        if (cnt[i] > 0)
        {
            res[i] = power(2, cnt[i], MOD) - 1;
            if (res[i] < 0)
                res[i] += MOD;
        }
    }

    for (int i = LIMIT - 1; i >= 1; i--)
    {
        for (int j = 2 * i; j < LIMIT; j += i)
        {
            res[i] = (res[i] - res[j] + MOD) % MOD;
        }
    }

    cout << res[1] << "\n";
}
int validlyTheBearAndBeautifulStrings(int cnt0, int cnt1, int target)
{
    if (cnt1 == 0)
    {
       if(cnt0%2==0){
          return target==1?1:0;
       }else{
        return target==0?1:0;
       }
    }
    if (cnt0 == 0)
    {
        return (cnt1 > 1 ? target == 0 : target == 1) ? 1 : 0;
    }

    int answer = 0;
    for (int i = 0; i <= cnt0; i++)
    {
        int total = cnt0 + cnt1 - 1 - i;
        if ((i % 2 == target && total > 0) || (i % 2 != target && total <= 0))
        // If i has the desired parity and more elements can be used, or if i has the opposite parity and we’re at the end, then this combination is valid.
        {
            answer = (answer + ncr(total, cnt1 - 1)) % MOD;
        }
    }
    return answer;
}
vector<pair<int,int>> div(int n){
    vector<int> p;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            p.push_back(i);
            while (n % i == 0)
                n /= i;
        }
    }
    if (n > 1)
        p.push_back(n);

    int size = p.size();
    vector<pair<int, int>> a(1 << size);
    a[0] = {1, 1};
    for (int i = 1; i < (1 << size); i++)
    {
        int j = __builtin_ctz(i);
        auto [x, y] = a[i ^ (1 << j)];
        a[i] = {x * p[j], -y};
    }
    return a;
}
void countGXDD(){
   int n,m;
   cin >> n>>m;
   vector<ll>v(n,0);
   for(int i=0;i<n;i++){
    cin >> v[i];
   }
   //early breakagae i will do 
   for(int i=1;i<n;i++){
    if(v[i-1]%v[i]!=0){
        cout<<0<<"\n";
        return;
    }
   }
  //well well
  ll ans=0;
  for(int i=1;i<n;i++){
    if(v[i]==v[i-1]){
        ans=(ans*(m/v[i]))%MOD;
    }else{
        ll res=0;
        for(auto [x,y]:div(v[i-1]/v[i])){
            res = (res + x * (m / v[i] / x) % MOD);
        }
        ans = (ans) * res % MOD;
    }
  }
  cout << ans << "\n";
}
int main()
{
    fast_io;
    int t;
    cin >> t;
    while(t--){
        countGXDD();
    }
    return 0;
}