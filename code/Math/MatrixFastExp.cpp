const int mod = 1e9 + 7;
const int mx = 205;

struct Matrix{
    int sz;
    vector<vector<int>> mat;

    Matrix(int _sz = 0) {
        sz = _sz;
        mat = vector<vector<int>>(sz, vector<int>(sz, 0));
    }

    Matrix operator * (const Matrix &p){
        Matrix ans(sz);
        for(int i = 0; i < sz; ++i){
            for(int j = 0; j < sz; ++j){
                for(int k = ans.mat[i][j] = 0; k < sz; ++k){
                    ans.mat[i][j] = (ans.mat[i][j] + (mat[i][k] * p.mat[k][j]) % mod) % mod;
                }
            }
        }
        return ans;
    }
};

Matrix fExp(Matrix a, long long b){
    Matrix ans(a.sz);
    for(int i = 0; i < a.sz; ++i) for(int j = 0; j < a.sz; ++j) ans.mat[i][j] = (i == j);

    while(b){
        if(b & 1) ans = ans * a;
        a = a*a;
        b >>= 1;
    }
    return ans;
}

// precompute
for(int k = 1;k <= 62;k++){
    memcpy(T[k], T[k-1], sizeof(T[k-1]));
    T[k] = T[k] * T[k];
}
for(int i = 0; i < 63 && (1LL<<i) <= N; i++){
	if(N&(1LL<<i)) S = S * T[i];
}
