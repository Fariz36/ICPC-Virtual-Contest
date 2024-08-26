#include <bits/stdc++.h>
using namespace std;

// Define Template          Python++
// Data Structure and Algorithm
#pragma region
#define all(vec)            (vec).begin(),(vec).end()
#define sortvec(vec)        sort(all(vec));
#define minvec(vec)         *min_element(all(vec))
#define maxvec(vec)         *max_element(all(vec))
#define uma(var,val)        var=max(var,(val));
#define umi(var,val)        var=min(var,(val));
#define sumvec(vec)         accumulate(all(vec),0LL)
#define reversevec(vec)     reverse(all(vec));
#define range(i,s,e)        for(int i=s;i<e;i++)
#define range2(i,s,e)       for(int i=s;i>=e;i--)
#define fors(var,arr)       for(auto &var:arr)
// Input Output Manage
#define debug(x)            cout<<(#x)<<" : "<<(x)<<endl;
#define test                cout<<"test"<<endl;
#define fastIO              ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define floatprecision      cout<<fixed<<setprecision(6);
#define fileread            freopen("input.txt","r",stdin);
#define fileout             freopen("output.txt","w",stdout);
#define query               cin>>QUERY;while(QUERY--)
#define inputvec(vec,am)    vector<int> vec(am);fors(num,vec)cin>>num;
#define inputmat(mat,n,m)   vector<vector<int>> mat(n, vector<int>(m, 0));range(i,0,n)range(j,0,m)cin>>mat[i][j];
#define input(var)          int var;cin>>var;
#define input2(a,b)         int a,b;cin>>a>>b;
#define inputp(var)         pair<int,int> var;cin>>var.first>>var.second;
#define inputs(var)         string var;cin>>var;
#define print(var)          cout<<(var)<<endl;
#define prints(var)         cout<<(var)<<" ";
#define print2(var1,var2)   cout<<(var1)<<" "<<(var2)<<endl;
#define printp(paired)      cout<<(paired.first)<<" "<<(paired.second)<<endl;
#define printyes(cond)      cout<<((cond)?"YES":"NO")<<endl;
#define printarr(arr)       fors(num,arr){cout<<num<<" ";};cout<<endl;
#define endline             cout<<endl;
#pragma endregion
// Macro
#pragma region
#define ll    long long
#define pb    push_back
#define pq    priority_queue
#define mp    make_pair
#define vi    vector<int>
#define pii   pair<int,int>
#define vpii  vector<pii>
#define vvi   vector<vector<int>>
#define mii   map<int,int>
// Oneliner Function
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll sigma(ll num){return num*(num+1)/2;}
ll gcd(ll a, ll b){return (a==0?b:gcd(b%a,a));}
ll lcm(ll a, ll b){return (a*b)/gcd(a,b);}
ll binpow(ll a,ll b,ll m=INT64_MAX){ll r=1;a%=m;while(b){if(b&1)r=(r*a)%m;a=(a*a)%m;b>>=1;}return r;}
ll invmod(ll a,ll m){return gcd(a,m)==1?binpow(a,m-2,m):0;}
ll random(ll l){return rng()%(l+1);}
ll random(ll a,ll b){ll w=b-a;return a+random(w);}
#pragma endregion
// More Macro
#pragma region
#define i32   int32_t
#define int   long long
#define float long double
int QUERY;
#pragma endregion
// Constant
const int MOD = 1e9+7;
const int MOD2 = 998244353;
const long long INF = 1e18;
const int maxn = 2e5+5;


struct val_type {
    int minval;
    val_type(int val = -1) {
        if (val == -1) {
            minval = INT_MAX;
        } else {
            minval = val;
        }
    }
};

val_type combine_val(val_type& a, val_type& b) {
    val_type ret;
    ret.minval = min(a.minval, b.minval);
    return ret;
}

struct segtreelazy{
    // generic segtree lazy template
    int n;
    vector<val_type> segment;
    vector<int> lazy;
    val_type init = val_type(); // initialize array value
    segtreelazy(int _n) {
        n = (_n == 1) ? 1 : (log2(_n-1) + 1);
        n = (1<<n);
        segment = vector<val_type>(2*n, init);
        lazy = vector<int>(2*n, 0);
    }
    segtreelazy(vector<int> array) {
        segtreelazy(array.size());
        build(array);
    }

    void build(vector<int> &array) {
        for(int i=0;i<array.size();i++) {
            segment[i+n] = val_type(array[i]);
        }
        for(int i=n-1;i>=1;i--) {
            segment[i] = combine_val(segment[2*i], segment[2*i+1]);
        }
    }

    void propagate(int idx) {
        if(lazy[idx] == 0)return ;
        int LOG = log2(idx);
        int mult = n / (1 << LOG); // add multiplier for sum query

        segment[idx].minval += lazy[idx];

        if(idx < n){ // not leaf
            lazy[2*idx] += lazy[idx];
            lazy[2*idx+1] += lazy[idx];
        }

        lazy[idx] = 0;
    }

    val_type& get(int idx){
        propagate(idx);
        return segment[idx];
    }

    void set(int idx, int val){
        idx += n;
        segment[idx].minval = val;
        for(idx/=2;idx>=1;idx/=2){
            segment[idx] = combine_val(segment[2*idx], segment[2*idx + 1]); 
        }
    }

    val_type range_query(int l, int r){return range_query(l,r,1,0,n-1);}
    val_type range_query(int l, int r, int idx, int sl, int sr) {
        if(l > sr || r < sl)return init; // out of range
        if(l <= sl && sr <= r)return get(idx);
        propagate(idx);
        int mid = (sl+sr)/2;

        val_type query_l = range_query(l, r, 2*idx, sl, mid);
        val_type query_r = range_query(l, r, 2*idx + 1, mid + 1, sr);

        return combine_val(query_l, query_r);
    }
};

void salah() {
    // vi v(n + 1, INF);
    // segtreelazy st(v);
    // st.set(0, 0);
    // auto walk_on_tree = [&](int val) {
    //     // find maximum index satisfy val > a[i]
    //     int idx = 1;
    //     while(idx < n) {
    //         idx *= 2;
    //         int left = get(idx);
    //         if(left != minall) {
    //             // go to right
    //             idx++;
    //             propagate(idx);
    //         }
    //     }
    //     return idx - n;
    // }

}

int32_t main() {
    fastIO

    input(n)
    inputvec(a, n)

    
    vector<int> pref(n + 1);
    for(int i=0;i<n;i++) {
        pref[i + 1] = pref[i] + a[i];
    }

    vi dp(n + 1);
    range(i,0,n + 1) {
        dp[i] = pref[i];
    }

    vector<pii> dp2; // {- (dp[idx] + pref[idx]), idx}
    dp2.emplace_back(-0, 0);

    range(i,1,n + 1) {
        pii key = {-pref[i], 0};
        auto it = upper_bound(dp2.rbegin(), dp2.rend(), key);
        int prefi = pref[(*it).second];
        dp[i] = pref[i] - prefi;

        // printp(key)
        // printp((*it))
        // fors(p, dp2) {
        //     prints(p.first)
        // }
        // endline
        // endline

        int nval = pref[i] + dp[i];
        while(!dp2.empty() && -dp2.back().first > nval) {
            dp2.pop_back();
        }

        dp2.emplace_back(-nval, i);
    }

    // printarr(dp)

    int ans = INF;
    int sumback = 0;
    range2(i,n-1,0) {
        sumback += a[i];
        umi(ans, max(sumback, dp[i]))
    }
    print(ans)


    return 0;
}
