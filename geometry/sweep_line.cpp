/**
 * @author palilo
 * @brief  line sweeping algorithm
 *         contains segments and maintains the total length they covered
 * @note   $O(\log n)$ for `update`
 *         $O(1)$ for `get_sum`
 */
template <typename T>
class sweep_line {
    const int n;
    vector<T> tree, len;
    vector<int> cnt;

public:
    sweep_line(const vector<T>& compressed) : n(compressed.size()), tree(n << 1), len(n << 1), cnt(n << 1) {
        for (int i = 0; i < n - 1; ++i) len[i + n] = compressed[i + 1] - compressed[i];
        for (int i = n - 1; i; --i) len[i] = len[i << 1] + len[i << 1 | 1];
    }
    /**
     * @brief   insert/remove segment [l, r)
     * @param l MUST BE A COMPRESSED INDEX 
     * @param r MUST BE A COMPRESSED INDEX 
     * @param v 1 if insert, -1 if remove
     */
    void update(int l, int r, int v) {
        l += n, r += n;
        const int l0 = l, r0 = r;
        for (; l != r; l >>= 1, r >>= 1) {
            if (l & 1) apply(l++, v);
            if (r & 1) apply(--r, v);
        }
        tree[l0] = cnt[l0] ? len[l0] : 0;
        tree[r0] = cnt[r0] ? len[r0] : 0;
        for (int i = l0 >> 1; i; i >>= 1)
            tree[i] = cnt[i] ? len[i] : tree[i << 1] + tree[i << 1 | 1];
        for (int i = r0 >> 1; i; i >>= 1)
            tree[i] = cnt[i] ? len[i] : tree[i << 1] + tree[i << 1 | 1];
    }
    T get_sum() const { return tree[1]; }

private:
    void apply(int i, int v) {
        tree[i] = (cnt[i] += v) ? len[i] : (i < n ? tree[i << 1] + tree[i << 1 | 1] : 0);
    }
};