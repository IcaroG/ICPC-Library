//HLD + ETT by adamant http://codeforces.com/blog/entry/53170
//query of path and subtree of p (in[p], out[p]) [l, r)
int sz[ms], par[ms], h[ms];
int t, in[ms], out[ms], rin[ms], nxt[ms];

void dfs_sz(int v = 0, int p = -1){
    sz[v] = 1;
    for(int i = 0; i < g[v].size(); ++i){
        int &u = g[v][i];
        if(u == p) continue;
        h[u] = h[v]+1, par[u] = v;
        dfs_sz(u, v);
        sz[v] += sz[u];
        if(g[v][0] == p || sz[u] > sz[g[v][0]]){
            swap(u, g[v][0]);
        }
    }
}

void dfs_hld(int v = 0, int p = -1){
    in[v] = t++;
    rin[in[v]] = v;
    for(auto u : g[v]){
        if(u == p) continue;
        nxt[u] = u == g[v][0] ? nxt[v] : u;
        dfs_hld(u, v);
    }
    out[v] = t;
}

int up(int v){
    return (nxt[v] != v) ? nxt[v] : (~par[v] ? par[v] : v); 
}

int getLCA(int a, int b){
    while(nxt[a] != nxt[b]){
        if(h[a] == 0 || h[up(a)] < h[up(b)]) swap(a, b);
        a = up(a);
    }
    return h[a] < h[b] ? a : b;
}

vector<ii> getPathAncestor(int a, int anc){
    vector<ii> ans;
    while(nxt[a] != nxt[anc]){
        ans.emplace_back(in[nxt[a]], in[a]);
        a = par[nxt[a]];
    }
    ans.emplace_back(in[anc], in[a]);
    return ans;
}

int queryPath(int a, int b){
    int res = 0;
    while(nxt[a] != nxt[b]){
        if(h[nxt[a]] > h[nxt[b]]) swap(a, b);
        int cur = qry(in[nxt[b]], in[b]).maxi;
        res = max(res, cur);
        b = par[nxt[b]];
    }
    if(h[a] > h[b]) swap(a, b);
    int cur = qry(in[a], in[b]).maxi; // in[a] + 1 dont include LCA
    res = max(res, cur);
    
    return res;
}
