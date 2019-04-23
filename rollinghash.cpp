
// 1073676287
template <typename T>
struct stringh {
  string s;
  vector<T> h;
  vector<T> h_base;
  T mod;

  stringh (string s, T mod) : s(s), mod(mod) {
    h.resize(s.size()+1);
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
  }

  T get (int l, int r) {
    return (h[r+1] - (h[l] * h_base[r-l+1]) % mod + mod) % mod;
  }
};
