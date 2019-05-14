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
double norm (PT p) { return hypot(p.x, p.y); }
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

bool cmp (double a, double b = 0) {
  if (abs(a-b) < eps) return 0;
  return a < b ? -1 : +1;
}

PT projectPointSegment (PT a, PT b, PT c) {
  double r = dot(b-a, b-a);
  if (cmp(r) == 0) return a;
  r = dot(b-a, c-a)/r;
  if (cmp(r, 0) == 0) return a;
  if (cmp(r, 1) == 0) return b;
  return a + (b - a) * r;
}

double distancePointSegment (PT a, PT b, PT c) {
  return dist(c, projectPointSegment(a, b, c));
}

// Parallel and opposite directions
bool ptInSegment (PT a, PT b, PT c) {
  if (a == b) return a == c;
  a = a-c, b = b-c;
  return cmp(cross(a, b)) == 0 && cmp(dot(a, b)) <= 0;
}

bool parallel (PT a, PT b, PT c, PT d) {
  return cmp(cross(b - a, c - d)) == 0;
}

bool collinear (PT a, PT b, PT c, PT d) {
  return parallel(a, b, c, d) && cmp(cross(a - b, a - c)) == 0 && cmp(cross(c - d, c - a)) == 0;
}

bool segmentsIntersect (PT a, PT b, PT c, PT d) {
  if (collinear(a, b, c, d)) {
    if (cmp(dist(a, c)) == 0 || cmp(dist(a, d)) == 0 || cmp(dist(b, c)) == 0 || cmp(dist(b, d)) == 0) return true;
    if (cmp(dot(c - a, c - b)) > 0 && cmp(dot(d - a, d - b)) > 0 && cmp(dot(c - b, d - b)) > 0) return false;
    return true;
  }
  if (cmp(cross(d - a, b - a) * cross(c - a, b - a)) > 0) return false;
  if (cmp(cross(a - c, d - c) * cross(b - c, d - c)) > 0) return false;
  return true;
}

// r = a1 + t*d1, (r - a2) x d2 = 0
PT computeLineIntersection (PT a, PT b, PT c, PT d) {
  b = b - a; d = c - d; c = c - a;
  assert(cmp(cross(b, d)) != 0);
  return a + b * cross(c, d) / cross(b, d);
}

PT computeCircleCenter (PT a, PT b, PT c) {
  b = (a + b) / 2; // bissector
  c = (a + c) / 2; // bissector
  return computeLineIntersection(b, b + rotateCW90(a - b), c, c + rotateCW90(a - c));
}

vector<PT> circleLine(PT a, PT b, PT c, double r) {
  vector<PT> ret;
  b = b - a;
  a = a - c;
  double A = dot(b, b);
  double B = dot(a, b);
  double C = dot(a, a) - r*r;
  double D = B*B - A*C;
  if (cmp(D) == -1) return ret;
  ret.push_back(c + a + b*(-B + sqrt(D + eps)) / A);
  if (cmp(D) > 0)
    ret.push_back(c + a + b*(-B - sqrt(D)) / A);
  return ret;
}

// area / semiperimeter
double rIncircle (PT a, PT b, PT c) {
  double ab = norm(a-b), bc = norm(b-c), ca = norm(c-a);
  return abs(cross(b-a, c-a)/(ab+bc+ca));
}

void sortByAngle (vector<PT>::iterator first, vector<PT>::iterator last, const PT o) {
  first = partition(first, last, [&o] (const PT &a) { return a == o; });
  auto pivot = partition(first, last, [&o] (const PT &a) {
    return !(a < o || a == o); // PT(a.y, a.x) < PT(o.y, o.x)
  });
  auto acmp = [&o] (const PT &a, const PT &b) {
    if (cmp(cross(a-o, b-o)) != 0) return cross(a-o, b-o) > 0;
    else return dist2(a, o) < dist2(b, o);
  };
  sort(first, pivot, acmp);
  sort(pivot, last, acmp);
}

vector<PT> circleCircle (PT a, double r, PT b, double R) {
  vector<PT> ret;
  double d = norm(a-b);
  if (d > r + R || d + min(r, R) < max(r, R)) return ret;
  double x = (d*d - R*R + r*r) / (2*d); // x = r*cos(R opposite angle)
  double y = sqrt(r*r - x*x);
  PT v = (b - a)/d;
  ret.push_back(a + v*x + rotateCCW90(v)*y);
  if (cmp(y) > 0)
    ret.push_back(a + v*x - rotateCCW90(v)*y);
  return ret;
}

double circularSegArea (double r, double R, double d) {
  double ang = 2 * acos((d*d - R*R + r*r) / (2*d*r)); // cos(R opposite angle) = x/r
  double tri = sin(ang) * r * r;
  double sector = ang * r * r;
  return (sector - tri) / 2;
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
