/**
 * @link
 *      https://github.com/spaghetti-source/algorithm/blob/master/combinatorics/permutation_index.cc
 *
 * @brief 
 *      compute the lexicographical index of the permutation
 *      `index`   = [permutation] -> [lexicographical index]
 *      `unindex` = [lexicographical index] -> [permutation]
 * 
 * @warning
 * 		duplicated numbers are NOT allowed
 * 
 * @note 
 *      $ O(n \log n) $
 */
class indexing_permutation {
    using num = unsigned long long;

public:
    num index(vector<int> x) {
        num r = 0;
        bit.assign(x.size() + 1, 0);
        for (int i = 0; i < int(x.size()); ++i) {
            int s = x[i];
            for (int k = x[i]; k; k &= k - 1) s -= bit[k];
            r = (x.size() - i) * r + s;
            for (int k = x[i] + 1; k < int(x.size()); k += k & -k) ++bit[k];
        }
        return r;
    }
    vector<int> unindex(num r, int n) {
        vector<int> d(n), x(n, n);
        for (int i = n; i--;) {
            d[i] = r % (n - i);
            r /= (n - i);
        }

        bit.assign(n + 1, 0);
        for (int k = 1; k <= n; ++k) bit[k] = k & -k;
        for (int i = 0; i < n; ++i) {
            for (int s : {1, 2, 4, 8, 16}) x[i] |= (x[i] >> s);
            for (int p = ++x[i]; p; p >>= 1, x[i] |= p)
                if (x[i] <= n && bit[x[i]] <= d[i])
                    d[i] -= bit[x[i]];
                else
                    x[i] ^= p;
            for (int k = x[i] + 1; k < int(x.size()); k += k & -k) --bit[k];
        }
        return x;
    }

private:
    vector<int> bit;
};