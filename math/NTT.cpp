namespace NTT {
// anonymous namespace
// TODO: make this namespace as private member
namespace {
constexpr int64_t mod = 998244353, root = 62;

int64_t modpow(int64_t b, int64_t e) {
    int64_t r = 1;
    for (; e; e >>= 1) {
        if (e & 1) r = r * b % mod;
        b = b * b % mod;
    }
    return r;
}
}; // namespace

void ntt(vector<int64_t>& a) {
    const int n = a.size(), L = __lg(n);
    static vector<int64_t> rt(2, 1);

    for (static int k = 2, s = 2; k < n; k *= 2, s++) {
        rt.resize(n);
        array<int64_t, 2> z = {1, modpow(root, mod >> s)};
        for (int i = k; i < k << 1; ++i)
            rt[i] = rt[i >> 1] * z[i & 1] % mod;
    }

    vector<int> rev(n);
    for (int i = 0; i < n; ++i)
        rev[i] = (rev[i >> 1] | (i & 1) << L) >> 1;
    for (int i = 0; i < n; ++i)
        if (i < rev[i])
            swap(a[i], a[rev[i]]);

    for (int k = 1; k < n; k <<= 1)
        for (int i = 0; i < n; i += k << 1)
            for (int j = 0; j < k; ++j) {
                auto z = rt[j + k] * a[i + j + k] % mod, &ai = a[i + j];
                a[i + j + k] = ai - z + (z > ai ? mod : 0);
                ai += (ai + z >= mod ? z - mod : z);
            }
}
vector<int64_t> conv(const vector<int64_t>& a, const vector<int64_t>& b) {
    if (a.empty() || b.empty()) return {};
    const int s = a.size() + b.size() - 1,
              n = 1 << (__lg(s) + 1),
              inv = modpow(n, mod - 2);

    vector<int64_t> L(a), R(b), out(n);
    L.resize(n), R.resize(n);

    ntt(L), ntt(R);
    for (int i = 0; i < n; ++i)
        out[-i & (n - 1)] = L[i] * R[i] % mod * inv % mod;
    ntt(out);
    return {out.begin(), out.begin() + s};
}
}; // namespace NTT