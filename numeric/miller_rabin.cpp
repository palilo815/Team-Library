/**
 * @include modular
 */
struct miller_rabin {
    using i64 = int64_t;
    using u64 = uint64_t;

    bool is_prime(u64 n) {
        using namespace modular;
        if (n < 2) return false;
        if (n == 2 || n == 3) return true;
        if (n % 6 != 1 && n % 6 != 5) return false;

        const auto& base = n < 4759123141ULL ? base_small : base_large;
        const int s = __builtin_ctzll(n - 1);
        const u64 d = n >> s;

        for (const auto& b : base) {
            if (b >= n) break;
            if (check_composite(n, b, d, s)) return false;
        }
        return true;
    }

private:
    const vector<u64> base_small = {2, 7, 61},
                      base_large = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};

    bool check_composite(u64 n, u64 x, u64 d, int s) {
        x = modular::pow(x, d, n);
        if (x == 1 || x == n - 1) return false;
        while (--s) {
            x = modular::mul(x, x, n);
            if (x == n - 1) return false;
        }
        return true;
    };
};