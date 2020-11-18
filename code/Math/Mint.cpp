const int mod = 1e9 + 9;
const int ms = 1e5 + 5;

template <class T>
T fexp(T x, long long e) {
  T ans(1);
  for(; e > 0; e /= 2) {
    if(e & 1) ans = ans * x;
    x = x * x;
  }
  return ans;
}

struct Mint {
  Mint(int v = 0) : val(v < 0 ? v + mod : v) {}
  int val;

  void operator+=(Mint o) { *this = *this + o; }
  void operator-=(Mint o) { *this = *this - o; }
  void operator*=(Mint o) { *this = *this * o; }
  Mint operator*(Mint o) { return (int)((long long)val * o.val % mod); }
  //Mint operator / (Mint o) { return *this * fexp(o, mod - 2); }
  Mint operator+(Mint o) { return val + o.val >= mod ? val + o.val - mod : val + o.val; }
  Mint operator-(Mint o) { return val - o.val < 0 ? val - o.val + mod : val - o.val; }

  friend std::ostream &operator<<(std::ostream &os, const Mint &p) {
    return os << p.val;
  }
  friend std::istream &operator>>(std::istream &is, Mint &p) {
    return is >> p.val;
  }
};

Mint fat[ms], ifat[ms];
void initComb() {
  fat[0] = 1;
  for(int i = 1; i < ms; i++) {
    fat[i] = fat[i - 1] * i;
  }
  ifat[ms - 1] = fexp(fat[ms - 1], mod - 2);
  for(int i = ms - 1; i > 0; i--) {
    ifat[i - 1] = ifat[i] * i;
  }
}

Mint comb(int n, int a) { return a < 0 || a > n ? Mint(0) : fat[n] * ifat[a] * ifat[n - a]; }
