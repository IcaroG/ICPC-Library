struct Matrix{
    long long mat[m][m];

    Matrix operator * (const Matrix &p){
        Matrix ans;
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < m; ++j){
                for(int k = ans.mat[i][j] = 0; k < m; ++k){
                    ans.mat[i][j] = (ans.mat[i][j] + (mat[i][k] * p.mat[k][j]) % mod) % mod;
                }
            }
        }
        return ans;
    }
};

Matrix fExp(Matrix a, long long b){
    Matrix ans;
    for(int i = 0; i < m; ++i) for(int j = 0; j < m; ++j) ans.mat[i][j] = (i == j);

    while(b){
        if(b & 1) ans = ans * a;
        a = a*a;
        b >>= 1;
    }
    return ans;
}
