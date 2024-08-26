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


struct DSU{
    vector<int> link, size;
    int n, component;
    DSU(int length){
        n = length;
        component = length;
        link = vector<int>(n+1);
        size = vector<int>(n+1, 1);
        iota(link.begin(), link.end(), 0);
    }

    int find(int x){ // O(log(n))
        if(x != link[x])link[x] = find(link[x]);
        return link[x];
    }

    void unite(int a,int b){ // O(log(n))
        a=find(a);
        b=find(b);
        if(a==b)return;
        if(size[a]<size[b])swap(a,b);
        size[a]+=size[b];
        link[b]=a;
        component--;
    }
};

bool check_combine(pii i1, pii i2) {
    return i1.second >= i2.first;
}

int32_t main() {
    fastIO

    input2(n, m)
    DSU dsu(n);

    vpii intervals(n);
    map<int, pii> comp_interval;
    range(i,0,n) {
        cin >> intervals[i].first >> intervals[i].second;
        comp_interval[i] = intervals[i];
    }

    auto update_interval = [&](pii& i1, pii& i2) {
        umi(i1.first, i2.first)
        uma(i1.second, i2.second)
    };

    range(i,0,n - 1) {
        int comp1 = dsu.find(i);
        if (check_combine(comp_interval[comp1], intervals[i + 1])) {
            dsu.unite(i, i + 1);
        }

        int comp2 = dsu.find(i + 1);

        // update_interval(comp_interval[comp1], intervals[i]);
        update_interval(comp_interval[comp2], intervals[i + 1]);
    }

    // range(i,0,n) {
    //     prints(dsu.find(i))
    // }
    // endline

    vi used;
    vi indexing(n, -1);
    used.push_back(dsu.find(0));
    indexing[0] = 0;
    range(i,0,n) {
        int comp = dsu.find(i);
        if (used.back() != comp) {
            indexing[comp] = used.size();
            used.push_back(comp);
        }
    }

    int usz = used.size();
    vector<int> pref(usz + 1);
    for(int i=0;i<usz - 1;i++) {
        int dist = comp_interval[used[i + 1]].first - comp_interval[used[i]].second;
        pref[i + 1] = pref[i] + dist;
    }

    // printarr(pref)

    auto get_dist = [&](int comp1, int comp2) {
        if (comp1 > comp2) {
            swap(comp1, comp2);
        }

        int idx1 = indexing[comp1];
        int idx2 = indexing[comp2];

        int dist = pref[idx2] - pref[idx1];
        return dist;
    };

    inputvec(a, m)
    int ans = 0;
    int comp = dsu.find(0);
    fors(nxt, a) {
        int nxtcomp = dsu.find(nxt - 1);

        int dist = get_dist(comp, nxtcomp);
        ans += dist;

        // print2(comp + 1, nxtcomp + 1)
        // print(dist)

        comp = nxtcomp;
    }

    print(ans)


    return 0;
}