struct Node {
    Node() {
        // empty constructor
    }

    Node(int v) {
        // init
    }

    Node(Node l, Node r) {
        // merge
    }

    // var
};

int n;
int a[ms];
Node seg[2*ms];

void build() {
    for(int i = 0; i < n; ++i) seg[i + n] = Node(a[i]);
    for(int i = n - 1; i > 0; --i) seg[i] = Node(seg[i<<1], seg[i<<1|1]); // Merge
}

void upd(int p, int value) { // set value at position p
    for(seg[p += n] = value; p > 1; p >>= 1) seg[p>>1] = Node(seg[p], seg[p^1]); // Merge
}

Node qry(int l, int r) {
    Node lp, rp;
    for(l += n, r += n+1; l < r; l >>= 1, r >>= 1) {
        if(l&1) lp = Node(lp, seg[l++]); // Merge
        if(r&1) rp = Node(seg[--r], rp); // Merge
    }
    return Node(lp, rp);
}
