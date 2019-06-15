int pre[ms][limit];

void build_automaton(string s){
    int n = (int) s.size();
    for(int i = 0; i < limit; ++i){
        pre[0][i] = 0;
    }
    pre[0][s[0] - 'A'] = 1;
    int fail = 0;
    for(int i = 1; i <= n; ++i){
        for(int j = 0; j < limit; ++j){
            pre[i][j] = pre[fail][j];
        }
        if(i == n) continue;
        pre[i][s[i] - 'A'] = i + 1;
        fail = pre[fail][s[i] - 'A'];
    }
}
