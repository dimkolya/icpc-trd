struct graph {
  graph(...) {...}
  set<pair<ll, ll>> get_bridges() const {
    set<pair<ll, ll>> result;
    vector<ll> enter(n, 0), ret(n, 0);
    ll time = 0;
    for (ll i = 0; i < n; ++i)
      if (enter[i] == 0)
        dfs1(i, time, n, result, enter, ret);
    return result;
  }
  vector<ll> get_edge_components() const {
    set<pair<ll, ll>> bs = get_bridges();
    ll cnt = 0;
    vector<ll> res(n, 0);
    for (ll i = 0; i < n; ++i) {
      if (res[i] == 0) {
        ++cnt;
        dfs2(i, cnt, cnt, res, bs);
      }
    }
    return res;
  }
private:
  ll n;
  vector<vector<ll>> g;
  static pair<ll, ll> edge(ll u, ll v) {
    return make_pair(min(u, v), max(u, v));
  }
  void dfs1(ll v, ll &time, ll p,
            set<pair<ll, ll>> &res,
            vector<ll> &tin, vector<ll> &tup) const {
    ++time;
    tin[v] = time;
    tup[v] = time;
    for (ll u : g[v]) {
      if (u == p) continue;
      if (tin[u] != 0) {
        tup[v] = min(tup[v], tin[u]);
      } else {
        dfs1(u, time, v, res, tin, tup);
        tup[v] = min(tup[v], tup[u]);
        if (tup[u] > tin[v]
            && count(g[v].begin(),g[v].end(),u)==1) {
          res.insert(edge(u, v));
        }
      }
    }
  }
  void dfs2(ll v, ll cur, ll &cnt,
            vector<ll> &res,
            const set<pair<ll, ll>> &bs) const {
    res[v] = cur;
    for (ll u : g[v]) {
      if (res[u] == 0) {
        if (bs.find(edge(u, v)) != bs.end()) {
          ++cnt;
          dfs2(u, cnt, cnt, res, bs);
        } else
          dfs2(u, cur, cnt, res, bs);
      }
    }
  }
};