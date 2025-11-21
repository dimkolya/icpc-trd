vector<ll> st;
vector<ll> ans(n, -1);
for (ll i = 0; i < n; ++i) {
  while (!st.empty() && a[st.back()] > a[i]) {
    ans[st.back()] = i;
    st.pop_back();
  }
  st.push_back(i);
}