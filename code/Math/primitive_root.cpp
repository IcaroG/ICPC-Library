int fexp(int x, int y, int p){
  int ans = 1;
  x = x % p;
  while (y) {
    if (y & 1) ans = (ans * x) % p;
    x = (x * x) % p;
    y = y >> 1;
  }
  return ans;
}
// If p has a primitive root, then there are phi(phi(p)) primitives roots of p
int get(int p) {
  vector<int> factors;
  int phi = p - 1; // phi(n)
  int n = phi;
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      factors.push_back(i);
      while (n % i == 0) n /= i;
    }
  }
  if (n > 1) factors.push_back(n);
  for (int i = 2; i <= p; i++) {
    bool ok = true;
    for (int j = 0; j < factors.size() && ok; j++) {
      ok &= (fexp(i, phi / factors[j], p) != 1);
    }
    if (ok) return i;
  }
  return -1;
}
