struct pollard_rho : miller_rabin {
    u64 pollard(u64 n) {
        auto f = [&](u64 x) { return modular::mul(x, x, n) + 1; };
        u64 x = 0, y = 0, prd = 2, i = 1, q;
        for (int t = 30; t++ % 40 || gcd(prd, n) == 1; x = f(x), y = f(f(y))) {
            if (x == y) x = ++i, y = f(x);
            if ((q = modular::mul(prd, x > y ? x - y : y - x, n))) prd = q;
        }
        return gcd(prd, n);
    }
    vector<u64> factorize(u64 n) {
        if (n == 1) return {};
        if (is_prime(n)) return {n};

        const u64 x = pollard(n);
        auto l = factorize(x), r = factorize(n / x);

        decltype(l) ret(l.size() + r.size());
        merge(l.begin(), l.end(), r.begin(), r.end(), ret.begin());
        return ret;
    }
};