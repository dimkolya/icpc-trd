vector<ll> d(n, INF); d[0] = 0;
priority_queue<pair<ll, ll>> q; q.emplace(0, 0);
vector<bool> used(n);
while (!q.empty()) {
  ll v = q.top().second; q.pop();
  if (used[v]) continue;
  used[v] = true;
  for (auto [u, w] : g[v]) {
    if (d[u] > d[v] + w) {
      d[u] = d[v] + w;
      q.emplace(-d[u], u);
    }
  }
}