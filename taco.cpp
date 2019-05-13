#include <bits/stdc++.h>
using namespace std;

const double inf = 1e100, eps = 1e-9;
const double PI = acos(-1.0L);

struct PT {
  double x, y;
  PT(double x = 0, double y = 0) : x(x), y(y) {}
  PT operator + (const PT &p) const { return PT(x+p.x, y+p.y); }
  PT operator - (const PT &p) const { return PT(x-p.x, y-p.y); }
  PT operator * (double c) const { return PT(x*c, y*c); }
  PT operator / (double c) const { return PT(x/c, y/c); }
  
  bool operator <(const PT &p) const {
    if(fabs(x - p.x) >= eps) return x < p.x;
    return fabs(y - p.y) >= eps && y < p.y;
  }
  bool operator ==(const PT &p) const {
    return !(*this < p || p < *this);
  }
};

double dot (PT p, PT q) { return p.x * q.x + p.y*q.y; }
double cross (PT p, PT q) { return p.x * q.y - p.y*q.x; }
double dist2 (PT p, PT q) { return dot(p-q, p-q); }
double dist (PT p, PT q) { return hypot(p.x-q.x, p.y-q.y); }
double angle (PT p, PT q) { return atan2(cross(p, q), dot(p, q)); }

// - p.y*sen(+90), p.x*sen(+90)
PT rotateCCW90 (PT p) { return PT(-p.y, p.x); }
// - p.y*sen(-90), p.x*sen(-90)
PT rotateCW90 (PT p) { return PT(p.y, -p.x); }

PT rotateCCW (PT p, double t) {
  return PT(p.x*cos(t)-p.y*sin(t), p.x*sin(t)+p.y*cos(t));
}

// a.b = |a| cost * |b|
PT projectPointLine (PT a, PT b, PT c) {
  return a + (b-a) * dot(b-a, c-a)/dot(b-a, b-a);
}

PT reflectPointLine (PT a, PT b, PT c) {
  auto p = projectPointLine(a, b, c);
  return p*2 - c;
}

PT projectPointSegment (PT a, PT b, PT c) {
  double r = dot(b-a, b-a);
  if (abs(r) < eps) return a;
  r = dot(b-a, c-a)/r;
  if (r < 0) return a;
  if (r > 1) return b;
  return a + (b - a) * r;
}

double distancePointSegment (PT a, PT b, PT c) {
  return dist(c, projectPointSegment(a, b, c));
}

// Parallel and opposite directions
bool ptInSegment (PT a, PT b, PT c) {
  if (a == b) return a == c;
  a = a-c, b = b-c;
  return cross(a, b) == 0 && dot(a, b) <= 0;
}

bool parallel (PT a, PT b, PT c, PT d) {
  return abs(cross(b - a, c - d)) < eps;
}

bool collinear (PT a, PT b, PT c, PT d) {
  return parallel(a, b, c, d) && abs(cross(a - b, a - c)) < eps && abs(cross(c - d, c - a)) < eps;
}

bool segmentsIntersect (PT a, PT b, PT c, PT d) {
  if (collinear(a, b, c, d)) {
    if (dist2(a, c) < eps || dist2(a, d) < eps || dist2(b, c) < eps || dist2(b, d) < eps) return true;
    if (dot(c - a, c - b) > 0 && dot(d - a, d - b) > 0 && dot(c - b, d - b) > 0) return false;
    return true;
  }
  if (cross(d - a, b - a) * cross(c - a, b - a) > 0) return false;
  if (cross(a - c, d - c) * cross(b - c, d - c) > 0) return false;
  return true;
}

// r = a1 + t*d1, (r - a2) x d2 = 0
PT computeLineIntersection (PT a, PT b, PT c, PT d) {
  b = b - a; d = d - c; c = c - a;
  assert(cross(b, d) != 0);
  return a + b * cross(c, d) / cross(b, d);
}

PT computeCircleCenter (PT a, PT b, PT c) {
  b = (a + b) / 2; // bissector
  c = (a + c) / 2; // bissector
  return computeLineIntersection(b, b + rotateCW90(a - b), c, c + rotateCW90(a - c));
}

void sortByAngle(vector<PT>::iterator first, vector<PT>::iterator last, const PT o) {
  first = partition(first, last, [&o] (const PT &a) { return a == o; });
  auto pivot = partition(first, last, [&o] (const PT &a) {
    return !(a < o || a == o); // PT(a.y, a.x) < PT(o.y, o.x)
  });
  auto acmp = [&o] (const PT &a, const PT &b) {
    if (abs(cross(a-o, b-o)) > eps) return cross(a-o, b-o) > 0;
    else return dist2(a, o) < dist2(b, o);
  };
  sort(first, pivot, acmp);
  sort(pivot, last, acmp);
}

int main () {
  ios::sync_with_stdio(0);
  cin.tie(0);
  vector<PT> v {PT{5, 5}, PT{1, 1}, PT{-1, -1}, {1, -1}, {-5, -5}};
  sortByAngle(v.begin(), v.end(), PT());
  for (int i = 0; i < v.size(); i++) {
    cout << v[i].x << " " << v[i].y << endl;
  }
}





