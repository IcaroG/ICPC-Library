struct point {
  double x, y;
};

point pt[MAXN];
int n;

double dist(point a, point b) {
  return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
} 

int solve() {
  vector<pair<double, int>> events;
  int ans = 1;
  for (int i = 0; i < n; i++) {
    events.clear();
    for (int j = 0; j < n; j++) {
      if (i == j || dist(pt[i], pt[j]) > 2.0 * R) continue;
      double A = atan2(pt[j].y - pt[i].y, pt[j].x - pt[i].x);
      if (A < 0) A += 2*PI;
      double B = acos(dist(pt[i], pt[j]) / (2.0 * R));
      if (A - B >= 0) {
        events.push_back({A - B, -1});
      } else {
        events.push_back({0.0, -1});
        events.push_back({+2*PI + (A - B), +1});
      }
      if (A + B <= 2*PI) {
        events.push_back({A + B, +1});
      } else {
        events.push_back({0.0, -1});
        events.push_back({-2*PI + (A + B), +1});
      }
    }
    sort(events.begin(), events.end());
    int cnt = 1;
    for (int i = 0; i < events.size(); i++) {
      if (events[i].second < 0) {
        cnt++;
      } else {
        cnt--;
      }
      ans = max(ans, cnt);
    }
  }
  return ans;
}
