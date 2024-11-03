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
// relatively prime pair
vector<pair<int, int>> getRelativelyPrimePairs(int n)
{
}
void relatively_prime()
{
    // l=2
    // r=15
    // right to left =>r-l+1 bande
    // iske beech mein jitne pair hai uski paoring karo
    // jitna pair bana hai uska gcd bana do
    /// agar possisble haoi yes karodo
    // agar not pssbl say no
    // relatively prime pair ka count
    // odd,even not neccesarily alwyas one hoga
    // sirf odd,even suffieicent nahi hai
    // kabhi bhi do consecutive no ko dekh lo uska gcd one hoga
    ll r, l;
    cin >> l >> r;

    // Check if we can form at least one pair
    if (r - l + 1 < 2)
    {
        cout << "NO\n";
        return;
    }

    // Output header for valid input case
    cout << "YES\n";

    for (ll i = l; i < r; i += 2)
    {
        ll a = i, b = i + 1;

        // Ensure `b` is within range
        if (b <= r && __gcd(a, b) == 1)
        {
            cout << a << " " << b << "\n";
        }
    }
}
void every_relatively_prime()
{
    ll l, r;
    cin >> l >> r;

    bool found = false;

    for (ll a = l; a <= r; ++a)
    {
        for (ll b = a + 1; b <= r; ++b)
        {
            if (__gcd(a, b) == 1)
            {
                if (!found)
                {
                    cout << "YES\n";
                    found = true;
                }
                cout << a << " " << b << "\n";
            }
        }
    }

    if (!found)
    {
        cout << "NO\n";
    }
}
// pigeonhole principle
//  p1     h1
//  p2     h2
//  p3     h3
//  .       .
//  .       .
//  .       .
//  .
//  Pn-1     Hn-1
//  Pn
// now we have n pigeion and n-1 hole then we can surely say that 2 pigeioen will accodmate in a hole for sure there will be a hole jaha 2 pigieon toh pakka se rahega
//  so it kinda ovious right? agar sare n-1 pigeioen ek ek hole pakad lenge tab ek pass aur koi chara nahi rahega alright alright less go
//  --------------------------$$$$$$$$$$-----------------
//  applications
//  red,black yellow and green 4 color ke shocks ek given color ke infinte shocks find minimum shocks such that ki ek color pair nikal ke aajye
//  toh kya kya ho sakta hai
// red green black yellow red ye worst condition hai jaha last mein jaak ek pair milega and what is this this is basically pigien hole principle
//  4 color 4 hole
//  1st color 1st hole
//  2nd color 2nd hole
//  3rd color 3rd hole
//  4th color 1st hole
//  so we can say that 2 color will be in same hole for sure
//    set {1,2,3,........,2n} u  want to choose n+1 no jisme ek aisa pair hoga jiska sum 2n+1 hoga n+1,n 2n+1 hoga agar increasing order mein bhi liya matlab worst case
// let say other than that agar randomly choose karnege n+1 C 2n toh phir toh jarur hi aayega lekin isme pigieonhole kaise lagg rha?
// sochiye har no ko pigieon ki tarah and har complementrry pair ko as a pigieonhole
//   for
//       example aapne 1 se leke n tak liya ab aap yaa to n + 1 lenge ya n + 2 ya n + 3 ..........maan lijiye aapne n + 10 liya and aapke pass already 10 hai to aapne ji ek complemntry pair bana liya na and since(every number 𝑘 k has a unique "complementary" pair 2 𝑛 + 1
// − 𝑘 2n + 1−k such that 𝑘 + (2 𝑛 + 1− 𝑘) = 2 𝑛 + 1 k + (2n + 1−k) = 2n + 1.)

//  n people hai ek grp hai (1,2,3,....,n)
// ab usme se bande apne hisab se firned bana skate hai person 1 chataha hai vo 5 firend banayega if(n>=5) to ye allowed hai
// toh usme se atleast 2 bande aise honge jinka count of frnd same hoga
// lets try for smaller friends
// 3 launde hai 1 ke 2,3 friend hai
// 2nd ke 1 frnd hai 3rd ke {1,2} toh dekho jhak maarke hua na 2 log aise jine friend count smae nikle agar mai 3 ko sirf ek friend deta toh bhi 2 aise bande rehte jinke friend same hai
// aur agar mai 3 ko 2 bande deta hoon like 1 nd 2  iska matlab 1 and 2 ka friend 3 hua and i alrady mentioned 1 ka 2,3 hai and iska matlab 3 and 2 ka 1 hua toh jhak marrke 2 and 3 ke 2 2 hue so this applies to all
// okay it says this can be solved using pigieonhole principle
void KuroniAndImpossibleCalculation()
{
    int n, m;
    cin >> n >> m;
    if (n > m)
    {
        cout << 0 << "\n";
        return;
    }

    vector<ll> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    ll prod = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            prod = (prod * abs(a[i] - a[j])) % m;
            if (prod == 0)
            {
                cout << 0 << "\n";
                return;
            }
        }
    }
    cout << prod << "\n";
}
void ekfxn()
{
    int n, m;
    cin >> n >> m;
    vector<ll> a(n, 0);
    for (auto &it : a)
        cin >> it;
    if (n > m)
    {
        cout << 0 << endl;
        return;
    }
    ll prod = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            prod = (prod * abs(a[i] - a[j])) % m;
            if (prod == 0)
            {
                cout << 0 << endl;
                return;
            }
        }
    }
    cout << prod << "\n";
}
void compProg()
{
    int n;
    cin >> n;
    //   to be divisble by 60 it should be divible by 10 ,6(2,3)
    //   to be divisble by 2 it should be even so agar ek zero last mein hua 10 and 2 dono ka kaam ho jayega and 3 ke liye it sum should be divisible by 3 alright
    //   so ek zero chaiye and sum /3 hona chaiye
    ll sum = 0;
    bool zeroflag = false;
    while (n != 0)
    {
        int rem = n % 10;
        if (rem == 0 && zeroflag == false)
        {
            zeroflag = true;
        }
        sum = sum + rem;
        n /= 10;
    }
    if (sum % 3 == 0 && zeroflag == true)
    {
        cout << "red" << endl;
    }
    else
    {
        cout << "cyan" << endl;
    }
}
void koxiaAndNumberTheory()
{
    int n;
    cin >> n;
    vector<int64_t> a(n, 0);
    for (auto &it : a)
        cin >> it;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (a[i] == a[j])
            {
                cout << "NO" << endl;
                return;
            }
        }
    }
    ll gcdx = 0;
    for (auto it : a)
    {
        gcdx = gcd(it, gcdx);
        if (gcdx != 1)
        {
            cout << "NO" << endl;
            return;
        }
    }
    if (gcdx == 1)
    {
        cout << "YES" << endl;
    }
}
// CRT
// ye ek mathematical concept hai jo hamlog use karte hai jab hume mutiple congurence solve karni rehni hai tab yeh kahin bhi apply hoti hai jaha pe ek number ko alag alag mdouli ke basis pe divide karke congurence form ho rhi ho
//  jaise
// x≡a1 mod m1
//  𝑥≡ 𝑎 2 mod𝑚2
//  x≡a3​ mod m3;
//  𝑥≡ 𝑎 4 mod𝑚4
// to ham CRT ki help se yeh find karte hai ki kaunse number in sabhi congurence ko satifuy kar rhi hai
// CRT ki basic idea yahi hai ki agar m1, m2, m3, m4......, mk pairwise co - prime hona chiayetoh in congruences ka ek unique solution exist karta hai in moduli ke product 𝑀 = 𝑚 1∗ 𝑚2∗ ...∗ 𝑚𝑘 ke mod mien
// CRT ke trhough we can eaisly find the solutions efficiently
// Finding Unique Solution for Large Moduli CRT ka ek major application hai jab hume bohot bade moduli ke saath kaam karna padta hai. Agar directly kaam nahi ho raha hai ya overflow ho raha hai, toh hum moduli ko chhote factors mein tod ke CRT se kaam kar sakte hain.
/*
Chinese Remainder Theorem (CRT) ko large moduli ke saath kaam karne ke liye use karna ek efficient technique hai. Agar hum directly kisi bade modulus ke saath kaam karte hain toh overflow ka issue aa sakta hai ya phir calculation slow ho sakti hai. CRT is issue ko solve karne mein help karta hai, kyunki CRT ke through hum modulus ko chhote co-prime moduli mein tod sakte hain aur unke solutions ko combine kar sakte hain.

Example Problem: Large Moduli with CRT
Problem Statement: Find
𝑥
x such that:

𝑥
≡
12
m
o
d
 
 
13
x≡12mod13
𝑥
≡
22
m
o
d
 
 
17
x≡22mod17
𝑥
≡
9
m
o
d
 
 
19
x≡9mod19
Here, direct modulus calculation could become complex if the number of such congruences grows or if we need a very large modulus. So, let’s solve it using CRT.

Solution Using CRT
Given Congruences:

𝑥
≡
12
m
o
d
 
 
13
x≡12mod13
𝑥
≡
22
m
o
d
 
 
17
x≡22mod17
𝑥
≡
9
m
o
d
 
 
19
x≡9mod19
Check Pairwise Co-Prime Moduli: Moduli 13, 17, and 19 are co-prime with each other. Thus, we can apply CRT directly.

Calculate Product of All Moduli:

𝑀
=
13
×
17
×
19
=
4199
M=13×17×19=4199
This means the unique solution
𝑥
x will be modulo 4199.

Compute Individual Terms: For each modulus
𝑚
𝑖
m
i
​
 , calculate
𝑀
𝑖
=
𝑀
𝑚
𝑖
M
i
​
 =
m
i
​

M
​
  and find its modular inverse
𝑀
𝑖
−
1
M
i
−1
​
  mod
𝑚
𝑖
m
i
​
 .

For
𝑚
1
=
13
m
1
​
 =13:

𝑀
1
=
4199
13
=
323
M
1
​
 =
13
4199
​
 =323
Find
𝑀
1
−
1
M
1
−1
​
  mod 13. Solving, we get
𝑀
1
−
1
=
6
M
1
−1
​
 =6 (as
323
×
6
≡
1
m
o
d
 
 
13
323×6≡1mod13).

For
𝑚
2
=
17
m
2
​
 =17:

𝑀
2
=
4199
17
=
247
M
2
​
 =
17
4199
​
 =247
Find
𝑀
2
−
1
M
2
−1
​
  mod 17. Solving, we get
𝑀
2
−
1
=
2
M
2
−1
​
 =2 (as
247
×
2
≡
1
m
o
d
 
 
17
247×2≡1mod17).

For
𝑚
3
=
19
m
3
​
 =19:

𝑀
3
=
4199
19
=
221
M
3
​
 =
19
4199
​
 =221
Find
𝑀
3
−
1
M
3
−1
​
  mod 19. Solving, we get
𝑀
3
−
1
=
8
M
3
−1
​
 =8 (as
221
×
8
≡
1
m
o
d
 
 
19
221×8≡1mod19).

Calculate
𝑥
x Using CRT Formula:

𝑥
=
𝑎
1
⋅
𝑀
1
⋅
𝑀
1
−
1
+
𝑎
2
⋅
𝑀
2
⋅
𝑀
2
−
1
+
𝑎
3
⋅
𝑀
3
⋅
𝑀
3
−
1
m
o
d
 
 
𝑀
x=a
1
⋅M1​
⋅M
1−1
​ +a2​ ⋅M2​ ⋅M2−1​ +a3
⋅M
3
⋅M
3−1​modMSubstitute values:

𝑥=(
12⋅
323⋅6)+(22⋅247⋅2)
+(9
⋅221⋅8)
mod  
4199x=(12⋅323⋅6)+(22⋅247⋅2)+(9⋅221⋅8)mod419
12⋅323
⋅6=
2325612⋅323⋅6=2325622⋅
247⋅2=
1086822⋅247⋅2=108689⋅221⋅8=159129⋅221⋅8=15912So
𝑥=(23256+10868+15912)mod 4199x=(23256+10868+15912)mod4199 𝑥=50036 mod 4199
x=50036mod4199
*/
int main()
{
    fast_io;
    int t;
    cin >> t;
    while (t--)
    {
        koxiaAndNumberTheory();
    }
    return 0;
}