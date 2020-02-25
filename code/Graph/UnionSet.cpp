int ds[ms], sz[ms];

void init(){
    for(int i = 0; i < n; ++i){
        ds[i] = i;
        sz[i] = 1;
    }
}

int find(int i){
    if(ds[i] != i) return ds[i] = find(ds[i]);
    return ds[i];
}

void join(int a, int b){
    a = find(a);
    b = find(b);
    if(sz[a] < sz[b]) swap(a, b);
    if(a != b) sz[a] += sz[b];
    ds[b] = a;
}
