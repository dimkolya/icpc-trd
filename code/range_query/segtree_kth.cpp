struct segment_tree {
  segment_tree(const vector<ll> &a) {
    x = a;
    std::sort(x.begin(), x.end());
    x.erase(unique(x.begin(), x.end()), x.end());
    n = x.size();
    roots.push_back(init(0, n));
    for (ll i : a)
      roots.push_back(add(
          lower_bound(x.begin(), x.end(), i)
          - x.begin(), roots.back(), 0, n));
  }
  ll get(ll l, ll r, ll k) const { //[l, r] k=[1..n]
    node *left_pre = roots[l];
    node *right_pre = roots[r];
    ll i = get(left_pre, right_pre, k, 0, n);
    return x[i];
  }
private:
  struct node {
    ll v;
    node *l;
    node *r;
  };
  ll n;
  vector<node *> roots;
  vector<ll> x;
  ll get(node *l, node *r, ll k, ll tl, ll tr) const {
    if (tl + 1 == tr) return tl;
    ll tm = (tl + tr) / 2;
    if (r->l->v - l->l->v >= k)
      return get(l->l, r->l, k, tl, tm);
    else
      return get(l->r,r->r,k-r->l->v+l->l->v,tm,tr);
  }
  node *add(ll i, node *cur, ll tl, ll tr) {
    if (tl + 1 == tr)
      return new node{cur->v + 1, 0, 0};
    ll tm = (tl + tr) / 2;
    node *result = new node();
    if (index < tm) {
      result->l = add(i, cur->l, tl, tm);
      result->r = cur->r;
    } else {
      result->l = cur->l;
      result->r = add(i, cur->r, tm, tr);
    }
    result->v = result->l->v + result->r->v;
    return result;
  }
  node *init(ll tl, ll tr) {
    if (tl + 1 == tr) return new node{0, 0, 0};
    ll tm = (tl + tr) / 2;
    node *result = new node{0, 0, 0};
    result->l = init(tl, tm);
    result->r = init(tm, tr);
    return result;
  }
};