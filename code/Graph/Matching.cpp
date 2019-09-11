// ADACITY - Matching
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
