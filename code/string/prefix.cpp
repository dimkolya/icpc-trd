// pi[i] = max{k | k<= i, s[0..k-1]=s[i-k+1..i-1]}
vector<ll> p(n, 0);
for (ll i = 1; i < n; ++i) {
  ll j = p[i - 1];
  while (j > 0 && s[j] != s[i]) j = p[j - 1];
  if (s[j] == s[i]) ++j;
  p[i] = j;
}