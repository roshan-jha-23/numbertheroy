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

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }

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

ll modularInverse(ll a, int mod) { return power(a, mod - 2, mod); }

void precompute()
{
    fact[0] = 1;
    rep(i, 1, N) fact[i] = fact[i - 1] * i % MOD;
    invfact[N - 1] = power(fact[N - 1], MOD - 2, MOD);
    rrep(i, N - 2, 0) invfact[i] = invfact[i + 1] * (i + 1) % MOD;
}

ll ncr(int n, int r)
{
    if (r > n || n < 0 || r < 0)
        return 0;
    return fact[n] * invfact[r] % MOD * invfact[n - r] % MOD;
}

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
// inclusion -exlusion principle ka main purpose hai overalpping set ko properly cnt karna ye ek tarreka hai jisse hum ensure karte hai ki ksisbhi solution mein jo elemrnts multiple sets meins aate hai unhe sahi tarreks e=se count kiya jaye na to kuch exra na to to kuch choot jaye chaliye isko alag alag examples ke satah dekgete hai

// Basic concept of Inclusion-exclusion principle
// in simple words agar hamare paas kuch sets hai aur humien unka unka union lena hai toh pehle hum un sets ko indivisually add karre hau phir jo ellemnets common hai unhe minus kar dte hai
//  formula:|A U B|=|A|+|B|-|A ∩ B|; yaaha haum  a union b mein vo saare lete hai jo  a and b mein common hote hai phir and phir enusre karne ke lu\iye ki double count na ho jaye usko hata dete hai intesection ke form mein
// for three no
//|A U B|=|A|+|B|+|C|-|A ∩ B|-|A ∩ C|-|B ∩ C|+|A ∩ B ∩ C|;
// isme hamne sare elments add kiye phir jo pair wiase common elemnts hai usko minus karte chale gaye and finally jo sabme common hai usko add back ka diya
// Example 1
void count_divisibles(int N)
{

    int div2 = N / 2;
    int div3 = N / 3;
    int div5 = N / 5;
    int div2And3 = N / (2 * 3);
    int div5And3 = N / (5 * 3);
    int div2And5 = N / (2 * 5);
    int div2And5And3 = N / (2 * 5 * 3);
    int total = div2 + div3 + div5 - div2And3 - div5And3 - div2And5 + div2And5And3;
    cout << total << "\n";
}
// inclusion-exlucions in factors cunitng
void solve2()
{
    vector<int> pf = {2, 3}; // suppose prime factors are 2 and 3
    int size = pf.size();
    vector<int> res;
    for (int i = 1; i < (1 << size); i++)
    {
        int prod = 1;
        int sign = -1;
        for (int j = 0; j < size; j++)
        {
            if (i & (1 << j))
            {
                prod *= pf[j];
                sign *= -1;
            }
        }
        res.push_back(sign * prod);
    }
    for (auto it : res)
    {
        cout << it << " ";
    }
    // 2 3 -6
}
// inclusion exclsuionsw for counting arrays with constaints
//  maan l tumahre ko ek array ke andar aise no ko count karna hai jo kisi given diviisors d se divisble ho agar har elemnts ke liye tumhe ye karna hai toh tumhe unke diviors oe inclusions exclusions lagana padega
void count_divisors_in_array()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 23, 45, 34, 2, 33, 442, 455, 3, 554, 6, 3, 5, 53, 5, 5, 53};
    int Limit = 1000;
    vector<int> cnt(Limit + 1, 0);
    for (auto it : arr)
    {
        for (int i = 1; i * i < it; i++)
        {
            if (it % i == 0)
            {
                cnt[i]++;
                if (it / i != i)
                {
                    cnt[it / i]++;
                }
            }
        }
    }
    vector<ll> res(Limit + 1, 0);
    for (int i = 1; i <= Limit; i++)
    {
        if (cnt[i] > 0)
        {
            res[i] = power(2, cnt[i], MOD) - 1;
        }
    }
    // upar mein hamne no of subests ko count kar liye hau
    for (int i = Limit; i >= 1; i--)
    {
        for (int j = 2 * i; j <= Limit; j += i)
        {
            res[i] -= res[j];
        }
    }

    for (auto it : res)
    {
        cout << it << " ";
    }
}

// Inclusion - Exclusion principle ka idea yeh hai ki hum pehle sab counts ko include karte hain, phir overlapping sets ko exclude karte hain aur jo bhi total hota hai wo hume final unique count de deta hai.Ye approach har jagah useful hai jahan overlapping combinations hoti hain.
// 0 67107460 1005 244 5 124 6 2 1 2 1 0 1 1 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 1 2 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
int count_div(int N, const std::vector<int> &div)
{
    int subset = 1 << div.size();
    int res = 0;
    // Generate each subset
    for (int mask = 0; mask < subset; mask++)
    {
        int lcm = 1;
        int bits = __builtin_popcount(mask);
        for (int j = 0; j < div.size(); j++)
        {
            if (mask & (1 << j))
            {
                lcm *= div[j];
            }
        }
        // Inclusion-Exclusion Principle
        if (bits % 2 == 1)
        {
            res += N / lcm; // Include if odd number of elements
        }
        else
        {
            res -= N / lcm; // Exclude if even number of elements
        }
    }
    return res;
}
vector<ll> prime_fac(int x)
{
    vector<ll> res;
    for (int i = 2; i * i <= x; ++i)
    {
        if (x % i == 0)
        {
            res.push_back(i);
            while (x % i == 0)
            {
                x /= i;
            }
        }
    }
    if (x > 1)
        res.push_back(x);
    return res;
}
int coprime_count(int n, int x)
{
    vector<ll> prime = prime_fac(x);
    int subset = 1 << prime.size();
    int cnt = 0;
    for (int i = 1; i < subset; i++)
    {
        int lcm = 1;
        int bits = __builtin_popcount(i);
        for (int j = 0; j < prime.size(); j++)
        {
            if (i & (1 << j))
            {
                lcm *= prime[j];
            }
        }
        if (bits % 2 == 1)
        {
            cnt += n / lcm;
        }
        else
        {
            cnt -= n / lcm;
        }
    }
    return n - cnt; // numbers that are coprime to x
}
// on a chessboard with some cells blocked ,how many ways can we place rooks  if some cells are marked as block\\// now this can be done with inclusion -exclusion by first choosing all possible placement then substarcting the way where rooks attack each other (on the same row or column)
int count_non_attacking_rooks(int N, vector<std::pair<int, int>> &blocked_cells)
{
    int rows = N;
    int cols = N;
    vector<ll> rowC(N, 0);
    vector<ll> colC(N, 0);
    for (auto &cell : blocked_cells)
    {
        rowC[cell.first]++;
        colC[cell.second]++;
    }
    int total_Ways = 1 << (rows + cols);
    int res = 0;
    for (int mask = 1; mask < total_Ways; mask++)
    {
        int row_rooks = 0;
        int col_rooks = 0;
        int bits = __builtin_popcount(mask);
        for (int i = 0; i < rows; ++i)
        {
            if (mask & (1 << i))
            {
                row_rooks++;
            }
        }
        for (int i = 0; i < cols; ++i)
        {
            if (mask & (1 << i + rows))
            {
                col_rooks++;
            }
        }
        int placement = 1;
        for (int i = 0; i < row_rooks; i++)
            placement *= rowC[i];
        for (int i = 0; i < col_rooks; i++)
            placement *= colC[i];
        if (bits % 2 == 1)
        {
            res += placement;
        }
        else
        {
            res -= placement;
        }
    }
    return res;
}
void co_prime(int t)
{
    ll n, a, b;
    cin >> a >> b >> n;
    vector<ll> fact;
    for (ll i = 2; i * i <= n; ++i)
    {
        if (n % i == 0)
        {
            fact.push_back(i);
            while (n % i == 0)
            {
                n /= i;
            }
        }
    }
    if (n > 1)
        fact.push_back(n);
    int si = fact.size();
    ll ans = 0ll;
    for (int mask = 1; mask < (1 << si); mask++)
    {
        ll lcm = 1;
        int bit = __builtin_popcount(mask);
        for (int j = 0; j < fact.size(); j++)
        {
            if (mask & (1 << j))
            {
                lcm *= fact[j];
            }
        }
        ll cnt = b / lcm - (a - 1) / lcm;
        if (bit & 1)
        {
            ans += cnt;
        }
        else
        {
            ans -= cnt;
        }
    }
    cout << " Case #" << t << ": " << (b - a + 1) - ans << "\n";
}
//count nof of binary string either starting from zero or ending with zero
//0' start + 0's end  - 0'start and end(IEP)
//count of no diviisble by either 2 or 5 in range (1,500);
//(500-1+1)/2 +(500-1+1)/5 - (500-1+1)/lcm(2,5);

int main()
{
    fast_io;
    int t;
    cin >> t;
    for(int i=1;i<=t;i++)co_prime(i);
    return 0;
}