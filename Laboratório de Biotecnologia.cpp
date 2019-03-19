#include <bits/stdc++.h>
using namespace std;

#define all(foo) foo.begin(), foo.end()

#define sc(a) scanf("%d", &a)
#define sc2(a,b) scanf("%d%d", &a, &b)
#define sc3(a,b,c) scanf("%d%d%d", &a, &b, &c)
#define pri(x) printf("%d\n", x)

#define db(x) cerr << #x << " == " << x << endl
#define dbs(x) cerr << x << endl
#define x first
#define y second


typedef long long ll;
typedef pair<int, int> ii;

const int inf = 0x3f3f3f3f;

// FFT courtesy of http://e-maxx.ru/algo/fft_multiply
const double PI = acos(0) * 2;

typedef struct complex_t {
  double a {0.0}, b {0.0};
  complex_t() {}
  complex_t(double a) : a(a), b(0) {};
  complex_t(double na, double nb) : a{na}, b{nb} {}
  const complex_t operator+(const complex_t &c) const {
    return complex_t(a + c.a, b + c.b);
  }
  const complex_t operator-(const complex_t &c) const {
    return complex_t(a - c.a, b - c.b);
  }
  const complex_t operator*(const complex_t &c) const {
    return complex_t(a*c.a - b*c.b, a*c.b + b*c.a);
  }
} cd;

const int MAX_SUM = 1 << 22;
using base = complex_t;

int rev[MAX_SUM << 1];
base wlen_pw[MAX_SUM << 1];

void fft(base a[], int n, bool invert) {
  for (int i = 0; i < n; ++i)
    if (i < rev[i])
      swap(a[i], a[rev[i]]);

  for (int len = 2; len <= n; len <<= 1) {
    double ang = 2 * PI / len * (invert ? -1 : +1);
    int len2 = len>>1;

    base wlen(cos(ang), sin(ang));
    wlen_pw[0] = base(1, 0);
    for (int i = 1; i < len2; ++i)
      wlen_pw[i] = wlen_pw[i-1] * wlen;

    for (int i = 0; i < n; i += len) {
      base t,
        *pu = a+i,
        *pv = a+i+len2,
        *pu_end = a+i+len2,
        *pw = wlen_pw;
      while (pu != pu_end) {
        t = *pv * *pw;
        *pv = *pu - t;
        *pu = *pu + t;

        ++pu, ++pv, ++pw;
      }
    }
  }

  if (invert)
    for (int i = 0; i < n; ++i) {
      a[i].a /= n;
      a[i].b /= n;
    }
}

void calc_rev(int n, int log_n) {
  for (int i = 0; i < n; ++i) {
    rev[i] = 0;
    for (int j = 0; j < log_n; ++j)
      if (i & (1<<j))
        rev[i] |= 1 << (log_n-1-j);
  }
}

int C[MAX_SUM<<1];

int main () {
  string s;
  cin >> s;
  vector<int> sums(s.size());
  
  int sum = 0;
  for (int i = 0; i < s.size(); i++) {
    sum += s[i]-'a'+1;
    sums[i] = sum;
  }
  int n = 1; int log_n = 0;
  while (n <= sum) { n <<= 1; log_n++; }
  n <<= 1; log_n++;
  calc_rev(n, log_n);

  cd P[n];
  cd Q[n];
  for (int i = 0; i < s.size(); i++) {
    P[sum+sums[i]] = cd(1);
    Q[sum-sums[i]] = cd(1);
  }
  P[sum] = cd(1);
  
  
  fft(P, n, false), fft(Q, n, false);
  
  for (int i = 0; i < n; ++i)
    P[i] = P[i] * Q[i];
  
  fft(P, n, true);
  for (int i = 0; i < n; ++i)
    C[i] = int(P[i].a + 0.5);
  
  int ans = 0;
  for (int i = sum+1; i <= 2*sum; i++) {
    ans += !!C[i];
  }
  cout << ans << endl;
}
