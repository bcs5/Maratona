template <class T>
class BIT {
public:
  void init (int n) {
    this->n = n;
    bit.assign(n + 1, 0);
  }

  void init (const std::vector<T> &a) {
    n = a.size();
    bit.assign(n + 1, 0);
    for(int i = 1; i <= n; i++) {
      bit[i] += a[i - 1];
      if(i + (i & -i) <= n) {
       bit[i + (i & -i)] += bit[i];
      }
    }
  }

  T qry (int x) {
    x = std::min(x, (int)bit.size() - 1);
    T ans = 0;
    for(; x > 0; x -= x & -x) {
      ans += bit[x];
    }
    return ans;
  }

  void upd (int x, T v) {
    if(x <= 0) return;
    for(; x <= n; x += x & -x) {
      bit[x] += v;
    }
  }

  int kth (int k) {
    int id = 0, bitmask = 1;
    while ((bitmask<<1) <= n) bitmask <<= 1;
    for (; bitmask; bitmask >>= 1) {
      if (id+bitmask <= n && bit[id+bitmask] < k) {
        id += bitmask;
        k -= bit[id];
      }
    }
    return id + (!!k);
  }
  
private:
  int n;
  std::vector<T> bit;
};
