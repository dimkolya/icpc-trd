vector<ll> d(n); // (n, INF)
d[0] = 0;
vector<ll> p(n, -1);
ll x;
for (ll i = 0; i < n; ++i) {
  x = -1;
  for (auto [u, v, w] : edges) {
    if (d[v] > d[u] + w) { // d[u] != INF
      d[v] = d[u] + w;
      p[v] = u;
      x = v;
    }
  }
}
if (x == -1) {
  // no negative cycles
} else {
  for (ll i = 0; i < n; ++i) x = p[x];
  vector<ll> path;
  for (ll cur = x;; cur = p[cur]) {
    path.push_back(cur);
    if (cur == x && path.size() > 1)
      break;
  }
  reverse(path.begin(), path.end());
}