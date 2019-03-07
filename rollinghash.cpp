// 1073676287
template <typename T>
struct stringh {
  string s;
  vector<T> h, rh;
  vector<T> h_base;
  T mod;
  
  stringh () {};
  
  stringh (string &s, T mod = 1) : s(s), mod(mod) {
    h.resize(s.size()+1);
    rh.resize(s.size()+1);
    h_base.resize(s.size()+1);
    hash_init();
  }
  
  void hash_init (T prime = 0xdefaced) {
    h_base[0] = 1;
    h[0] = 0;
    
    for (int i = 1; i <= s.size(); i++){
      h[i] = (h[i-1] * prime + s[i-1]) % mod;
      h_base[i] = (h_base[i-1] * prime) % mod;
    }
    rh[0] = 0;
    for (int i = 1; i <= s.size(); i++) {
      rh[i] = (rh[i-1] * prime + s[s.size()-i]) % mod;
    }
  }
  
  T get (int l, int r) {
    return (h[r+1] - (h[l] * h_base[r-l+1]) % mod + mod) % mod;
  }
  
  T rget (int l, int r) {
    int nl = (s.size()-1-r), nr = (s.size()-l);
    return (rh[nr] - (rh[nl] * h_base[r-l+1]) % mod + mod) % mod;
  }
  
  T get (int l, int r, bool f) {
    return (f) ? rget (l, r) : get(l, r);
  }
};
