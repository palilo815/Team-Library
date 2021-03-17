/**
 * using mint = mint<998244353>;
 */
template <int _mod>
struct mint {
    mint() : v(0) {}
    mint(int64_t _v) : v(int(_v % mod)) {
        if (v < 0) v += mod;
    }

    /**
     * @note O(log mod)
     * @return `inv`, num * inv = 1 (% mod)
     */
    mint inv() const {
        if (is_prime) {
            assert(v);
            return pow(mod - 2);
        } else {
            int m0 = 0, m1 = 1, a = v, m = mod;
            while (a != 0) {
                int t = m / a;
                m -= t * a;
                swap(a, m);
                m0 -= t * m1;
                swap(m0, m1);
            }
            assert(m == 1);
            mint res;
            res.v = m0 < 0 ? m0 + mod : m0;
            return res;
        }
    }
    /**
     * @note O(log mod)
     * @return -num % mod
     */
    mint neg() const {
        mint res;
        res.v = v ? mod - v : 0;
        return res;
    }
    /**
     * @note O(log p)
     * @return num^p % mod
     */
    mint pow(int64_t p) const {
        assert(p >= 0);
        int64_t x = v, r = 1;
        while (p) {
            if (p & 1) r = r * x % mod;
            p >>= 1;
            x = x * x % mod;
        }
        mint res;
        res.v = r;
        return res;
    }

    operator int() const { return v; }

    mint operator-() const { return neg(); }
    mint operator+() const { return mint(*this); }

    mint& operator++() {
        if (++v == mod) v = 0;
        return *this;
    }
    mint& operator--() {
        v = v ? v - 1 : mod - 1;
        return *this;
    }
    mint& operator+=(const mint& o) {
        v -= mod - o.v;
        if (v < 0) v += mod;
        return *this;
    }
    mint& operator-=(const mint& o) {
        v -= o.v;
        if (v < 0) v += mod;
        return *this;
    }
    mint& operator*=(const mint& o) {
        v = int64_t(v) * o.v % mod;
        return *this;
    }
    mint& operator/=(const mint& o) {
        return *this *= o.inv();
    }

    friend ostream& operator<<(ostream& out, const mint& n) { return out << int(n); }
    friend istream& operator>>(istream& in, mint& n) {
        int64_t _v;
        in >> _v;
        n = mint(_v);
        return in;
    }

    friend mint operator++(mint& a, int) {
        mint r = a;
        ++a;
        return r;
    }
    friend mint operator--(mint& a, int) {
        mint r = a;
        --a;
        return r;
    }
    friend mint operator+(const mint& a, const mint& b) { return mint(a) += b; }
    friend mint operator-(const mint& a, const mint& b) { return mint(a) -= b; }
    friend mint operator*(const mint& a, const mint& b) { return mint(a) *= b; }
    friend mint operator/(const mint& a, const mint& b) { return mint(a) /= b; }
    friend bool operator==(const mint& a, const mint& b) { return a.v == b.v; }
    friend bool operator!=(const mint& a, const mint& b) { return a.v != b.v; }

private:
    static constexpr int mod = _mod;
    static constexpr bool is_prime = mod == 998'244'353 || mod == 1'000'000'007;
    static_assert(_mod > 0);

    int v;
};