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
const int N = 50;

char arr[N][N];
char temp[N][N];
int state[N][N][N][N];
bool visited[N][N][N][N];

int solve(int x1, int y1, int x2, int y2) {
  if (x1 > x2 || y1 > y2) {
    //cout << x1 << " " << y1 << " " << x2 << " " << y2 << " " << 0 << endl;
    return 0;
  }
  if (visited[x1][y1][x2][y2]) return state[x1][y1][x2][y2];

  unordered_map<int, bool> mp;
  for (int i = x1; i <= x2; i++) {
    for (int j = y1; j <= y2; j++) {
      if (arr[i][j] == '.') continue;

      if (arr[i][j] == 'R') {
        int a = solve(x1, y1, i-1, y2) ^ solve(i+1, y1, x2, y2);
        mp[a] = true;
      }

      if (arr[i][j] == 'B') {
        int a = solve(x1, y1, x2, j-1) ^ solve(x1, j+1, x2, y2);
        mp[a] = true;
      }

      if (arr[i][j] == 'G') {
        int a = solve(x1, y1, i-1, j-1);
        int b = solve(x1, j+1, i-1, y2);
        int c = solve(i+1, y1, x2, j-1);
        int d = solve(i+1, j+1, x2, y2);

        mp[(a^b)^(c^d)] = true;
      }
    }
  }

  int mex = 0;
  while (mp[mex]) mex++;

  //cout << x1 << " " << y1 << " " << x2 << " " << y2 << " " << mex << endl;

  visited[x1][y1][x2][y2] = true;
  return state[x1][y1][x2][y2] = mex;
}

void solve() {
    int n, m;
    cin >> n >> m;
    
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        temp[i][j] = '.';
        arr[i][j] = '.';
      }
    }

    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        cin >> temp[i][j];
      }
    }

    int initx = 1, inity = 13;
    for (int i = 1; i < N; i+=2) {
      int now = i;
      int x = initx, y = inity;
      for (int j = 1; j <= i; j++) {
        if (now < 1 || j > N) arr[x][y] = 'x';
        else arr[x][y] = temp[now][j];
        y++;
        now--;
      }

      initx++;
      inity--;
    }

    int ans1 = solve(1, 1, 25, 25);

    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        arr[i][j] = '.';
        
        for (int k = 0; k < N; k++) {
          for (int l = 0; l < N; l++) {
            state[i][j][k][l] = 0;
            visited[i][j][k][l] = false;
          }
        }
      }
    }

    initx = 1, inity = 13;
    for (int i = 2; i < N; i+=2) {
      int now = i;
      int x = initx, y = inity;
      for (int j = 1; j <= i; j++) {
        if (now < 1 || j > N) arr[x][y] = 'x';
        else arr[x][y] = temp[now][j];
        y++;
        now--;
      }

      initx++;
      inity--;
    }

    int ans2 = solve(1, 1, 25, 25);
    
    //cout << ans1 << " " << ans2 << endl;
    if ((ans1^ans2) == 0) cout << "L" << endl;
    else cout << "W" << endl;
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