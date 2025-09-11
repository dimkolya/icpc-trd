struct node {
    ll x;
    ll size = 1;
    ll y = gen();
    node *left = nullptr;
    node *right = nullptr;
};
ll size(node *t) {
    if (!t) return 0;
    return t->size;
}
void upd(node *t) {
    t->size = size(t->left) + size(t->right) + 1;
}
node *merge(node *l, node *r) {
    if (l == nullptr) return r;
    if (r == nullptr) return l;
    // push(l), push(r);
    if (l->y < r->y) {
        r->left = merge(l, r->left), upd(r);
        // if (r->left) r->left->parent = r;
        return r;
    } else {
        l->right = merge(l->right, r), upd(l);
        // if (l->right) l->right->parent = l;
        return l;
    }
}
// size(l) == x
pair<node *, node *> split(node *t, ll x) {
    if (t == nullptr) return {nullptr, nullptr};
    // push(t);
    if (size(t->left) < x) {
        auto [l,r]=split(t->right,x-size(t->left)-1);
        t->right = l, upd(t);
        // if (l) l->parent = t;
        // if (r) r->parent = nullptr;
        // t->parent = nullptr;
        return {t, r};
    } else {
        auto [l, r] = split(t->left, x);
        t->left = r, upd(t);
        // if (l) l->parent = nullptr;
        // if (r) r->parent = t;
        // t->parent = nullptr;
        return {l, t};
    }
}
void print(node *t) {
    if (!t) return;
    // push(t);
    print(t->left);
    cout << t->x << ' ';
    print(t->right);
}

//Lazy reverse [l,r) 0-index:
// auto [x, yz] = split(t, l);
// auto [y, z] = split(yz, r - l);
// y->reversed ^= true;
// t = merge(merge(x, y), z);
void push(node *t) {
    if (!t || !t->reversed) return;
    swap(t->left, t->right);
    if (t->left) t->left->reversed ^= true;
    if (t->right) t->right->reversed ^= true;
    t->reversed = false;
}

//Insert(i, k):
// 1) if a[i] == 0: a[i] = k;
// 2) else Insert(i + 1, a[i]), a[i] = k;
// auto [l, r] = split(t, i - 1);
// r = remove_next_zero(r);
// t = merge(merge(l, new node(k, false)), r);
bool has_zero(node *t) {
    if (!t) return false;
    return t->has_zero;
}
void upd(node *t) {
    t->size = size(t->left) + size(t->right) + 1;
    t->has_zero = (t->x == 0
            ||has_zero(t->left)||has_zero(t->right));
}
node *remove_next_zero(node *t) {
    if (!t) return t;
    if (has_zero(t->left)) {
        t->left = remove_next_zero(t->left);
    } else if (t->x == 0) {
        return merge(t->left, t->right);
    } else {
        t->right = remove_next_zero(t->right);
    }
    upd(t);
    return t;
}

// Index calculation
node *root(node *v) {
    while (v->parent) v = v->parent;
    return v;
}
node *begin(node *t) {
    while (true) {
        push(t);
        if (!t->left) break;
        t = t->left;
    }
    return t;
}
ll pos(node *v) {
    vector<ll> p;
    while (v->parent) {
        if (v->parent->left == v) {
            p.push_back(0);
        } else {
            p.push_back(1);
        }
        v = v->parent;
    }
    ll result = 0;
    std::reverse(p.begin(), p.end());
    for (ll i : p) {
        node *next = (i ? v->right : v->left);
        push(v);
        if (next != v->left) {
            result += size(v->left) + 1;
        }
        v = next;
    }
    push(v);
    result += size(v->left);
    return result;
}