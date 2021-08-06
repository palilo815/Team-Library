struct hash_t {
    uint64_t x;
    hash_t() = default;
    hash_t(uint64_t x) : x(x) {}
#define OP(O, A, B)                         \
    hash_t operator O(hash_t o) {           \
        uint64_t r = x;                     \
        asm(A "addq %%rdx, %0\n adcq $0,%0" \
            : "+a"(r)                       \
            : B);                           \
        return r;                           \
    }
    OP(+, , "d"(o.x))
    OP(*, "mul %1\n", "r"(o.x)
        : "rdx")
    hash_t operator-(const hash_t& o) { return *this + ~o.x; }
    uint64_t get() const { return x + !~x; }
    bool operator==(const hash_t& o) const { return get() == o.get(); }
    bool operator<(const hash_t& o) const { return get() < o.get(); }
};

static const hash_t C = 1e11 + 3;

struct hash_interval {
    vector<hash_t> h, pw;
    hash_interval(string& str) : h(str.size() + 1), pw(h) {
        pw[0] = 1;
        for (int i = 0; i < int(str.size()); ++i) {
            h[i + 1] = h[i] * C + str[i];
            pw[i + 1] = pw[i] * C;
        }
    }
    // hash [st, ed)
    hash_t get_hash(int st, int ed) {
        return h[ed] - h[st] * pw[ed - st];
    }
};

vector<hash_t> hash_substrs(string& str, int length) {
    if (int(str.size()) < length) return {};
    hash_t h = 0, pw = 1;
    for (int i = 0; i < length; ++i) {
        h = h * C + str[i];
        pw = pw * C;
    }
    vector<hash_t> ret;
    ret.reserve(int(str.size()) - length + 1);
    ret.emplace_back(h);
    for (int i = length; i < int(str.size()); ++i) {
        h = h * C + str[i] - pw * str[i - length];
        ret.emplace_back(h);
    }
    return ret;
}

hash_t hash_str(const string& s) {
    hash_t h = 0;
    for (const auto& c : s) {
        h = h * C + c;
    }
    return h;
}