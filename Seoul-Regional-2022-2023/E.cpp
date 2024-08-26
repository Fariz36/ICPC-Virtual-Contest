#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ld long double

struct node{
    ll D; int cur, pr;

    bool operator < (const node &other) const {
        return D > other.D;
    }
};

vector<pair<int, ll>> adj[30001];
vector<int> bef[30001];
set<int> forbidden[30001][10];
bool vis[30001][11];
ll dist[30001][11];

void solve(){
    int M, N, F; cin >> M >> N >> F;

    int st, ed; cin >> st >> ed;

    for(int i = 1; i <= M; ++i){
        int u, v; ll w; cin >> u >> v >> w;

        adj[v].push_back({u, w});
        bef[u].push_back(v);
    }

    for(int i = 0; i < N; ++i){
        sort(bef[i].begin(), bef[i].end());
        for(int j = 0; j < (int)bef[i].size(); ++j){
            dist[i][j] = 1e18;
        }
    }

    for(int i = 1; i <= F; ++i){
        int x, y, z; cin >> x >> y >> z;

        int index = lower_bound(bef[y].begin(), bef[y].end(), z) - bef[y].begin();

        forbidden[y][index].insert(x);
    }

    if(st == ed){
        cout << "0\n";
        return;
    }

    priority_queue<node> pq;
    pq.push({0, ed, 10});
    dist[ed][10] = 0;

    while(!pq.empty()){
        ll D = pq.top().D; int cur = pq.top().cur, pr = pq.top().pr;
        pq.pop();

        if(vis[cur][pr]){
            continue;
        }
        vis[cur][pr] = 1;

        //cout << D << " " << cur << " " << pr << "\n";

        for(auto nx : adj[cur]){
            int to = nx.first; ll len = nx.second;
            int index = lower_bound(bef[to].begin(), bef[to].end(), cur) - bef[to].begin();
            if(!forbidden[cur][pr].count(to)){
                if(dist[to][index] > D + len){
                    dist[to][index] = D + len;
                    pq.push({dist[to][index], to, index});
                }
            }
        }
    }

    ll answer = 1e18;
    for(int i = 0; i < (int)bef[st].size(); ++i){
        answer = min(answer, dist[st][i]);
    }

    cout << (answer >= 1e18 ? -1 : answer) << "\n";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int tc = 1; //cin >> tc;

    while(tc--){
        solve();
    }

    return 0;
}
