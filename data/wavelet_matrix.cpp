/**
 * @link
 *      http://kmyk.github.io/competitive-programming-library/data_structure/wavelet_matrix.hpp
 * 
 * @brief
 *      Wavelet Matrix
 * 
 * @note 
 *      `rank(value, l, r)`
 *      	@return # of value in [l, r)
 *                  $ O(BITS) $
 *      
 *      `select(value, k)`
 *          @return index of the k-th occurence of value
 *                  $ O(BITS \log{\frac{n}{64})} $
 *      `select(value, k, l)`
 *          @return index of the k-th occurence of value in [l, n)
 * 
 *      `access(i)`
 *          @return i-th element
 *                  $ O(BITS) $
 * 
 *      `quantile(k, l, r)`
 *          @return k-th value in [l, r)
 *                  $ O(BITS) $
 * 
 *      `range_frequency(l, r, value_l, value_r)`
 *          @return # of values in [value_l, value_r) in range [l, r)
 *                  $ O(BITS) $
 */

class fully_indexable_dictionary {
    static constexpr int block_size = 64;
    vector<uint64_t> block;
    vector<int> rank_block;

public:
    int n;
    fully_indexable_dictionary() = default;

    template <typename T>
    fully_indexable_dictionary(const vector<T>& bits) : n(bits.size()) {
        const int block_count = n / block_size + 1;

        block.resize(block_count);
        for (int i = 0; i < n; ++i)
            if (bits[i])
                block[i / block_size] |= 1ull << (i % block_size);

        rank_block.resize(block_count);
        for (int i = 1; i < block_count; ++i)
            rank_block[i] = rank_block[i - 1] + __builtin_popcountll(block[i - 1]);
    }

    int rank(bool value, int r) const {
        assert(0 <= r and r <= n);
        uint64_t mask = (1ull << (r % block_size)) - 1;
        int rank_1 = rank_block[r / block_size] + __builtin_popcountll(block[r / block_size] & mask);
        return value ? rank_1 : r - rank_1;
    }
    int rank(bool value, int l, int r) const {
        assert(0 <= l and l <= r and r <= n);
        return rank(value, r) - rank(value, l);
    }

    int select(bool value, int k) const {
        if (k >= rank(value, n)) return n;

        int lo = 0, hi = int(block.size()) - 1;
        while (lo != hi) {
            int mid = (lo + hi) >> 1;
            (value ? rank_block[mid] : mid * block_size - rank_block[mid]) <= k ? lo = mid : hi = mid - 1;
        }

        lo *= block_size;
        hi = min(n, lo + block_size);
        while (lo != hi) {
            int mid = (lo + hi) >> 1;
            rank(value, mid) <= k ? lo = mid : hi = mid - 1;
        }
        return lo;
    }
    int select(bool value, int k, int l) const {
        assert(0 <= l and l <= n);
        return select(value, k + rank(value, l));
    }

    bool access(int i) const {
        assert(0 <= i and i < n);
        return block[i / block_size] >> (i % block_size) & 1;
    }
};

template <int BITS>
class wavelet_matrix {
    const int n;
    array<fully_indexable_dictionary, BITS> fid;
    array<int, BITS> zero_count;

public:
    template <typename T>
    wavelet_matrix(vector<T> data) : n(data.size()) {
        vector<uint8_t> bits(n);
        vector<T> next(n);

        for (int k = BITS; k--;) {
            int lo = 0, hi = n;
            for (int i = 0; i < n; ++i) {
                bits[i] = data[i] >> k & 1;
                (bits[i] ? next[--hi] : next[lo++]) = data[i];
            }

            fid[k] = fully_indexable_dictionary(bits);
            zero_count[k] = lo;
            reverse(next.begin() + hi, next.end());
            data.swap(next);
        }
    }

    int rank(uint64_t value, int l, int r) const {
        assert(0 <= value and value < (1ull << BITS));
        assert(0 <= l and l <= r and r <= n);

        for (int k = BITS; k--;) {
            bool p = value >> k & 1;
            l = fid[k].rank(p, l) + p * zero_count[k];
            r = fid[k].rank(p, r) + p * zero_count[k];
        }
        return r - l;
    }
    int select(uint64_t value, int k) const {
        assert(0 <= value and value < (1ull << BITS));
        assert(0 <= k);

        // do rank(value, 0, size) with logging
        vector<int> l(BITS + 1), r(BITS + 1);
        r[BITS] = fid[0].n;

        for (int d = BITS; d--;) {
            bool p = value >> d & 1;
            l[d] = fid[d].rank(p, l[d + 1]) + p * zero_count[d];
            r[d] = fid[d].rank(p, r[d + 1]) + p * zero_count[d];
        }
        if (r[0] - l[0] <= k) return fid[0].n;

        // trace the log inversely
        for (int d = 0; d < BITS; ++d) {
            bool p = value >> d & 1;
            k = fid[d].select(p, k, l[d + 1]) - l[d + 1];
        }
        return k;
    }
    int select(uint64_t value, int k, int l) const {
        return select(value, k + rank(value, l));
    }
    uint64_t access(int i) const {
        assert(0 <= i and i < fid[0].n);
        uint64_t acc = 0;
        for (int k = BITS; k--;) {
            bool p = fid[k].access(i);
            acc |= uint64_t(p) << k;
            i = fid[k].rank(p, i) + p * zero_count[k];
        }
        return acc;
    }
    uint64_t quantile(int k, int l, int r) {
        assert(0 <= k);
        assert(0 <= l and l <= r and r <= fid[0].n);
        if (r - l <= k) return 1ull << BITS;
        uint64_t acc = 0;
        for (int d = BITS; d--;) {
            int lc = fid[d].rank(true, l);
            int rc = fid[d].rank(true, r);
            int zero = (r - l) - (rc - lc);
            bool p = (k >= zero);
            if (p) {
                acc |= 1ull << d;
                l = lc + zero_count[d];
                r = rc + zero_count[d];
                k -= zero;
            } else {
                l -= lc;
                r -= rc;
            }
        }
        return acc;
    }
    int range_frequency(int l, int r, uint64_t value_l, uint64_t value_r) const {
        assert(0 <= l and l <= r and r <= fid[0].n);
        assert(0 <= value_l and value_l <= value_r and value_r <= (1ull << BITS));
        return range_frequency(BITS - 1, l, r, 0, value_l, value_r);
    }

private:
    int range_frequency(int k, int l, int r, uint64_t v, uint64_t a, uint64_t b) const {
        if (l == r) return 0;
        if (k == -1) return (a <= v and v < b) ? r - l : 0;
        uint64_t nv = v | (1ull << k);
        uint64_t nnv = nv | ((1ull << k) - 1);
        if (nnv < a or b <= v) return 0;
        if (a <= v and nnv < b) return r - l;
        int lc = fid[k].rank(true, l);
        int rc = fid[k].rank(true, r);
        return range_frequency(k - 1, l - lc, r - rc, v, a, b) +
               range_frequency(k - 1, lc + zero_count[k], rc + zero_count[k], nv, a, b);
    }
};