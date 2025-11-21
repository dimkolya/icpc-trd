vector<ll> phi(n + 1);
iota(phi.begin(), phi.end(), 0);
for(ll x = 2; x <= n; ++x){
  if (phi[x] == x){
    for (ll y = x; y <= n; y += x)
      phi[y] -= phi[y] / x;
  }
}