int spf[MAXN]; 

// Complexity: O(nloglogn)
void sieve() {
  spf[1] = 1;
  for (int i = 2; i < MAXN; i++) {
    if (!spf[i]) {
      for (int j = i; j < MAXN; j += i) {
        if (!spf[j]) spf[j] = i;
      }
    }
  }
}

// Complexity: O(log n)
vector<int> getFactors(int n) {
  vector<int> ans;
  while (n != 1) {
    ans.push_back(spf[n]);
    n = n / spf[n];
  }
  return ans;
}
