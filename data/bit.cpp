template <typename T>
class BinaryIndexedTree {
    const size_t n;
    std::vector<T> tree;

public:
    explicit BinaryIndexedTree(size_t n) : n(n), tree(n + 1) {}

    auto build() {
        for (size_t i = 1; i < n; ++i) {
            if (i + (i & -i) <= n) {
                tree[i + (i & -i)] += tree[i];
            }
        }
    }
    auto fake_add(size_t i, T val) {
        tree[i + 1] += val;
    }
    // a[i] += val
    auto add(size_t i, T val) {
        assert(i <= n);
        for (++i; i <= n; i += i & -i) {
            tree[i] += val;
        }
    }
    // return sum a[0, i)
    [[nodiscard]] auto sum(size_t i) const {
        assert(i <= n);
        T ret = 0;
        for (; i; i &= i - 1) {
            ret += tree[i];
        }
        return ret;
    }
    // return sum a[l, r)
    [[nodiscard]] auto sum(size_t l, size_t r) const {
        assert(l <= r && r <= n);
        return sum(r) - sum(l);
    }
    // return a[i]
    [[nodiscard]] auto get(size_t i) const {
        assert(i < n);
        return i & 1 ? sum(i, i + 1) : tree[i + 1];
    }
    // return minimum i s.t. sum[0...i] >= k
    [[nodiscard]] auto lower_bound(T k) const {
        size_t x = 0;
        for (size_t pw = 1 << std::__lg(n); pw; pw >>= 1)
            if ((x | pw) <= n && tree[x | pw] < k)
                k -= tree[x |= pw];
        return x;
    }
    // return minimum i s.t. sum[0...i] > k
    [[nodiscard]] auto upper_bound(T k) const {
        size_t x = 0;
        for (size_t pw = 1 << std::__lg(n); pw; pw >>= 1)
            if ((x | pw) <= n && tree[x | pw] <= k)
                k -= tree[x |= pw];
        return x;
    }
};
