int b[ms];

void kmpPreprocess(string p) {
    int m = p.size();
    int i = 0, j = -1;
    b[0] = -1;
    while(i < m) {
        while(j >= 0 && p[i] != p[j]) j = b[j];
        b[++i] = ++j;
    }
}

int kmpSearch(string p, string s) {
    int n = s.size(), m = p.size();
    int i = 0, j = 0, ans = 0;
    while(i < n) {
        while(j >= 0 && s[i] != p[j]) j = b[j];
        i++; j++;
        if(j == m) {
            //ocorrencia aqui comecando em i - j
            ans++;
            j = b[j];
        }
    }
    return ans;
}
