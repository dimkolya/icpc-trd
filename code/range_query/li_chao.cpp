// Line is k * x + b.
// f(x) = min_i (k_i * x + b_i).
// get(0, 0, n, x) - min value at x.
// upd(0, 0, n, ln) - add new line.
struct li_chao {
  struct line {
    ll k, b;
    line(ll k, ll b) : k(k), b(b) {}
    ll get(ll x) { return k * x + b; }
  };
  vector<line> t;
  ll n;
  const line NONE = {0, INF};
  li_chao(ll n) : n(n) { t.resize(4 * n, NONE); }
  void upd(ll p, ll l, ll r, line ln){
    if (ln.k == t[p].k) {
      if (ln.b < t[p].b) t[p] = line;
      return;
    }
    if (r - l == 1) {
      if (ln.get(l) < t[p].get(l)) t[p] = ln;
      return;
    }
    ll m = (l + r) / 2;
    if (ln.get(m) < t[p].get(m)) swap(ln, t[p]);
    if (ln.k > t[p].k) upd(2 * p + 1, l, m, ln);
    else upd(2 * p + 2, m, r, ln);
  }
  ll get(ll p, ll l, ll r, ll q){
    if (r-l==1) return t[p].get(q);
    ll m = (l + r) / 2;
    if (q < m)
      return min(t[p].get(q), get(2 * p + 1, l, m, q));
    else
      return min(t[p].get(q), get(2 * p + 2, m, r, q));
  }
  void upd(ll k, ll b){
    return upd(0, 0, n, line(k, b));
  }
  ll get(ll q){
    return get(0, 0, n, q);
  }
};