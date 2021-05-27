/**
 * @link
 *      https://github.com/spaghetti-source/algorithm/blob/master/combinatorics/permutation_hash.cc
 *
 * @brief 
 *      hash function for permutation
 *      computed hash value is an integer in [0, n!)
 * 
 * @note 
 *      $ O(n) $
 */
class hash_permutation {
public:
    int64_t hash_perm(vector<int> x) {
        int n = x.size();
        vector<int> y(n);
        for (int i = 0; i < n; ++i) y[x[i]] = i;
        int64_t c = 0, fac = 1;
        for (; n > 1; --n) {
            c += fac * x[n - 1];
            fac *= n;
            swap(x[n - 1], x[y[n - 1]]);
            swap(y[n - 1], y[x[y[n - 1]]]);
        }
        return c;
    }
    vector<int> unhash_perm(int64_t r, int n) {
        vector<int> x(n);
        iota(x.begin(), x.end(), 0);
        for (; n > 0; --n) {
            swap(x[n - 1], x[r % n]);
            r /= n;
        }
        return x;
    }
};