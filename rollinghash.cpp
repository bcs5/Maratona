// building
// 1073676287
T prime = 0xdefaced
T mod1,  mod2;
struct hash_k {
  T h1, h2;
  hash_k operator + (hash_t rh) {
    return hash_k((rh.h1 + h1) % mod1, (rh.h2 + h2) % mod2);
  }
  hash_k operator - (hash_t rh) {
    return hash_k((-rh.h1 + h1 + mod1) % mod1, (-rh.h2 + h2 + mod2) % mod2);
  }
   hash_k operator * (hash_t rh) {
    T a = (((rh.h1 * h1) % mod1)+mod1)%mod1;
    T b = (((rh.h2 * h2) % mod2)+mod2)%mod2;
    return hash_k(a, b);
  }
}  
vector<hash_k> primepot;

struct hash_t {
  hash_k key;
  int sz;
  hash_t (char c) { hash1 = t}
  hash_t operator + (hash_t lh, hash_t rh) {
    c.key * primepot[rh.sz] + rh;
    c.sz = lh.sz + rh.sz;
    return c;
  }
  hash_t operator - (hash_t lh, hash_t rh) {
    c.sz = lh.sz - rh.sz + 1;
    c.key = lh - 1*rh*primepot[c.sz];
    return c;
  }
}

struct stringh {
  vector<hash_t> hl, hr;
  stringh (string s = "") {
    hl.resize(s.size()+2);
    hr.resize(s.size()+2);
    for (int i = 1; i <= s.size(); i++) {
      hl[i] = hl[i-1] + hash_t(s[i-1]);
    }
    for (int i = s.size(); i > 0; i--) {
      hr[i] = hr[i+1] + hash_t(s[i-1]);
    }
  }
  
  hash_t lget (int l, int r) {
    return hl[r+1] - hl[l];
  }
  
  hash_t rget (int l, int r) {
    return hr[l+1] - hr[r];
  }
};
