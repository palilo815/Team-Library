/**
 * @author  palilo 
 * @brief   segment-tree (complete binary tree, i.e. every non-leaf nodes have 2 child nodes)
 * @warning must be used when (length of interval) or (order) of the child nodes doesn't matter
 *          if it is matter, use "seg_full" (full binary tree).
 * @todo    e  <- identity element (op(e, any_value) = e)
 *          op <- unite two nodes
 */
template <typename node_t>
class segtree {
    // change this (1/2)
    const node_t e {};
    // change this (1/2)
    const size_t n;
    vector<node_t> tree;

public:
    segtree(size_t n) : n(n), tree(n << 1, e) {}

    node_t& operator[](size_t i) { return tree[n + i]; }
    void build() {
        for (size_t i = n; i--;) {
            pull(i);
        }
    }
    void set(size_t idx, node_t val) {
        assert(0 <= idx and idx < n);
        tree[idx += n] = val;
        while (idx >>= 1) pull(idx);
    }
    node_t prod(size_t l, size_t r) const {
        assert(0 <= l and l <= r and r <= n);
        node_t ret = e;
        for (l += n, r += n; l != r; l >>= 1, r >>= 1) {
            if (l & 1) ret = op(ret, tree[l++]);
            if (r & 1) ret = op(tree[--r], ret);
        }
        return ret;
    }
    node_t all_prod() const { return tree[1]; }
    void clear() { fill(tree.begin(), tree.end(), e); }

private:
    void pull(size_t i) {
        tree[i] = op(tree[i << 1], tree[i << 1 | 1]);
    }
    // change this (2/2)
    node_t op(node_t lhs, node_t rhs) const {
        assert(false);
        return node_t {};
    }
    // change this (2/2)
};