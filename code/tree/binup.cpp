// Min edge on path(u,v)
vector up(n + 1, vector<ll>(20, n));
vector dp(n + 1, vector<ll>(20, INF));
vector<ll> d(n + 1, -1);
auto build = [&](auto &&build,ll v,ll p,ll c)->void{
  d[v] = d[p] + 1;
  up[v][0] = p;
  dp[v][0] = c;
  for (auto [u, k] : g[v]) {
    if (u == p) continue;
    build(build, u, v, k);
  }
};
build(build, 0, n, INF);
for (ll k = 1; k < 20; ++k)
  for (ll i = 0; i < n; ++i) {
    up[i][k] = up[up[i][k - 1]][k - 1];
    dp[i][k] = min(dp[i][k - 1],
                   dp[up[i][k - 1]][k - 1]);
  }
auto lca = [&](ll v, ll u) -> ll {
  if (d[v] < d[u]) swap(v, u);
  ll result = INF;
  for (ll k = 19; k >= 0; --k)
    if (d[up[v][k]] >= d[u]) {
      result = min(result, dp[v][k]);
      v = up[v][k];
    }
  if (v == u) return result;
  for (ll k = 19; k >= 0; --k)
    if (up[v][k] != up[u][k]) {
      result = min(result, dp[v][k]);
      result = min(result, dp[u][k]);
      v = up[v][k], u = up[u][k];
    }
  result = min(result, dp[v][0]);
  result = min(result, dp[u][0]);
  return result;
};

// Online (vertex 0 already exists):
//  1) link(v, p)
//  2) kill(v): dead[v] = true
vector up(m + 1, vector<ll>(20, m));
vector<ll> d(m + 1, -1);
d[0] = 0;
vector<ll> nearest(m + 1);
vector<ll> dead(m + 1);
std::iota(nearest.begin(), nearest.end(), 0);
auto link = [&](ll v, ll p) -> void {
  d[v] = d[p] + 1;
  up[v][0] = p;
  for (ll k = 1; k < 20; ++k)
    up[v][k] = up[up[v][k - 1]][k - 1];
};
auto get = [&](auto &&get, ll v) -> ll {
  if (dead[nearest[v]])
    nearest[v] = get(get, up[v][0]);
  return nearest[v];
};
auto lca = [&](ll v, ll u) -> ll {
  if (d[v] < d[u]) swap(v, u);
  for (ll k = 19; k >= 0; --k)
    if (d[up[v][k]] >= d[u]) {
      v = up[v][k];
    }
  if (v == u) return get(get, v);
  for (ll k = 19; k >= 0; --k) {
    if (up[v][k] != up[u][k]) {
      v = up[v][k], u = up[u][k];
    }
  }
  return get(get, up[v][0]);
};