#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;

const double inf = 1e100, eps = 1e-9;
const double PI = acos(-1.0L);

int cmp (double a, double b = 0) {
  if (abs(a-b) < eps) return 0;
  return (a < b) ? -1 : +1;
}

struct PT {
  long long x, y;
  bool c;
  PT(long long x = 0, long long y = 0) : x(x), y(y) {}
  PT operator + (const PT &p) const { return PT(x+p.x, y+p.y); }
  PT operator - (const PT &p) const { return PT(x-p.x, y-p.y); }
  PT operator * (long long c) const { return PT(x*c, y*c); }
  
  bool operator <(const PT &p) const {
    if(cmp(x, p.x) != 0) return x < p.x;
    return cmp(y, p.y) < 0;
  }
  bool operator ==(const PT &p) const {
    return (cmp(x, p.x) || cmp(y, p.y)) == 0;
  }
};

double dot (PT p, PT q) { return p.x * q.x + p.y*q.y; }
long long cross (PT p, PT q) { return p.x * q.y - p.y*q.x; }
double dist2 (PT p, PT q = PT(0, 0)) { return dot(p-q, p-q); }
double dist (PT p, PT q) { return hypot(p.x-q.x, p.y-q.y); }
double norm (PT p) { return hypot(p.x, p.y); }
double angle (PT p, PT q) { return atan2(cross(p, q), dot(p, q)); }
double angle (PT p) { return atan2(p.y, p.x); }
double polarAngle (PT p) {
  double a = atan2(p.y,p.x);
  return a < 0 ? a + 2*PI : a;
}

void sortByAngle (vector<PT>::iterator first, vector<PT>::iterator last, const PT o) {
  first = partition(first, last, [&o] (const PT &a) { return a == o; });
  auto pivot = partition(first, last, [&o] (const PT &a) {
    return !(a < o || a == o); // PT(a.y, a.x) < PT(o.y, o.x)
  });
  auto acmp = [&o] (const PT &a, const PT &b) { // C++11 only
    if (cmp(cross(a-o, b-o)) != 0) return cross(a-o, b-o) > 0;
    else return cmp(norm(a-o), norm(b-o)) < 0;
  };
  sort(first, pivot, acmp);
  sort(pivot, last, acmp);
}

vector<PT> graham (vector<PT> v) {
  sort(v.begin(), v.end());
  sortByAngle(v.begin(), v.end(), v[0]);
  vector<PT> u (v.size());
  int top = 0;
  for (int i = 0; i < v.size(); i++) {
    while (top > 1 && cmp(cross(u[top-1] - u[top-2], v[i]-u[top-2])) <= 0) {
      top--;
    }
    u[top++] = v[i];
  }
  u.resize(top);
  return u;
}


#define L(x, n) (x-1+n) % n
#define R(x, n) (x+1) % n

int main () {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<PT> v(n);
  for (int i = 0; i < n; i++) {
    cin >> v[i].x >> v[i].y;
  }
  auto ch1 = graham(vector<PT> (v.begin(), v.begin()+m));
  auto ch2 = graham(vector<PT> (v.begin(), v.end()));
  int sz1 = ch1.size();
  int sz2 = ch2.size();
  long long ans = 0, area1 = 0, area = 0;
  for (int i = 0; i < sz1; i++) {
    area += cross(ch1[i], ch1[R(i, sz1)]);
  }
  ans = area;
  int l = 0, r = 0;
  while (cross(ch1[l]-ch2[0], ch1[L(l, sz1)] - ch2[0]) >= 0) {
    area1 -= cross(ch1[l]-ch1[r], ch1[L(l, sz1)] - ch1[l]);
    l = L(l, sz1);
  }
  
  for (int i = 0; i < sz2; i++) {
    while (cross(ch1[r]-ch2[i], ch1[R(r, sz1)] - ch2[i]) <= 0) {
      area1 += cross(ch1[r]-ch1[l], ch1[R(r, sz1)] - ch1[l]);
      r = R(r, sz1);
    }
    while (cross(ch1[R(l, sz1)]-ch2[i], ch1[l] - ch2[i]) < 0) {
      area1 += cross(ch1[R(l, sz1)]-ch1[r], ch1[l] - ch1[r]);
      l = R(l, sz1);
    }
    ans = max(ans, area + (long long)cross(ch1[r]-ch2[i], ch1[l]-ch2[i]) - area1);
  }
  cout << ans/2 << "." << (ans%2)*5 << endl;
}
