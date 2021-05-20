template <typename T>
struct point {
    T x, y;
    point() = default;
    point(T _x, T _y) : x(_x), y(_y) {}

    friend ostream& operator<<(ostream& o, const point& p) { return o << '(' << p.x << ',' << p.y << ')'; }
    friend istream& operator>>(istream& i, point& p) { return i >> p.x >> p.y; }

    friend bool operator==(const point& a, const point& b) { return a.x == b.x && a.y == b.y; }
    friend bool operator!=(const point& a, const point& b) { return a.x != b.x || a.y != b.y; }

    point operator+() const { return point(+x, +y); }
    point operator-() const { return point(-x, -y); }

    point& operator+=(const point& p) {
        x += p.x, y += p.y;
        return *this;
    }
    point& operator-=(const point& p) {
        x -= p.x, y -= p.y;
        return *this;
    }
    point& operator*=(const T& t) {
        x *= t, y *= t;
        return *this;
    }
    point& operator/=(const T& t) {
        x /= t, y /= t;
        return *this;
    }

    friend point operator+(const point& a, const point& b) { return point(a.x + b.x, a.y + b.y); }
    friend point operator-(const point& a, const point& b) { return point(a.x - b.x, a.y - b.y); }
    friend point operator*(const point& a, const T& t) { return point(a.x * t, a.y * t); }
    friend point operator*(const T& t, const point& a) { return point(t * a.x, t * a.y); }
    friend point operator/(const point& a, const T& t) { return point(a.x / t, a.y / t); }

    T dist2() const { return x * x + y * y; }
    auto dist() const { return sqrt(dist2()); }
    point unit() const { return *this / dist(); }
    auto angle() const { return atan2(y, x); }

    T int_norm() const { return gcd(x, y); }
    point int_unit() const {
        if (!x && !y) return *this;
        return *this / int_norm();
    }

    // Convenient free-functions, mostly for generic interop
    friend auto norm(const point& a) { return a.dist2(); }
    friend auto abs(const point& a) { return a.dist(); }
    friend auto unit(const point& a) { return a.unit(); }
    friend auto arg(const point& a) { return a.angle(); }
    friend auto int_norm(const point& a) { return a.int_norm(); }
    friend auto int_unit(const point& a) { return a.int_unit(); }

    point perp_cw() const { return point(y, -x); }
    point perp_ccw() const { return point(-y, x); }

    friend T dot(const point& a, const point& b) { return a.x * b.x + a.y * b.y; }
    friend T cross(const point& a, const point& b) { return a.x * b.y - a.y * b.x; }
    friend T cross3(const point& a, const point& b, const point& c) { return cross(b - a, c - a); }

    // Complex numbers and rotation
    friend point conj(const point& a) { return point(a.x, -a.y); }

    // Returns conj(a) * b
    friend point dot_cross(const point& a, const point& b) { return point(dot(a, b), cross(a, b)); }
    friend point cmul(const point& a, const point& b) { return dot_cross(conj(a), b); }
    friend point cdiv(const point& a, const point& b) { return dot_cross(b, a) / b.norm(); }

    // Must be a unit vector; otherwise multiplies the result by abs(u)
    point rotate(const point& u) const { return dot_cross(conj(u), *this); }
    point unrotate(const point& u) const { return dot_cross(u, *this); }

    friend bool same_dir(const point& a, const point& b) { return cross(a, b) == 0 && dot(a, b) > 0; }

    // check if 180 <= s..t < 360
    friend bool is_reflex(const point& a, const point& b) {
        auto c = cross(a, b);
        return c ? (c < 0) : (dot(a, b) < 0);
    }

    // operator < (s,t) for angles in [base,base+2pi)
    friend bool angle_less(const point& base, const point& s, const point& t) {
        int r = is_reflex(base, s) - is_reflex(base, t);
        return r ? (r < 0) : (0 < cross(s, t));
    }

    friend auto angle_cmp(const point& base) {
        return [base](const point& s, const point& t) { return angle_less(base, s, t); };
    }
    friend auto angle_cmp_center(const point& center, const point& dir) {
        return [center, dir](const point& s, const point& t) -> bool { return angle_less(dir, s - center, t - center); };
    }

    // is p in [s,t] taken ccw? 1/0/-1 for in/border/out
    friend int angle_between(const point& s, const point& t, const point& p) {
        if (same_dir(p, s) || same_dir(p, t)) return 0;
        return angle_less(s, p, t) ? 1 : -1;
    }
};