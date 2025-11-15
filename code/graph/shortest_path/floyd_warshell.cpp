for (ll v = 0; v < n; ++v)
  d[v][v] = 0;
for (ll k = 0; k < n; ++k){
  for (ll v = 0; v < n; ++v){
    for (ll u = 0; u < n; ++u){
      if (d[v][k] < INF && d[k][u] < INF
         && d[v][u] > d[v][k] + d[k][u]){
        d[v][u] = max(d[v][k] + d[k][u], -INF);
        p[v][u] = p[k][u];
      }
      if (v==u && d[v][v]<0)
        x = v;
    }
  }
}
if(x == -1){
  // no negative cycles
  return;
} else {
  vector<ll> cycle;
  cycle.push_back(x);
  for(ll v = p[x][x]; v != x; v = p[x][v])
    cycle.push_back(v);
  reverse(cycle.begin(), cycle.end());
}
// restore path v -> u
vector<int> path;
path.push_back(u);
while(u != v){
  u = p[v][u];
  path.push_back(u);
}
reverse(path.begin(), path.end());