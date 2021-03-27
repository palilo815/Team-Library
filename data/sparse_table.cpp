/**
 * sparse_table rmq(move(vector));
 */
template <typename T>
struct sparse_table {
    sparse_table(vector<T> a) : n(a.size()), dp(__lg(n) + 1) {
        dp[0] = a;
        for (int i = 1, k = 1; i < int(dp.size()); ++i, k <<= 1) {
            dp[i].resize(n - (k << 1) + 1);
            for (int j = 0; j + (k << 1) <= n; ++j)
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j + k]);
        }
    }
    T query(int l, int r) {
        assert(0 <= l && r <= n);
        if (l == r) return 0;
        const int k = __lg(r - l);
        return max(dp[k][l], dp[k][r - (1 << k)]);
    }

private:
    const int n;
    vector<vector<T>> dp;
};