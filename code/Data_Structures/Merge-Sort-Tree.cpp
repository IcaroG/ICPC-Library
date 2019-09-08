const int mx = 512345;
vector<long long> tree[2*mx];
int n;
void init() {
	for(int i = n - 1; i >= 1; i--) {
	merge(all(tree[i + i]), all(tree[i + i + 1]), back_inserter(tree[i]));
	}
}
// Count the numbers in range [l, r] smaller or equal to k
int get(int l, int r, long long k) {
	int ans = 0; //colocar a base
	for(l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
		if (l & 1) {
			ans += upper_bound(all(tree[l]), k) - tree[l].begin();
			l++;
		}
		if (r & 1) {
			r--;
			ans += upper_bound(all(tree[r]), k) - tree[r].begin();
		}
	}
	return ans;
}

int main() {
	cin >> n;
	vector<ll> v(n);
	for (int i = n; i < 2*n; i++) {
		cin >> v[i - n];
		tree[i].push_back(v[i - n]);
	}
  init();
  //get(0, n - 1, x);
}
