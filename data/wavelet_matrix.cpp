/**
 * @author  palilo
 * @brief   wavelet_matrix & helper class bit_array for bit prefix sum
 * @warning only non-negative integers are allowed in wavelet_matrix
 *          but allowed in compressed_wavelet_matrix. it will perform coordinate compression
 */

class bit_array {
    using block_t = unsigned long long;

    const size_t size;
    vector<block_t> bit;
    vector<int> pref;

public:
    bit_array(size_t n) : size((n + 63) >> 6), bit(size), pref(size + 1) {}

    void set(size_t i, bool v) {
        const auto block_id = i >> 6, bit_id = i & 63;
        bit[block_id] = (bit[block_id] & ~(static_cast<block_t>(1) << bit_id)) | (static_cast<block_t>(v) << bit_id);
    }
    void build() {
        for (size_t i = 0; i != size; ++i) {
            pref[i + 1] = pref[i] + __builtin_popcountll(bit[i]);
        }
    }
    size_t rank(size_t r, bool value) const {
        return value ? rank(r) : r - rank(r);
    }
    size_t rank(size_t l, size_t r, bool value) const {
        return value ? rank(r) - rank(l) : (r - l) - (rank(r) - rank(l));
    }

private:
    size_t rank(size_t r) const {
        return pref[r >> 6] + __builtin_popcountll(bit[r >> 6] & ((static_cast<block_t>(1) << (r & 63)) - 1));
    }
};

template <typename T>
class wavelet_matrix {
    const size_t size, height;
    vector<bit_array> bit_matrix;
    vector<int> mid_point;

public:
    wavelet_matrix(vector<T> v) : size(v.size()), height(1 + __lg(*max_element(v.begin(), v.end()))),
                                  bit_matrix(height, bit_array(size)), mid_point(height) {
        for (const auto& x : v) {
            assert(x >= 0);
        }
        for (auto h = height; h--;) {
            for (size_t i = 0; i != size; ++i) {
                bit_matrix[h].set(i, v[i] >> h & 1);
            }
            bit_matrix[h].build();
            mid_point[h] = stable_partition(v.begin(), v.end(), [&](const auto& x) {
                return !(x >> h & 1);
            }) - v.begin();
        }
    }
    // # of x in [0, r)
    size_t rank(size_t r, T x) const {
        size_t l = 0;
        for (size_t h = height; h--;) {
            shrink(l, r, h, x >> h & 1);
        }
        return r - l;
    }
    // k-th (0-based) smallest value in [l, r)
    T kth_smallest(size_t l, size_t r, size_t k) const {
        size_t ret = 0;
        for (size_t h = height; h--;) {
            const auto zeros = bit_matrix[h].rank(r, false) - bit_matrix[h].rank(l, false);
            const auto value = zeros <= k;
            if (value) {
                ret |= static_cast<T>(1) << h;
                k -= zeros;
            }
            shrink(l, r, h, value);
        }
        return ret;
    }
    // k-th (0-based) largest value in [l, r)
    T kth_largest(size_t l, size_t r, size_t k) const {
        return kth_smallest(l, r, r - l - k - 1);
    }

private:
    void shrink(size_t& l, size_t& r, size_t h, bool value) const {
        l = bit_matrix[h].rank(l, value) + mid_point[h] * value;
        r = bit_matrix[h].rank(r, value) + mid_point[h] * value;
    }
};

template <typename T>
class compressed_wavelet_matrix {
    vector<T> sorted_v;
    wavelet_matrix<T> wm;

public:
    compressed_wavelet_matrix(vector<T> v) : sorted_v(v), wm(move(compress(move(v)))) {}

    size_t rank(size_t r, T x) const {
        return wm.rank(r, get_index(x));
    }
    T kth_smallest(size_t l, size_t r, size_t k) const {
        return sorted_v[wm.kth_smallest(l, r, k)];
    }
    T kth_largest(size_t l, size_t r, size_t k) const {
        return sorted_v[wm.kth_largeest(l, r, k)];
    }

private:
    int get_index(T value) {
        auto it = lower_bound(sorted_v.begin(), sorted_v.end(), value);
        assert(it != sorted_v.end() && !(value < *it));
        return it - sorted_v.begin();
    }
    vector<int> compress(const vector<T> v) {
        sort(sorted_v.begin(), sorted_v.end());
        sorted_v.erase(unique(sorted_v.begin(), sorted_v.end()), sorted_v.end());
        vector<int> index(v.size());
        transform(v.begin(), v.end(), index.begin(), [&](const auto& x) {
            return lower_bound(sorted_v.begin(), sorted_v.end(), x) - sorted_v.begin();
        });
        return index;
    }
};