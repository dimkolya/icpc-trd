struct dsu {
  vector<ll> p;
  vector<ll> s;
  dsu(ll n) {
    s.resize(n, 1); // note: fill 1
    p.resize(n);
    std::iota(p.begin(), p.end(), 0);
  }
  ll find(ll v) {
    if (v == p[v]) return v;
    return p[v] = find(p[v]);
  }
  bool same(ll u, ll v) {
    return find(u) == find(v);
  }
  void join(ll u, ll v) {
    u = find(u), v = find(v);
    if (u == v) return;
    if (s[u] < s[v]) swap(u, v);
    p[v] = u, s[u] += s[v];
  }
};