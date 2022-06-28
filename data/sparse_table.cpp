/**
 * @author  palilo
 * @brief   sparse table
 * @note    $O(1)$ for query, $O(n \log n)$ for initialization
 *          in most cases, segment tree is better
 * @example range minimum query
 *          vector<int> a;
 *          auto f = [&](const int& l, const int& r) { return min(l, r); };
 *          sparse_table<int, decltype(f)> sparse(a, INT_MIN, f);
 */
template <typename T, typename F>
class SparseTable {
    const size_t n;
    const T e;
    const F f;
    std::vector<std::vector<T>> dp;

public:
    SparseTable(std::vector<T> a, T e, F f) : n(a.size()), e(e), f(f) {
        const auto height = std::__lg(n) + 1;
        dp.resize(height);
        dp[0] = move(a);
        for (size_t i = 1, k = 1; i != height; ++i, k <<= 1) {
            dp[i].resize(n - (k << 1) + 1);
            for (size_t j = 0; j + (k << 1) <= n; ++j) {
                dp[i][j] = f(dp[i - 1][j], dp[i - 1][j + k]);
            }
        }
    }
    auto query(size_t l, size_t r) {
        if (l == r) return e;
        assert(l < r and r <= n);
        const auto k = std::__lg(r - l);
        return f(dp[k][l], dp[k][r - (1 << k)]);
    }
};
