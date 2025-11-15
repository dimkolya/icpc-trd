// z[i] = max{k | k<=i, s[0..k-1]=s[i..i+k-1]}
vector<ll> foo(string s) {
  ll n = s.size();
  ll l = 0, r = 0;
  vector<ll> z(n);
  for (ll i = 1; i < n; ++i) {
    if (i <= r) z[i] = min(r - i + 1, z[i - l]);
    while (i+z[i]<n && s[z[i]] == s[i+z[i]]) ++z[i];
    if (r < i + z[i] - 1) {
      l = i;
      r = i + z[i] - 1;
    }
  }
  return z;
}