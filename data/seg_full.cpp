/**
 * @author  palilo 
 * @brief   segment tree (full binary tree, i.e. # of nodes = 2^k-1)
 * @todo    e  <- identity element
 *          op <- unite two nodes
 */
template <typename node_t>
class segtree {
    // change this (1/1)
    const node_t e {};
    // change this (1/1)
    const size_t n, height, size;

public:
    segtree(size_t n) : n(n), height(n ? __lg(n - 1) + 1 : 0), size(1 << height), tree(size << 1, e) {}

    node_t& operator[](size_t i) { return tree[size + i]; }
    void build() {
        for (size_t i = size; i--;) {
            pull(i);
        }
    }
    void set(size_t idx, node_t val) {
        assert(0 <= idx and idx < n);
        tree[idx += size] = val;
        while (idx >>= 1) pull(idx);
    }
    node_t prod(size_t l, size_t r) {
        assert(0 <= l and l <= r and r <= n);
        node_t lval = e, rval = e;
        for (l += size, r += size; l != r; l >>= 1, r >>= 1) {
            if (l & 1) lval = op(lval, tree[l++]);
            if (r & 1) rval = op(tree[--r], rval);
        }
        return op(lval, rval);
    }

private:
    inline int get_index(node_t& node) { return &node - tree.data(); }
    inline int get_depth(node_t& node) { return __lg(get_index(node)); }
    inline int get_height(node_t& node) { return height - get_depth(node); }
    inline int get_length(node_t& node) { return 1 << get_height(node); }
    inline int get_first(node_t& node) {
        int idx = get_index(node);
        int dep = __lg(idx);
        int len = 1 << height - dep;
        return len * (idx ^ 1 << dep);
    }
    void pull(size_t i) {
        tree[i] = op(tree[i << 1], tree[i << 1 | 1]);
    }
    // change this (2/2)
    node_t op(node_t lhs, node_t rhs) {
        assert(false);
        return node_t {};
    }
    // change this (2/2)
};