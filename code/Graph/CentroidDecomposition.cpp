const int ms = 1e5 + 7;

vector<int> g[ms];
int parent[ms], sz[ms], removed[ms];

void dfsSubtree(int u, int p) {
  sz[u] = 1;
  for (auto v : g[u]) {
    if (v != p && !removed[v]) {
      dfsSubtree(v, u);
      sz[u] += sz[v];
    }
  }
}

int getCentroid(int u, int p, int size) {
  for (auto v : g[u]) {
    if (v != p && !removed[v] && sz[v] * 2 >= size) return getCentroid(v, u, size);
  }
  return u;
}

void decompose(int u, int p) {
  dfsSubtree(u, -1);
  int ctr = getCentroid(u, -1, sz[u]); 
  if (p == -1) {
    p = ctr;
  }
  parent[ctr] = p;
  removed[ctr] = 1;
  for (auto v : g[ctr]) {
    if (v != p && !removed[v]) {
      decompose(v, ctr);
    }
  }
}
