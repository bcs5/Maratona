typedef pair<PT, double> circle;
bool inCircle(circle c, PT p){
  return cmp(dist(c.first, p), c.second) <= 0;
}

PT circumcenter(PT p, PT q, PT r){
  PT a = p-r, b = q-r;
  PT c = PT(dot(a, p+r)/2, dot(b, q+r)/2);
  return PT(cross(c, PT(a.y,b.y)), cross(PT(a.x,b.x), c)) / cross(a, b);
}

circle spanningCircle (vector<PT> &v) {
  int n = v.size();
  random_shuffle(v.begin(), v.end());
  circle C(PT(), -1);
  for (int i = 0; i < n; i++) if (!inCircle(C, v[i])) {
    C = circle(v[i], 0);
    for (int j = 0; j < i; j++) if (!inCircle(C, v[j])) {
      C = circle((v[i]+v[j])/2, dist(v[i], v[j])/2);
      for(int k = 0; k < j; k++) if (!inCircle(C, v[k])){
        PT o = circumcenter(v[i], v[j], v[k]);
        C = circle(o,dist(o,v[k]));
      }
    }
  }
  return C;
}

vector<PT> convexHull(vector<PT> p) {
  int n = p.size(), k = 0;
  vector<PT> h(2 * n);
  sort(p.begin(), p.end());
  for(int i = 0; i < n; i++) {
    while(k >= 2 && cmp(cross(h[k - 1] - h[k - 2], p[i] - h[k - 2])) <= 0) k--;
    h[k++] = p[i];
  }
  for(int i = n - 2, t = k + 1; i >= 0; i--) {
    while(k >= t && cmp(cross(h[k - 1] - h[k - 2], p[i] - h[k - 2])) <= 0) k--;
    h[k++] = p[i];
  }
  h.resize(k); // n+1 points where the first is equal to the last
  return h;
}

vector<PT> graham (vector<PT> v) {
  sort(v.begin(), v.end());
  sortByAngle(v.begin(), v.end(), v[0]);
  vector<PT> u (v.size());
  int top = 0;
  for (int i = 0; i < v.size(); i++) {
    while (top > 1 && cmp(cross(u[top-1] - u[top-2], v[i]-u[top-2])) <= 0) top--;
    u[top++] = v[i];
  }
  u.resize(top);
  return u;
}
