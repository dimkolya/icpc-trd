// merge_sort(a, 0, n)
void merge_sort(vector<ll> &a, ll l, ll r) {
    if (l + 1 == r) return;
    ll m = (l + r) / 2;
    merge_sort(a, l, m);
    merge_sort(a, m, r);
    inplace_merge(a.begin() + l,
                  a.begin() + m,
                  a.begin() + r);
//    merge(l, m, r, a);
}

//for inversions
ll inv = 0;
void merge(ll l, ll m, ll r, vector<ll> &a) {
    vector<ll> t; t.reserve(r - l);
    ll i = l, j = m;
    while (i < m && j < r)
        if (a[i] <= a[j]) t.push_back(a[i++]);
        else t.push_back(a[j++]), inv += m - i;
    while (i < m) t.push_back(a[i++]);
    while (j < r) t.push_back(a[j++]);
    copy(t.begin(), t.end(), a.begin() + l);
}