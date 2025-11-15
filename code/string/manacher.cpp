// s[l..r] - palindrome iff d[l+r] >= r-l+1
vector<ll> manacher(const string &t){
  string s;
  for(ll i=0; i < t.size(); ++i){
    s.push_back(t[i]);
    s.push_back('#');
  }
  ll n=s.size();
  vector<ll> d(n, 1);
  ll l=0, r=0;
  for(ll i=1; i<n; ++i){
    if(i<r)
      d[i] = min(r-i+1, d[l+r-i]);
    while(i-d[i]>=0 && i+d[i]<n &&
          s[i-d[i]]==s[i+d[i]])
      ++d[i];
    if(i+d[i]-1>r)
      l = i-d[i]+1, r = i+d[i]-1;
  }
  return d;
}