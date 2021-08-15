/**
 * @author  palilo
 * @brief   sparse table
 * @note    $O(1)$ for query, $O(n \log n)$ for initialization
 *          in most cases, segment tree is better
 * @example range minimum query
 *          auto f = [&](const int& l, const int& r) { return min(l, r); };
 *          sparse_table<int, decltype(f)> sparse(a, f);
 */
template <typename T, typename F>
class sparse_table {
    const size_t n;
    vector<vector<T>> dp;
    const F f;

public:
    sparse_table(vector<T> a, F f) : n(a.size()), dp(__lg(n) + 1), f(move(f)) {
        dp[0] = move(a);
        for (size_t i = 1, k = 1; i < dp.size(); ++i, k <<= 1) {
            dp[i].resize(n - (k << 1) + 1);
            for (size_t j = 0; j + (k << 1) <= n; ++j)
                dp[i][j] = f(dp[i - 1][j], dp[i - 1][j + k]);
        }
    }
    T query(size_t l, size_t r) {
        if (l == r) return 0;
        assert(0 <= l and l < r and r <= n);
        const size_t k = __lg(r - l);
        return f(dp[k][l], dp[k][r - (1 << k)]);
    }
};