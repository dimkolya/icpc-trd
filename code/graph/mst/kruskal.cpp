struct graph {
  graph(...) {...}
  ll mst() {
    ll result = 0;
    vector<ll> p(n);
    vector<ll> rang(n, 0);
    for (ll i = 0; i < n; ++i) p[i] = i;
    for (ll i = 0; i < m; ++i) {
      ll v = g[i].second.first;
      ll u = g[i].second.second;
      ll weight = g[i].first;
      if (get(v, p) != get(u, p)) {
        result += weight;
        join(v, u, p, rang);
      }
    }
    return result;
  }
private:
  using edge_t = pair<ll, pair<ll, ll>>; //{w, {u, v}}
  ll n, m;
  vector<edge_t> g; //sorted by weight
  static ll get(ll x, vector<ll> &p) {
    if (p[x] != x) p[x] = get(p[x], p);
    return p[x];
  }
  static void join(ll x, ll y, vector<ll> &p,
                   vector<ll> &rang) {
    x = get(x, p);
    y = get(y, p);
    if (x != y) {
      if (rang[x] > rang[y]) swap(x, y);
      p[x] = y;
      if (rang[x] == rang[y]) rang[y]++;
    }
  }
};