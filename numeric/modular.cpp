/**
 * @brief modular arithmetics
 * @link https://github.com/kth-competitive-programming/kactl 
 */
namespace modular {
using i64 = int64_t;
using u64 = uint64_t;

/**
 * @note $O(1)$
 * @return $(a * b) \mod m$
 */
u64 mul(u64 a, u64 b, u64 m) {
    i64 ret = a * b - m * u64(1.L / m * a * b);
    return ret + m * (ret < 0) - m * (ret >= i64(m));
}

/**
 * @note $O(log p)$
 * @return $(a^p) \mod m$
 */
u64 pow(u64 a, u64 p, u64 m) {
    u64 ret = 1;
    for (; p; p >>= 1) {
        if (p & 1) ret = mul(ret, a, m);
        a = mul(a, a, m);
    }
    return ret;
}

/**
 * @note $O(1)$
 * @return $0 + 1 + 2 + \dots + (r - 1)$
 */
u64 sumsq(u64 r) {
    return r / 2 * ((r - 1) | 1);
};

/**
 * @note $O(1)$
 * @return $\sum_{i = 0}^{r - 1}{\lfloor \frac{ai + b}{m} \rfloor}$
 */
u64 divsum(u64 r, u64 a, u64 b, u64 m) {
    u64 res = a / m * sumsq(r) + b / m * r;
    a %= m, b %= m;
    if (!a) return res;
    u64 r2 = (r * a + b) / m;
    return res + (r - 1) * r2 - divsum(r2, m, m - 1 - b, a);
};

/**
 * @note $O(1)$
 * @return $\sum_{i = 0}^{r - 1}{(ai + b) \% m}$
 */
u64 modsum(u64 r, u64 a, u64 b, u64 m) {
    b = ((b % m) + m) % m;
    a = ((a % m) + m) % m;
    return r * b + a * sumsq(r) - m * divsum(r, a, b, m);
};

/**
 * @note $O(\log^2 p)$ in worst case, $O(\log p)$ for most $p$
 * @return $x$ s.t. $x^2 = a \mod p$
 *         if (a is 0) or (no solution) return 0
 */
i64 sqrt(i64 a, i64 p) {
    a %= p;
    if (a < 0) a += p;

    if (a == 0 || pow(a, (p - 1) / 2, p) != 1) return 0;
    if (p % 4 == 3) return pow(a, (p + 1) / 4, p);

    i64 s = p - 1, n = 2;
    int r = __builtin_ctzll(s);
    s >>= r;

    while (pow(n, (p - 1) / 2, p) != p - 1) ++n;
    i64 x = pow(a, (s + 1) / 2, p);
    i64 b = pow(a, s, p), g = pow(n, s, p);
    for (int m;; r = m) {
        i64 t = b;
        for (m = 0; m < r && t != 1; ++m)
            t = t * t % p;
        if (m == 0) return x;
        i64 gs = pow(g, 1LL << (r - m - 1), p);
        g = gs * gs % p;
        x = x * gs % p;
        b = b * g % p;
    }
}
} // namespace modular