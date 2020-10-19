struct LazyContext {
    LazyContext() {

    }
    
    LazyContext(long long c) {
        
    }

    void reset() {

    }

    void operator += (LazyContext o) {

    }
};

struct Node {
    Node() {

    }

    Node(long long c) {

    }

    Node(Node &l, Node &r) {

    }

    void apply(LazyContext lazy) {

    }
};

Node tree[2*ms];
LazyContext lazy[ms];
bool dirty[ms];
int n, lg, a[ms];

void init() {
    lg = 0;
    while((1 << lg) < n) lg++;
    for(int i = 0; i < n; i++) {
        tree[i + n] = Node(a[i]);
    }
    for(int i = n - 1; i > 0; i--) {
        tree[i] = Node(tree[i + i], tree[i + i + 1]);
        lazy[i].reset();
        dirty[i] = 0;
    }
}

void apply(int p, LazyContext &lc) {
    tree[p].apply(lc);
    if(p < n) {
        dirty[p] = true;
        lazy[p] += lc;
    }
}

void push(int p) {
    for(int s = lg; s > 0; s--) {
        int i = p >> s;
        if(dirty[i]) {
            apply(i + i, lazy[i]);
            apply(i + i + 1, lazy[i]);
            lazy[i].reset();
            dirty[i] = false;
        }
    }
}

void build(int p) {
    for(p /= 2; p > 0; p /= 2) {
        tree[p] = Node(tree[p + p], tree[p + p + 1]);
        if(dirty[p]) {
            tree[p].apply(lazy[p]);
        }
    }
}

Node qry(int l, int r) {
    if(l > r) return Node();
    l += n, r += n+1;
    push(l);
    push(r - 1);
    Node lp, rp;
    for(; l < r; l /= 2, r /= 2) {
        if(l & 1) lp = Node(lp, tree[l++]);
        if(r & 1) rp = Node(tree[--r], rp);
    }
    return Node(lp, rp);
}

void upd(int l, int r, LazyContext lc) {
    if(l > r) return;
    l += n, r += n+1;
    push(l);
    push(r - 1);
    int l0 = l, r0 = r;
    for(; l < r; l /= 2, r /= 2) {
        if(l & 1) apply(l++, lc);
        if(r & 1) apply(--r, lc);
    }
    build(l0);
    build(r0 - 1);
}
