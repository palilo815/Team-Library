/**
 * @link
 *      https://github.com/kth-competitive-programming/kactl/blob/main/content/number-theory/FastEratosthenes.h
 *
 * @brief 
 *      faster Eratosthenes' sieve !!!!
 *      
 *      two methods to check x is prime
 *          1. is_prime[x] = true
 *          2. x in primes
 */
template <int MAX>
class eratosthenes {
public:
    bitset<MAX> is_prime;
    vector<int> get_primes() {
        const int s = round(sqrt(MAX)), r = MAX >> 1;

        vector<int> primes = {2}, sieve(s + 1);
        primes.reserve(MAX / log(MAX) * 1.1);

        vector<pair<int, int>> cp;
        for (int i = 3; i <= s; i += 2)
            if (!sieve[i]) {
                cp.emplace_back(i, (i * i) >> 1);
                for (int j = i * i; j <= s; j += i << 1)
                    sieve[j] = 1;
            }

        for (int l = 1; l <= r; l += s) {
            array<bool, s> block {};
            for (auto& [p, idx] : cp)
                for (int i = idx; i < s + l; idx = (i += p))
                    block[i - l] = 1;

            for (int i = 0, j = min(s, r - l); i < j; ++i)
                if (!block[i])
                    primes.emplace_back((l + i) << 1 | 1);
        }

        for (const auto& i : primes)
            is_prime[i] = true;
        return primes;
    }
};