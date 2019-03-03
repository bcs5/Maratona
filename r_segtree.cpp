#include <bits/stdc++.h>

using namespace std;

struct lazy_t {
  int x;
  bool dirty;
  
  lazy_t (int x = 0, bool dirty = 0) : x(x), dirty(dirty) {};
  
  void operator += (const lazy_t &o) { // acumulate lazy
    
  }
};

struct node_t {
  int x;
  node_t(int x = 0) {}
  
  node_t(const node_t &lhs, const node_t &rhs) { // merge
   
  }
  
  void apply (lazy_t o) { // apply lazy
  }
};


template <class n_t, class l_t>
struct segtree_t {
  int n;
  vector<n_t> tree;
  vector<l_t> lazy;
  
  void push (int x, int l, int r) {
    if (lazy[x].dirty) {
      tree[x].apply(lazy[x]);
      if (l != r) {
        lazy[x + x] += lazy[x];
        lazy[x + x + 1] += lazy[x];
      }
      lazy[x] = l_t();
    }
  }
  
  segtree_t (int _n) : n(_n) {
    tree.resize(4*_n);
    lazy.resize(4*_n);
  }
  
  void upd (l_t lc, int a, int b, int l, int r, int x = 1) {
    push(x, l, r);
    if (a > r || b < l) return;
    if (a <= l && b >= r) {
      lazy[x] += lc;
      push(x, l, r);
      return;
    }
    int m = (l+r)/2;
    upd(lc, a, b, l, m, x + x);
    upd(lc, a, b, m, r, x + x + 1);
    tree[x] = n_t(tree[x + x], tree[x + x + 1]);
  }
  
  n_t qry (int a, int b, int l, int r, int x = 1) {
    if (a > r || b < l) return n_t();
    if (a <= l && b >= r) {
      return tree[x];
    }
    push(x, l, r);
    int m = (l+r)/2;
    return n_t(qry(a, b, l, m, x + x), qry(a, b, m, r, x + x + 1));
  }
};
