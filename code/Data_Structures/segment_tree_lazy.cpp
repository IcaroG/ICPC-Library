int tree[4*MAXN], lazy[4*MAXN];

void build(int on = 1, int l = 0, int r = n - 1) {
  lazy[on] = 0;
  if (l == r) {
    tree[on] = a[l];
    return;
  }
  int mid = (l + r) / 2;
  build(2 * on, l, mid);
  build(2 * on + 1, mid + 1, r);
  tree[on] = tree[2*on] | tree[2*on + 1];
}

void propagate(int on, int l, int r) {
  if (lazy[on]) {
    tree[on] = lazy[on];
    if (l != r) {
      lazy[2 * on] = lazy[on];
      lazy[2 * on + 1] = lazy[on];
    }
    lazy[on] = 0;
  }
}

int query(int left, int right, int on = 1, int l = 0, int r = n - 1) {
  propagate(on, l, r);
  if (right < l || left > r) return 0;
  if (l >= left && r <= right) {
    return tree[on];
  }
  int mid = (l + r) / 2;
  int x = query(left, right, 2 * on, l, mid);
  int y = query(left, right, 2 * on + 1, mid + 1, r);
  return x | y;
}

void update(int left, int right, int val, int on = 1, int l = 0, int r = n - 1) {
  propagate(on, l, r);
  if (right < l || left > r) return;
  if (l >= left && r <= right) {
    lazy[on] = val;
    propagate(on, l, r);
    return;
  }
  int mid = (l + r) / 2;
  update(left, right, val, 2 * on, l, mid);
  update(left, right, val, 2 * on + 1, mid + 1, r);
  tree[on] = tree[2*on] | tree[2*on + 1];
}
