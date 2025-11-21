// Problem: array a[0]..a[n-1].
// Queries: find number of distinct elements in [L,R].
// add(i) - add a[i] to the Mo's block.
// rem(i) - remove a[i] from the Mo's block.
vector<int> a(n);
struct Query{
  int l, r, id;
};
vector<Query> query(Q);
const int B=500; //Block size
sort(query.begin(), query.end(),
		[](const Query &x, const Query &y){
  if(x.l/B != y.l/B)
    return x.l/B < y.l/B;
  return (x.l/B & 1) ? x.r < y.r : x.r > y.r;
});
vector<int> cnt(n);
int total=0;
auto add = [&](int i)->void{
  ++cnt[a[i]];
  if(cnt[a[i]]==1)
    ++total;
};
auto rem = [&](int i)->void{
  --cnt[a[i]];
  if(cnt[a[i]]==0)
    --total;
};
vector<int> ans(Q);
int l=0, r=0;
add(l);
for(auto [ql,qr,id] : query){
  while(l>ql) add(--l);
  while(r<qr) add(++r);
  while(l<ql) rem(l++);
  while(r>qr) rem(r--);
  ans[id] = total;
}