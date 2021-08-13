/**
 * @author  palilo 
 * @brief   Segment Tree
 * @warning must be used when (length of interval) or (order) of child nodes doesn't matter
 * @todo    e  -> identity element
 *          op -> unite two nodes
 */
template <typename node_t>
class segtree {
    const node_t e = node_t {};
    const int n;
    vector<node_t> tree;

public:
    segtree(int _n) : n(_n), tree(n << 1, e) {}

    node_t& operator[](int i) { return tree[n + i]; }
    void build() {
        for (int i = n; i--;)
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
    void pull(int i) {
        tree[i] = op(tree[i << 1], tree[i << 1 | 1]);
    }
    node_t op(node_t lhs, node_t rhs) {
        assert(false);
        return node_t {};
    }
};