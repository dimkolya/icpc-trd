vector<ll> d(n, -1);
vector<bool> used(n, false);
d[s] = 0;
for (ll i = 0; i < n - 1; ++i) {
  ll v = -1;
  for (ll u = 0; u < n; ++u)
    if (d[u] != -1 && !used[u]
        && (v == -1 || d[u] < d[v]))
      v = u;
  if (v == -1) break;
  used[v] = true;
  for (ll u = 0; u < n; ++u)
    if (d[u] == -1 || d[u] > d[v] + w[v][u])
      d[u] = d[v] + w[v][u];
}