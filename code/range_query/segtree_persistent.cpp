struct st {
  struct node {
    ll v;
    node *l;
    node *r;
  };
  ll n;
  vector<node *> roots;
  st(const vector<ll> &a) { // version 0
    n = a.size();
    roots.push_back(init(0, n, a));
  }
  node *init(ll tl, ll tr, const vector<ll> &a) {
    if (tl + 1 == tr) return new node{a[tl], 0, 0};
    ll tm = (tl + tr) / 2;
    node *result = new node{0, 0, 0};
    result->l = init(tl, tm, a);
    result->r = init(tm, tr, a);
    result->v = result->l->v + result->r->v;
    return result;
  }
  void add(ll i, ll v) {
    roots.push_back(add(i, v, roots.back(), 0, n));
  }
  node *add(ll i, ll v, node *cur, ll tl, ll tr) {
    if (tl + 1 == tr)
      return new node{cur->v + v, 0, 0};
    ll tm = (tl + tr) / 2;
    node *result = new node();
    if (i < tm) {
      result->l = add(i, v, cur->l, tl, tm);
      result->r = cur->r;
    } else {
      result->l = cur->l;
      result->r = add(i, v, cur->r, tm, tr);
    }
    result->v = result->l->v + result->r->v;
    return result;
  }
  // get(...) const
};