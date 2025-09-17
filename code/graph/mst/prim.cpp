struct graph {
  graph() {...}
  ld mst() const {
    vector<ld> key(n, INF);
    vector<ll> p(n, n);
    key[0] = 0;
    vector<bool> used(n, false);
    ld result = 0;
    for (ll i = 0; i < n; ++i) {
      ll v = n;
      for (ll u = 0; u < n; ++u)
        if (!used[u]
            && (v == n || key[v] > key[u]))
          v = u;
      used[v] = true;
      if (p[v] != n) {
        result += weight(v, p[v]);
      }
      for (ll u = 0; u < n; ++u) {
        ld temp = weight(v, u);
        if (!used[u] && key[u] > temp) {
          p[u] = v;
          key[u] = temp;
        }
      }
    }
    return result;
  }
private:
  ll n; vector<ll> x, y;
};