struct graph {
  graph(...) {...}
  vector<ll> get_bridges() {
    vector<ll> res;
    vector<ll> tin(n, 0);
    vector<ll> tup(n, 0);
    vector<bool> used(n, false);
    ll time = 0;
    for (ll i = 0; i < n; ++i)
      if (!used[i])
        dfs(i, time, i, used, res, tin, tup);
    return res;
  }
private:
  ll n;
  vector<vector<pair<ll, ll>>> g;
  void dfs(ll v, ll &time, ll p,
           vector<bool> &used, vector<ll> &res,
           vector<ll> &tin, vector<ll> &tup) {
    used[v] = true;
    tin[v] = time;
    tup[v] = time;
    ++time;
    for (ll i = 0; i < g[v].size(); ++i) {
      ll u = g[v][i].first;
      ll vu = g[v][i].second;
      if (u == p) continue;
      if (used[u]) {
        tup[v] = min(tup[v], tin[u]);
      } else {
        dfs(u, time, v, used, res, tin, tup);
        tup[v] = min(tup[v], tup[u]);
        if (tup[u] > tin[v])
          res.push_back(vu);
      }
    }
  }
};