mt19937_64 gen(42);
struct node {
    ll x;
    ll y = gen();
    node *left = nullptr;
    node *right = nullptr;
};
node *merge(node *l, node *r) {
    if (l == nullptr) return r;
    if (r == nullptr) return l;
    if (l->y < r->y) {
        r->left = merge(l, r->left);
        return r;
    } else {
        l->right = merge(l->right, r);
        return l;
    }
}
// (l < x, x <= r)
pair<node *, node *> split(node *t, ll x) {
    if (t == nullptr) return {nullptr, nullptr};
    if (t->x < x) {
        auto [l, r] = split(t->right, x);
        t->right = l;
        return {t, r};
    } else {
        auto [l, r] = split(t->left, x);
        t->left = r;
        return {l, t};
    }
}
node *find(node *t, ll x) {
    while (t && t->x != x) {
        if (t->x < x) t = t->right;
        else t = t->left;
    }
    return t;
}
node *lower_bound(node *t, ll x) {
    node *result = nullptr;
    while (t) {
        if (t->x < x) t = t->right;
        else result = t, t = t->left;
    }
    return result;
}
node *upper_bound(node *t, ll x) {
    node *result = nullptr;
    while (t) {
        if (t->x <= x) t = t->right;
        else result = t, t = t->left;
    }
    return result;
}
node *under_bound(node *t, ll x) {
    node *result = nullptr;
    while (t) {
        if (t->x >= x) t = t->left;
        else result = t, t = t->right;
    }
    return result;
}
// t = insert(t, x)
node *insert(node *t, ll x) {
    if (find(t, x)) return t;
    auto [l, r] = split(t, x);
    return merge(merge(l, new node(x)), r);
}
// t = erase(t, x)
node *erase(node *t, ll x) {
    if (!find(t, x)) return t;
    auto [l, mr] = split(t, x);
    auto [m, r] = split(mr, x + 1);
    return merge(l, r);
}