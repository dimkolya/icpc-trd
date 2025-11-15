struct graph {
  graph(...) {...}
  vector<ll> get_apoints() {
    vector<ll> res;
    vector<ll> tin(n);
    vector<ll> tup(n);
    vector<bool> used(n, false);
    ll time = 0;
    for (ll i = 0; i < n; ++i)
      if (!used[i])
        dfs(i, time, n, used, res, tin, tup);
    return res;
  }
private:
  ll n;
  vector<vector<ll>> g;
  void dfs(ll v, ll &time, ll p,
           vector<bool> &used, vector<ll> &res,
           vector<ll> &tin, vector<ll> &tup) {
    used[v] = true;
    tin[v] = tup[v] = time++;
    ll child_count = 0;
    bool apoint = false;
    for (ll u : g[v]) {
      if (u == p) continue;
      if (used[u]) {
        tup[v] = min(tup[v], tin[u]);
      } else {
        dfs(u, time, v, used, res, tin, tup);
        tup[v] = min(tup[v], tup[u]);
        if (tup[u] >= tin[v] && p != n)
          apoint = true;
        ++child_count;
      }
    }
    if (apoint || (p == n && child_count > 1))
      res.push_back(v);
  }
};