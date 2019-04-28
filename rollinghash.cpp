ll base[1123456];
ll prime = 0xdefaced;
ll mod = 1073676287;

struct stringh {
  vector<ll> a, b;
  stringh () {};
  
  stringh (string &s) {
    a.resize(s.size()+1);
    b.resize(s.size()+1);
    a[0] = 0;
    for (int i = 0; i < s.size(); i++){
      a[i+1] = (a[i] * prime + s[i]) % mod;
    }
    b[s.size()] = 0;
    for (int i = s.size()-1; i >= 0; i--) {
      b[i] = (b[i+1] * prime + s[i]) % mod;
    }
  }
  // 0 based
  ll get (int l, int r) {
    return (a[r+1] - a[l] * base[r-l+1] % mod + mod) % mod;
  }
  
  ll rget (int l, int r) {
    return (b[l] - b[r+1] * base[r-l+1] % mod + mod) % mod;
  }
};

void init () {
  base[0] = 1;
  for (int i = 1; i < 1123456; i++) {
    base[i] = (base[i-1] * prime) % mod;
  }
}
