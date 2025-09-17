struct dmst {
  struct edge {
    ll from, to;
    ll weight;
  };
  dmst() {
    ll m;
    cin >> size >> m;
    for (ll i = 0; i < m; ++i) {
      ll from, to;
      ll weight;
      cin >> from >> to >> weight;
      edges.emplace_back(from - 1, to - 1, weight);
    }
  }
  ll size_of_MST(ll root) {
    vector<bool> used(size, false);
    dfs(root, graph(size, edges, false), used);
    if (any_of(used.begin(), used.end(), [](bool i) {
      return !i;
    })) return INF; // doesn't exists
    ll result = 0;
    size_of_MST_loop(result, root, size, edges);
    return result;
  }
private:
  ll size; // n
  vector<edge> edges;
  vector<vector<ll>> graph(ll n, const vector<edge> &es,
                           bool tr) {
    vector<vector<ll>> result(n);
    for (auto &e : es)
      if (tr) result[e.to].push_back(e.from);
      else result[e.from].push_back(e.to);
    return result;
  }
  void size_of_MST_loop(ll &result, ll root, ll n,
                        const vector<edge> &es) {
    vector<ll> mine(n, INF);
    for (auto &e : es) {
      mine[e.to] = min(mine[e.to], e.weight);
    }
    for (ll i = 0; i < n; ++i) {
      if (i == root) continue;
      result += mine[i];
    }
    vector<vector<ll>> g(n);
    vector<edge> z;
    for (auto &e : es)
      if (e.weight == mine[e.to]) {
        g[e.from].push_back(e.to);
        z.push_back(e);
      }
    vector<bool> used(n);
    dfs(root, g, used); g.clear();
    if (all_of(used.begin(), used.end(), [](bool i) {
      return i;
    })) return;
    vector<ll> comp(condensation(n, z)); z.clear();
    vector<edge> nes;
    ll k = 0;
    for (auto &e : es) {
      ll from = comp[e.from];
      ll to = comp[e.to];
      k = max(k, max(from, to));
      if (from != to)
        nes.emplace_back(from, to,e.weight - mine[e.to]);
    }
    size_of_MST_loop(result, comp[root], k + 1, nes);
  }
  void dfs(ll v, const vector<vector<ll>> &g,
           vector<bool> &used) {
    used[v] = true;
    for (ll u : g[v])
      if (!used[u])
        dfs(u, g, used);
  }
  void dfs1(ll v, vector<bool> &used, vector<ll> &t,
            const vector<vector<ll>> &g) {
    used[v] = true;
    for (ll u : g[v])
      if (!used[u])
        dfs1(u, used, t, g);
    t.push_back(v);
  }
  void dfs2(ll v, ll k, vector<ll> &comp,
            const vector<vector<ll>> &gr) {
    comp[v] = k;
    for (ll u : gr[v])
      if (comp[u] == -1)
        dfs2(u, k, comp, gr);
  }
  vector<ll> condensation(ll n, const vector<edge> &e) {
    vector<bool> used(n, false);
    vector<ll> t;
    vector<vector<ll>> g(graph(n, e, false));
    for (ll v = 0; v < n; ++v)
      if (!used[v])
        dfs1(v, used, t, g);
    g.clear();
    std::reverse(t.begin(), t.end());
    ll k = 0;
    vector<ll> comp(n, -1);
    vector<vector<ll>> gr(graph(n, e, true));
    for (ll v : t)
      if (comp[v] == -1) {
        dfs2(v, k, comp, gr);
        ++k;
      }
    return comp;
  }
};