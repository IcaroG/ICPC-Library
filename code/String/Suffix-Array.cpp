typedef pair<int, int> ii;
  
vector<int> buildSA(string s) {
    int n = (int) s.size();
    vector<int> ids(n), pos(n);
    vector<ii> pairs(n);
    for(int i = 0; i < n; i++) {
        ids[i] = i;
        pairs[i] = ii(s[i], -1);
    }
    sort(ids.begin(), ids.end(), [&](int a, int b) -> bool {
        return pairs[a] < pairs[b];
    });
    int on = 0;
    for(int i = 0; i < n; i++) {
        if (i && pairs[ids[i - 1]] != pairs[ids[i]]) on++;
        pos[ids[i]] = on;
    }
    for(int offset = 1; offset < n; offset <<= 1) {
        for(int i = 0; i < n; i++) {
            pairs[i].first = pos[i];
            if (i + offset < n) {
                pairs[i].second = pos[i + offset];
            } else {
                pairs[i].second = -1;
            }
        }
        sort(ids.begin(), ids.end(), [&](int a, int b) -> bool {
            return pairs[a] < pairs[b];
        });
        int on = 0;
        for(int i = 0; i < n; i++) {
            if (i && pairs[ids[i - 1]] != pairs[ids[i]]) on++;
            pos[ids[i]] = on;
        }
    }
    return ids;
}

vector<int> buildLCP(string s, vector<int> sa) {
    int n = (int) s.size();
    vector<int> pos(n), lcp(n, 0);
    for(int i = 0; i < n; i++) {
        pos[sa[i]] = i;
    }
    int k = 0;
    for(int i = 0; i < n; i++) {
        if (pos[i] + 1 == n) {
            k = 0;
            continue;
        }	
        int j = sa[pos[i] + 1];
        while(i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
        lcp[pos[i]] = k;
        k = max(k - 1, 0);
    }
    return lcp;
}

int distinctSubstrings(string s) {
    vector<int> sa = buildSA(s);
    vector<int> pref = buildLCP(s, sa);
    int n = s.size();
    int ans = n - sa[0];
    for (int i = 1; i < s.size(); i++) {
        ans += (n - sa[i]) - pref[i - 1];
    }
    return ans;
}

void kthLexicographicalSubstring() {
    string s;
    cin >> s;
    int n = s.size();
    vector<int> sa = buildSA(s);
    vector<int> pref = buildLCP(s, sa);
    vector<int> prefAcum(n);	
    prefAcum[0] = n - sa[0];
    for (int i = 1; i < n; i++) {
        prefAcum[i] = prefAcum[i - 1] + ((n - sa[i]) - pref[i - 1]);
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int k;
        cin >> k;
        int pos = lower_bound(prefAcum.begin(), prefAcum.end(), k) - prefAcum.begin();
        string ans;
        ans = s.substr(sa[pos], pref[pos - 1] + (k - prefAcum[pos - 1]));
        cout << ans << '\n';
    }
}
