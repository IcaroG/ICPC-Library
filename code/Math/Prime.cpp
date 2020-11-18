vector<int> prime;
bool notPrime[ms];

//O(nlogn)
void sieve() {
  for(int i = 2; i < ms; ++i) {
    if(!notPrime[i]) {
      prime.push_back(i);
      for(int j = 2 * i; j < ms; j += i) {
        notPrime[j] = true;
      }
    }
  }
}

vector<int> fact(int x) {
  vector<int> ans;
  int idx = 0, pf = prime[idx];
  while(pf * pf <= x) {
    while(x % pf == 0) {
      x /= pf;
      ans.push_back(pf);
    }
    pf = prime[++idx];
  }
  if(x != 1) {
    ans.push_back(x);
  }
  return ans;
}
