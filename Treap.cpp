
mt19937 rng ((int) chrono::steady_clock::now().time_since_epoch().count());

typedef int Key;
typedef struct item * pitem;

struct item {
  item() { }
  item (Key k) {
    key = k;
    prio = uniform_int_distribution<int>() (rng);
    cnt = 1;
    rev = 0;
    l = r = NULL;
  }
  Key key;
  int prio;
  pitem l, r;
};

void split (pitem t, int key, pitem & l, pitem & r) {
  if (!t) return void(l = r = NULL);
  if (key < t->key)
    split (t->l, key, l, t->l),  r = t;
  else
    split (t->r, key, t->r, r),  l = t;
}

void insert (pitem & t, pitem it) {
  if (!t)
    t = it;
  else if (it->prior > t->prior)
    split (t, it->key, it->l, it->r),  t = it;
  else
    insert (it->key < t->key ? t->l : t->r, it);
}

void merge (pitem & t, pitem l, pitem r) {
  if (!l || !r)
    t = l ? l : r;
  else if (l->prior > r->prior)
    merge (l->r, l->r, r),  t = l;
  else
    merge (r->l, l, r->l),  t = r;
}

void erase (pitem & t, int key) {
  if (t->key == key)
    merge (t, t->l, t->r);
  else
    erase (key < t->key ? t->l : t->r, key);
}

pitem unite (pitem l, pitem r) {
  if (!l || !r)  return l ? l : r;
  if (l->prior < r->prior)  swap (l, r);
  pitem lt, rt;
  split (r, l->key, lt, rt);
  l->l = unite (l->l, lt);
  l->r = unite (l->r, rt);
  return l;
}
