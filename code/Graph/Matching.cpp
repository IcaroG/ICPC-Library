// ADACITY - Matching

#include <bits/stdc++.h>

using namespace std;
const int INF = 0x3f3f3f3f;
const int MAXN = 500 + 7;

int friends[MAXN], match[MAXN], adj[MAXN][MAXN];
bool vis[MAXN];
vector<int> v[MAXN];
int n, m, f, t;

int solve(int u) {
  if(vis[u]) return 0;
  vis[u] = true;
  for(int i = 0; i < v[u].size(); i++) {
    int w = v[u][i];
    if(match[w] == -1 || solve(match[w])) {
      match[w] = u;
      return 1;
    }
  }
  return 0;
}

void clear() {
  for(int i = 1; i <= MAXN; i++) {
    v[i].clear();
  }
  for(int i = 1; i <= MAXN; i++) {
    for(int j = 1;j <= MAXN; j++) {
      adj[i][j] = INF;
    }
    adj[i][i] = 0;
  }
  memset(match, -1, sizeof(match));
}

int main() {
  int tc;
  cin >> tc;
  while(tc--) {
    cin >> n >> m >> f >> t;
    clear();
    for(int i = 1; i <= f; i++) {
      cin >> friends[i];   
    }
    for(int i = 1; i <= m; i++) {
      int u, v, w;
      cin >> u >> v >> w;
      adj[u][v] = min(adj[u][v], w);
      adj[v][u] = min(adj[v][u], w);
    }
    for(int k = 1; k <= n; k++) {
      for(int i = 1; i <= n; i++) {
        for(int j = 1;j <= n; j++) {
          adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
        }
      }
    }
    for(int i = 1; i <= f; i++) {
      for(int j = 1; j <= n; j++) {
        if(adj[friends[i]][j] <= t) {
          v[i].push_back(j);
        }
      }
    }
    int ans = 0;
    for(int i = 1; i <= f; i++) {
      memset(vis, false, sizeof(vis));
      ans += solve(i);
    }
    cout << ans << '\n';
  }
}