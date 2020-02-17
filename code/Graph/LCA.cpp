int par[ms][mlg + 1], h[ms];
vector<int> g[ms];

void dfs(int v = 0, int p = 0){ // chamar dfs(parent, parent)
    par[v][0] = p;
    for(int k = 1; k <= mlg; ++k){
        par[v][k] = par[par[v][k-1]][k-1];
    }
    for(auto u : g[v]){
        if(u != p){
            h[u] = h[v] + 1;
            dfs(u, v);
        }
    }
}

int lca(int a, int b){
    if(h[b] > h[a]) swap(a, b);
    for(int i = mlg; i >= 0; --i){
        if(h[a] - (1 << i) >= h[b]) a = par[a][i];
    }

    if(a == b) return a;

    for(int i = mlg; i>= 0; --i){
        if(par[a][i] != par[b][i]) a = par[a][i], b = par[b][i];
    }
    return par[a][0];
}
