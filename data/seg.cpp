/**
 * @author  palilo 
 * @brief   segment-tree
 */
template <class T, class F>
class SegTree {
    const size_t n;
    const T e;
    const F f;
    std::vector<T> tree;

public:
    SegTree(size_t n, T e, F f) : n(n), e(e), f(f), tree(n << 1, e) {}

    auto operator[](size_t i) -> T& { return tree[n + i]; }

    auto build() {
        for (size_t i = n; i--;) {
            pull(i);
        }
    }

    auto set(size_t i, T val) {
        assert(i < n);
        tree[i += n] = val;
        while (i >>= 1) pull(i);
    }

    [[nodiscard]] auto prod(size_t l, size_t r) const {
        assert(l <= r and r <= n);
        T val = e;
        for (l += n, r += n; l != r; l >>= 1, r >>= 1) {
            if (l & 1) val = f(val, tree[l++]);
            if (r & 1) val = f(tree[--r], val);
        }
        return f(val, val);
    }

private:
    auto pull(size_t i) {
        tree[i] = f(tree[i << 1], tree[i << 1 | 1]);
    }
};
