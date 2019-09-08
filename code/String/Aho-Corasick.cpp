#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 7;
const int sigma = 55;

int fail[MAXN];
vector<int> terminal[MAXN];
vector<int> all;
queue<int> q;
int trie[MAXN][sigma], z;
bool res[1010];

void init() {
  memset(trie[0], -1, sizeof trie[0]);
  z = 1;
}

int get_id(char c) {
	if (c >= 'a' && c <= 'z') return c - 'a';
	return 26 + (c - 'A');
}

void insert(string &p, int idx) {
  int cur = 0;
  for(int i = 0; i < p.size(); i++) {
    int id = get_id(p[i]);
    if(trie[cur][id] == -1) {
      memset(trie[z], -1, sizeof trie[z]);
      trie[cur][id] = z++;
    }
    cur = trie[cur][id];
  }
  all.push_back(cur);
  terminal[cur].push_back(idx);
}

vector<int> merge(vector<int> &a, vector<int> &b) {
	vector<int> ans(int(a.size()) + int(b.size()));
	merge(a.begin(), a.end(), b.begin(), b.end(), ans.begin());
	ans.resize(unique(ans.begin(), ans.end()) - ans.begin());
	return ans;
}

void buildFailure() {
  q.push(0);
  while(!q.empty()) {
    int node = q.front();
    q.pop();
    for(int pos = 0; pos < sigma; pos++) {
      int &v = trie[node][pos];
      int f = node == 0 ? 0 : trie[fail[node]][pos];
      if(v == -1) {
        v = f;
      } else {
        fail[v] = f;
        q.push(v);
        //terminal[v] += terminal[f];
        terminal[v] = merge(terminal[v], terminal[f]);
      }
    }
  }
}

void search(string &txt) {
	int node = 0;
	vector<int> ans;
	for(int i = 0; i < txt.length(); i++) {
		int pos = get_id(txt[i]);
		node = trie[node][pos];
		ans = merge(ans, terminal[node]);
		//cout << "Na posicao " << i << '\n';
		//for (auto v : terminal[node]) cout << v << ' ';
		//cout << '\n';
	}
	for (auto v : ans) {
		res[v] = true;
	}
}

int main() {
	int t;
	cin >> t;
	while (t--) {
		init();
		string s;
		cin >> s;
		int n;
		cin >> n;
		for (int i = 0; i < n; i++) {
			string str;
			cin >> str;
			insert(str, i);
		}
		buildFailure();
		memset(res, false, sizeof res);
		search(s);
		for (auto v : all) {
			terminal[v].clear();
		}
		all.clear();
		for (int i = 0; i < n; i++) {
			if (res[i]) cout << "y\n";
			else cout << "n\n";
		}
	}
	return 0;
}
