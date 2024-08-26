#include <bits/stdc++.h>
using namespace std;

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
const int N = 505;

int arr[N];
int p1[N], p2[N];
int one = 1;

void solve() {
    int n, p, q;
    cin >> n >> p >> q;

    map<string, int> mp;
    int now = 1;

    int dp[n+5][p+5][q+5];
    memset(dp, 0, sizeof dp);

    for (int i = 1; i <= n; i++) {
      string s;
      cin >> s;

      if (mp.find(s) == mp.end()) {
        mp[s] = now++;
      }
      arr[i] = mp[s];
    }

    for (int i = 1; i <= p; i++) {
      string s;
      cin >> s;

      p1[i] = mp[s];
    }

    for (int i = 1; i <= q; i++) {
      string s;
      cin >> s;

      p2[i] = mp[s];
    }

    for (int i = 1; i <= n; i++) {
      for (int j = 0; j <= p; j++) {
        for (int k = 0; k <= q; k++) {
          dp[i][j][k] = dp[i-1][j][k];
          
          if (j != 0) dp[i][j][k] = max(dp[i][j][k], dp[i][j-1][k]);
          if (k != 0) dp[i][j][k] = max(dp[i][j][k], dp[i][j][k-1]);

          if (p1[j] == arr[i]) dp[i][j][k] = max(dp[i][j][k], dp[i-1][j-1][k] + one);
          if (p2[k] == arr[i]) dp[i][j][k] = max(dp[i][j][k], dp[i-1][j][k-1] + one);
        }
      }
    }

    cout << dp[n][p][q] << endl;
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