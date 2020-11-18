//double operator * (const PT p) const { return p.x * q.x + p.y*q.y; }

int maximizeScalarProduct(const vector<PT> &hull, PT vec) {
  int ans = 0;
  int n = hull.size();
  if(n < 20) {
    for(int i = 0; i < n; i++) {
      if(hull[i] * vec > hull[ans] * vec) {
        ans = i;
      }
    }
  } else {
    int diff = 1;
    if(hull[0] * vec == hull[1] * vec) {
      int l = 2, r = n - 1;
      while(l != r) {
        int mid = (l + r) / 2;
        if((hull[1] - hull[0]) * (hull[mid] - hull[0]) > 0 && (hull[1] - hull[0]) % (hull[mid] - hull[0]) == 0) {
          l = mid + 1;
        } else {
          r = mid;
        }
      }
      diff = l;
      //diff = 2;
    }
    if(hull[0] * vec < hull[diff] * vec) {
      int l = diff, r = n - 1;
      while(l != r) {
        int mid = (l + r + 1) / 2;
        if(hull[mid] * vec >= hull[mid - 1] * vec && hull[mid] * vec >= hull[0] * vec) {
          l = mid;
        } else {
          r = mid - 1;
        }
      }
      if(hull[0] * vec < hull[l] * vec) {
        ans = l;
      }
    } else {
      int l = diff, r = n - 1;
      while(l != r) {
        int mid = (l + r + 1) / 2;
        if(hull[mid] * vec >= hull[mid - 1] * vec || hull[mid - 1] * vec < hull[0] * vec) {
          l = mid;
        } else {
          r = mid - 1;
        }
      }
      if(hull[0] * vec < hull[l] * vec) {
        ans = l;
      }
    }
  }
  return ans;
}
