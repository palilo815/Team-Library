/**
 * @link  https://github.com/kth-competitive-programming/kactl/blob/main/content/number-theory/FastEratosthenes.h
 * @brief implement Eratosthenes' sieve
 * @note  $O(MAX)$
 */
vector<int> get_primes(int MAX) {
    const int s = round(sqrt(MAX)), r = MAX >> 1;
    vector<int> primes = {2}, sieve(s + 1);
    primes.reserve(MAX / log(MAX) * 1.1);
    vector<pair<int, int>> cp;
    for (int i = 3; i <= s; i += 2) {
        if (!sieve[i]) {
            cp.emplace_back(i, (i * i) >> 1);
            for (int j = i * i; j <= s; j += i << 1) {
                sieve[j] = 1;
            }
        }
    }
    vector<char> block(s);
    for (int l = 1; l <= r; l += s) {
        memset(block.data(), 0, s);
        for (auto& [p, idx] : cp) {
            for (int i = idx; i < s + l; idx = (i += p)) {
                block[i - l] = 1;
            }
        }
        for (int i = 0, j = min(s, r - l); i < j; ++i) {
            if (!block[i]) {
                primes.emplace_back((l + i) << 1 | 1);
            }
        }
    }
    return primes;
}

vector<int> get_factors(int MAX) {
    vector<int> f(MAX), primes;
    primes.reserve(MAX / log(MAX) * 1.1);
    for (int i = 2; i <= MAX; ++i) {
        if (f[i] == 0) {
            f[i] = i;
            primes.emplace_back(i);
        }
        for (const auto& p : primes) {
            if (p > f[i] || i * p > MAX) {
                break;
            }
            f[i * p] = p;
        }
    }
    return f;
}