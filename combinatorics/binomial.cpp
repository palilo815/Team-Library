/**
 * @link    https://github.com/indy256/codelibrary/blob/master/cpp/combinatorics/binomial.cpp
 * 
 * @brief   compute nCk
 * @warning **overflow** maximum value of r can be (n)C(n/2)
 * @note    O(k)
 */
auto binomial = [&](int n, int k) -> int {
    int r = 1;
    for (int i = 0; i < k; ++i)
        r = r * (n - i) / (i + 1);
    return r;
};