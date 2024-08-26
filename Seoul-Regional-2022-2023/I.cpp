#include <bits/stdc++.h>
using namespace std;

#define int long long
#define ii pair<int, int>
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define vi vector<int>
#define vii vector<ii>
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define rep(i, a, b) for (int i = a; i < b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
#define endl '\n'
#define sz(x) (int)x.size()

const int mod = 998244353;
const int N = 100069;

vector<int> arr(N), brr(N);
int n;
string s;

int f(int l, int r, int k) {
  if (k == 4) return 1e18;
  if (l >= r) return k;
  if (s[l] == s[r]) return f(l+1, r-1, k);

  return min(f(l+1, r, k+1), f(l, r-1, k+1));
}

void solve() {
    cin >> s;

    int n = s.length();
    int ans = f(0, n-1, 0);

    if (ans >= 4) cout << "-1" << endl;
    else cout << ans << endl;
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int tc = 1;
  //cin >> tc;
  
  while (tc--) {
    solve();
  }
}