vector<ll> lis(vector<ll> &a) {
  ll n = a.size();
  vector<ll> dp(n + 1, INF), id(n + 1), p(n + 1);
  dp[0] = -INF;
  id[0] = -1;
  ll len = 0;
  for (ll i = 0; i < n; ++i) {
    ll l = lower_bound(dp.begin(), dp.end(), a[i])
           - dp.begin();
//  upper_bound for non-decreasing
    dp[l] = a[i];
    id[l] = i;
    p[i] = id[l - 1];
    if (dp[l] < INF) len = max(len, l);
  }
//  return len;
  vector<ll> ans;
  ll i = id[len];
  while (i != -1) {
    ans.push_back(a[i]);
    i = p[i];
  }
  reverse(ans.begin(), ans.end());
  return ans;
}