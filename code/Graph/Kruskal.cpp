vector<pair<int, ii>> edge;
vector<ii> g[ms];

void kruskal(){
	sort(edge.begin(), edge.end());

	for(int i = m - 1; i >= 0; --i){
		int w = edge[i].first, u = edge[i].second.first, v = edge[i].second.second;
		if(dsFind(u) != dsFind(v)){
			dsUnion(u, v);
			g[u].push_back({v, w});
			g[v].push_back({u, w});
		}
	}
}
