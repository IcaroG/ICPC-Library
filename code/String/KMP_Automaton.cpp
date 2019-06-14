int pre[ms][limit];
int fail[ms];

void build_automaton(string s){
    s += '#'; //diferente de todos caracteres
    int n = (int) s.size();
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < limit; ++j){
            if(i == 0){
                if(s[i] == j + 'a'){
                    pre[i][j] = i + 1;
                }else{
                    pre[i][j] = 0;
                }
            }else{
                if(s[i] == j + 'a'){
                    pre[i][j] = i + 1;
                }else{
                    pre[i][j] = pre[fail[i - 1]][j];
                }
            }
        }
        if(i == 0) continue;
        int j = fail[i - 1];
        while(j > 0 && s[i] != s[j]) {
            j = fail[j - 1];
        }
        fail[i] = j + (s[i] == s[j]);
    }
}
