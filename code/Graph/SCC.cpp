vector<int> g[ms];
int idx[ms], low[ms], z, comp[ms], ncomp, n;

stack<int> st;
// Operacoes comuns de 2-sat
int NOT(int x) { return x < n ? x + n : x - n; }
void add(int a, int b) { g[a].push_back(b); }
void addOr(int a, int b) { add(NOT(a), b); add(NOT(b), a); }
void addImp(int a, int b) { addOr(NOT(a), b); }
void addEqual(int a, int b) { addOr(a, NOT(b)); addOr(NOT(a), b); }
void addDiff(int a, int b) { addEqual(a, NOT(b)); }
// valoracao: value[v] = comp[trad(v)] < comp[trad(~v)]

int dfs(int u) {
    if(~idx[u]) return idx[u] ? idx[u] : z;
    low[u] = idx[u] = z++;
    st.push(u);
    for(int v : g[u]) {
        low[u] = min(low[u], dfs(v));
    }
    if(low[u] == idx[u]) {
        while(st.top() != u) {
            int v = st.top();
            idx[v] = 0;
            low[v] = low[u];
            comp[v] = ncomp;
            st.pop();
        }
        idx[st.top()] = 0;
        st.pop();
        comp[u] = ncomp++;
    }
    return low[u];
}

bool solveSat() {
    memset(idx, -1, sizeof idx);
    z = 1; ncomp = 0;
    for(int i = 0; i < 2*n; i++) dfs(i);
    for(int i = 0; i < n; i++) if(comp[i] == comp[NOT(i)]) return false;
    return true;
}

