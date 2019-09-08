const int K = 3;
long long MOD = 1e9 + 9;
long long F1[K+1], T[K+1][K+1];

void mul(long long (&A)[K+1][K+1], long long B[K+1][K+1]){
	long long C[K+1][K+1];
	memset(C, 0, sizeof(C));
	for (int i = 0; i < K; i++) {
		for (int j = 0; j < K; j++) {
			for (int k = 0; k < K; k++) {
				C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
			}
		}
	}
	for (int i = 0; i < K; i++) {
		for (int j = 0; j < K; j++) {
			A[i][j] = C[i][j] % MOD;
		}
	}
}

void pow(long long (&A)[K+1][K+1], long long p){
	long long r[K+1][K+1];
	for (int i = 0; i < K; i++) {
		for (int j = 0; j < K; j++) {
			r[i][j] = (i == j);
		}
	}
	while(p) {
		if (p & 1) mul(r, A);
		mul(A, A);
		p = p >> 1;
	}
	for (int i = 0; i < K; i++) {
		for (int j = 0; j < K; j++) {
			A[i][j] = r[i][j];
		}
	}
}
