/**
 * @link 
 *      https://github.com/kth-competitive-programming/kactl/blob/master/content/numerical/FastFourierTransform.h
 */
namespace FFT {
constexpr long double PI = acos(-1.0L);
void fft(vector<complex<double>>& a) {
    const int n = a.size(), L = __lg(n);
    static vector<complex<long double>> R(2, 1);
    static vector<complex<double>> rt(2, 1);

    for (static int k = 2; k < n; k <<= 1) {
        R.resize(n), rt.resize(n);
        const auto x = polar(1.0L, PI / k);
        for (int i = k; i < k << 1; ++i)
            rt[i] = R[i] = i & 1 ? R[i >> 1] * x : R[i >> 1];
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
                const auto z = rt[j + k] * a[i + j + k];
                a[i + j + k] = a[i + j] - z;
                a[i + j] += z;
            }
}
vector<int64_t> conv(const vector<int64_t>& a, const vector<int64_t>& b) {
    if (a.empty() || b.empty()) return {};
    vector<int64_t> res(a.size() + b.size() - 1);
    const int n = 1 << (__lg(res.size()) + 1);

    vector<complex<double>> in(n);
    copy(a.begin(), a.end(), in.begin());
    for (int i = 0; i < int(b.size()); ++i)
        in[i].imag(b[i]);

    fft(in);
    for (auto& x : in) x *= x;

    vector<complex<double>> out(n);
    for (int i = 0; i < n; ++i)
        out[i] = in[-i & (n - 1)] - conj(in[i]);

    fft(out);
    for (int i = 0; i < int(res.size()); ++i)
        res[i] = llround(imag(out[i])) / (n << 2);
    return res;
}
template <int mod>
vector<int64_t> conv_mod(const vector<int64_t>& a, const vector<int64_t>& b) {
    if (a.empty() || b.empty()) return {};
    vector<int64_t> res(a.size() + b.size() - 1);
    const int n = 1 << (__lg(res.size()) + 1), cut = sqrt(mod);

    vector<complex<double>> L(n), R(n), outs(n), outl(n);
    for (int i = 0; i < int(a.size()); ++i)
        L[i] = complex<double>(int(a[i]) / cut, int(a[i]) % cut);
    for (int i = 0; i < int(b.size()); ++i)
        R[i] = complex<double>(int(b[i]) / cut, int(b[i]) % cut);

    fft(L), fft(R);
    for (int i = 0; i < n; ++i) {
        int j = -i & (n - 1);
        outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
        outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
    }

    fft(outl), fft(outs);
    for (int i = 0; i < int(res.size()); ++i) {
        int64_t av = int64_t(real(outl[i]) + .5), cv = int64_t(imag(outs[i]) + .5);
        int64_t bv = int64_t(imag(outl[i]) + .5) + int64_t(real(outs[i]) + .5);
        res[i] = ((av % mod * cut + bv) % mod * cut + cv) % mod;
    }
    return res;
}
}; // namespace FFT
