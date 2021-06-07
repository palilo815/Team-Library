template <typename T>
int extr_vertex(const vector<point2D<T>>& poly, const point2D<T>& dir) {
    int n = poly.size(), lo = 0, hi = n;
    auto cmp = [&](int i, int j) {
        auto r = dir.perp_ccw().cross(poly[i % n] - poly[j % n]);
        return (r > 0) - (r < 0);
    };
    auto extr = [&](int i) {
        return cmp(i + 1, i) >= 0 && cmp(i, i - 1 + n) < 0;
    };
    if (extr(0)) return 0;

    while (lo + 1 < hi) {
        int m = (lo + hi) / 2;
        if (extr(m)) return m;
        int ls = cmp(lo + 1, lo), ms = cmp(m + 1, m);
        (ls < ms || (ls == ms && ls == cmp(lo, m)) ? hi : lo) = m;
    }
    return lo;
}

template <typename T>
array<int, 2> line_hull(const point2D<T>& a, const point2D<T>& b, const vector<point2D<T>>& poly) {
    int endA = extr_vertex(poly, (a - b).perp_ccw());
    int endB = extr_vertex(poly, (b - a).perp_ccw());
    auto cmp = [&](int i) {
        auto r = a.cross(poly[i], b);
        return (r > 0) - (r < 0);
    };
    if (cmp(endA) < 0 || cmp(endB) > 0) return {-1, -1};

    array<int, 2> res;
    for (auto& r : res) {
        int lo = endB, hi = endA, n = poly.size();
        while ((lo + 1) % n != hi) {
            int m = ((lo + hi + (lo < hi ? 0 : n)) / 2) % n;
            (cmp(m) == cmp(endB) ? lo : hi) = m;
        }
        r = (lo + !cmp(hi)) % n;
        swap(endA, endB);
    }

    if (res[0] == res[1]) return {res[0], -1};
    if (!cmp(res[0]) && !cmp(res[1]))
        switch ((res[0] - res[1] + poly.size() + 1) % poly.size()) {
        case 0: return {res[0], res[0]};
        case 2: return {res[1], res[1]};
        }
    return res;
}