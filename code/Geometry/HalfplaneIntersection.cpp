struct L {
    PT a, b;
    L(){}
    L(PT a, PT b) : a(a), b(b) {}
};

double angle(const L la) { return atan2(-(la.a.y - la.b.y), la.b.x - la.a.x); }


bool comp(L la, L lb){       
    if (cmp(angle(la), angle(lb)) == 0) return cross((lb.b - lb.a), (la.b - lb.a)) > eps;
    return cmp(angle(la), angle(lb)) < 0;
}

PT computeLineIntersection(L a, L b){
    return computeLineIntersection(a.a, a.b, b.a, b.b);
}

bool check(L l1, L l2, L l3) {
    PT p = computeLineIntersection(l2, l3);
    double det = cross((l1.b - l1.a),  (p - l1.a));
    return cmp(det) < 0;
}

vector<PT> hpi(vector<L> line) { // salvar (i, j) CCW, (j, i) CW
    sort(line.begin(), line.end(), comp);
    vector<L> pl(1, line[0]);
    for (int i = 0; i < (int)line.size(); ++i) if (cmp(angle(line[i]), angle(pl.back())) != 0) pl.push_back(line[i]);
    deque<int> dq;
    dq.push_back(0);
    dq.push_back(1);
    for (int i = 2; i < (int)pl.size(); ++i) {
        while ((int)dq.size() > 1 && check(pl[i], pl[dq.back()], pl[dq[dq.size() - 2]])) dq.pop_back();
        while ((int)dq.size() > 1 && check(pl[i], pl[dq[0]], pl[dq[1]])) dq.pop_front();
        dq.push_back(i);
    }
    while ((int)dq.size() > 1 && check(pl[dq[0]], pl[dq.back()], pl[dq[dq.size() - 2]])) dq.pop_back();
    while ((int)dq.size() > 1 && check(pl[dq.back()], pl[dq[0]], pl[dq[1]])) dq.pop_front();
    vector<PT> res;
    for (int i = 0; i < (int)dq.size(); ++i){
        res.emplace_back(computeLineIntersection(pl[dq[i]], pl[dq[(i + 1) % dq.size()]]));
    }
    return res;
}
 
