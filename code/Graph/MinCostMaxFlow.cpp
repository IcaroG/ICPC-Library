#include <bits/stdc++.h>

using namespace std;
const int INF = 1e9 + 7;

struct Edge{
  int from, to, capacity, cost;
  Edge(int from, int to, int capacity, int cost) : from(from), to(to), capacity(capacity), cost(cost) {}
};

vector<Edge> edges;
vector<vector<int>> adj, cost, capacity;

void shortest_paths(int n, int s, vector<int>& d, vector<int>& p) {
  d.assign(n, INF);
  d[s] = 0;
  vector<int> m(n, 2);
  deque<int> q;
  q.push_back(s);
  p.assign(n, -1);
  
  while (!q.empty()) {
    int u = q.front();
    q.pop_front();
    m[u] = 0;
    for (int v : adj[u]) {
      if (capacity[u][v] > 0 && d[v] > d[u] + cost[u][v]) {
        d[v] = d[u] + cost[u][v];
        p[v] = u;
        if (m[v] == 2) {
          m[v] = 1;
          q.push_back(v);
        } else if (m[v] == 0) {
          m[v] = 1;
          q.push_front(v);
        }
      }
    }
  }
}

int min_cost_flow(vector<Edge> edges, int K, int s, int t) {
  int N = edges.size();
  adj.assign(N, vector<int>());
  cost.assign(N, vector<int>(N, 0));
  capacity.assign(N, vector<int>(N, 0));
  for (Edge e : edges) {
    adj[e.from].push_back(e.to);
    adj[e.to].push_back(e.from);
    cost[e.from][e.to] = e.cost;
    cost[e.to][e.from] = -e.cost;
    capacity[e.from][e.to] = e.capacity;
  }

  int flow = 0;
  int cost = 0;
  vector<int> d, p;
  while (flow < K) {
    shortest_paths(N, s, d, p);
    if (d[t] == INF) break;

    int f = K - flow;
    int cur = t;
    while (cur != s) {
      f = min(f, capacity[p[cur]][cur]);
      cur = p[cur];
    }

    flow += f;
    cost += f * d[t];
    cur = t;
    while (cur != s) {
      capacity[p[cur]][cur] -= f;
      capacity[cur][p[cur]] += f;
      cur = p[cur];
    }
  }
  
  if (flow < K) return -1;
  else return cost;
}

int main() {
  
  return 0;
}
