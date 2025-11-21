// find maximal non-intersecting set of segments
sort(seg.begin(), seg.end(), [](auto a, auto b){
  return a.second < b.second;
});
ll cnt=0, cur=-INF;
for(auto x : seg){
  if(x.first >= cur){
    ++cnt;
    cur = x.second;
  }
}