struct LazyContext {
  LazyContext() {
    add = 0;
    dirty = 0;
  }

  LazyContext(long long c) {
    add = c;
    dirty = 1;
  }

  void reset() {
    add = 0;
    dirty = 0;
  }

  void operator+=(LazyContext o) {
    add += o.add;
    dirty = 1;
  }

  long long add;
  bool dirty;
};

struct Node {
  Node() {
    sum = 0;
  }

  Node(long long c) {
    sum = c;
  }

  Node(Node &l, Node &r) {
    sum = l.sum + r.sum;
  }

  void apply(LazyContext lazy, int l, int r) {
    sum += (r - l + 1) * lazy.add;
  }

  long long sum;
};

Node tree[4 * ms];
LazyContext lazy[4 * ms];
int n;

void build(int on = 1, int l = 0, int r = n - 1) {
  lazy[on] = LazyContext(0);
  if(l == r) {
    tree[on] = Node(a[l]);
    return;
  }
  int mid = (l + r) / 2;
  build(2 * on, l, mid);
  build(2 * on + 1, mid + 1, r);
  tree[on] = Node(tree[2 * on], tree[2 * on + 1]);
}

void propagate(int on, int l, int r) {
  if(lazy[on].dirty) {
    tree[on].apply(lazy[on], l, r);
    if(l != r) {
      lazy[2 * on] += lazy[on];
      lazy[2 * on + 1] += lazy[on];
    }
    lazy[on].reset();
  }
}

Node query(int left, int right, int on = 1, int l = 0, int r = n - 1) {
  propagate(on, l, r);
  if(right < l || left > r) return 0;
  if(l >= left && r <= right) {
    return tree[on];
  }
  int mid = (l + r) / 2;
  Node x = query(left, right, 2 * on, l, mid);
  Node y = query(left, right, 2 * on + 1, mid + 1, r);
  return Node(x, y);
}

void update(int left, int right, LazyContext val, int on = 1, int l = 0, int r = n - 1) {
  propagate(on, l, r);
  if(right < l || left > r) return;
  if(l >= left && r <= right) {
    lazy[on] += val;
    propagate(on, l, r);
    return;
  }
  int mid = (l + r) / 2;
  update(left, right, val, 2 * on, l, mid);
  update(left, right, val, 2 * on + 1, mid + 1, r);
  tree[on] = Node(tree[2 * on], tree[2 * on + 1]);
}
