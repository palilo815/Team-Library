template <typename node_t>
struct complete_seg {
    complete_seg(int _n) : n(_n),
                           tree(_n << 1, e) {}

    node_t& operator[](int i) { return tree[n + i]; }
    void build() {
        for (int i = n - 1; i; --i)
            pull(i);
    }
    void set(int idx, node_t val) {
        assert(0 <= idx and idx < n);

        tree[idx += n] = val;
        while (idx >>= 1) pull(idx);
    }
    node_t prod(int l, int r) {
        assert(0 <= l and l <= r and r <= n);

        node_t ret = e;
        for (l += n, r += n; l != r; l >>= 1, r >>= 1) {
            if (l & 1) ret = op(ret, tree[l++]);
            if (r & 1) ret = op(tree[--r], ret);
        }
        return ret;
    }

private:
#define lson (i << 1)
#define rson (i << 1 | 1)
    const node_t e = node_t {};
    const int n;
    vector<node_t> tree;

    void pull(int i) {
        tree[i] = op(tree[lson], tree[rson]);
    }
    node_t op(node_t lhs, node_t rhs) {
        assert(true);
        return node_t {};
    }
#undef lson
#undef rson
};