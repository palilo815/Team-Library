/**
 * @link
 *      https://github.com/kth-competitive-programming/kactl/blob/main/content/geometry/Point.h
 * @brief
 *      some basic functions and struct `point2D`
 * @warning
 *      integer overflow in `dot`, `cross`, `dist2`
 *      just use `long long`. NOT `int`
 *      choose some proper `EPS` value
 */

/* basics */
namespace geo {
#define EPS 1e-8
template <typename T, enable_if_t<is_integral<T>::value, bool> = true>
int sign(T x) { return (x > 0) - (x < 0); }
template <typename T, enable_if_t<is_floating_point<T>::value, bool> = true>
int sign(T x) { return (x > EPS) - (x < -EPS); }
}; // namespace geo

/* point2D */
namespace geo {
template <typename T>
struct point2D {
    T x, y;
    point2D() = default;
    point2D(T _x, T _y) : x(_x), y(_y) {}
    template <typename U>
    explicit point2D(const point2D<U>& p) : x(p.x), y(p.y) {}

    using P = point2D;

    bool operator<(const P& p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator==(const P& p) const { return tie(x, y) == tie(p.x, p.y); }
    bool operator!=(const P& p) const { return tie(x, y) != tie(p.x, p.y); }

    friend P operator+(const P& a, const P& b) { return P(a.x + b.x, a.y + b.y); }
    friend P operator-(const P& a, const P& b) { return P(a.x - b.x, a.y - b.y); }
    friend P operator*(const P& a, const T& scalar) { return P(a.x * scalar, a.y * scalar); }
    friend P operator*(const T& scalar, const P& a) { return P(scalar * a.x, scalar * a.y); }
    friend P operator/(const P& a, const T& scalar) { return P(a.x / scalar, a.y / scalar); }

    friend ostream& operator<<(ostream& o, const P& p) { return o << '(' << p.x << ", " << p.y << ')'; }
    friend istream& operator>>(istream& i, P& p) { return i >> p.x >> p.y; }

    T dot(const P& p) const { return x * p.x + y * p.y; }
    T cross(const P& p) const { return x * p.y - y * p.x; }
    T cross(const P& a, const P& b) const { return (a - *this).cross(b - *this); }

    T dist2() const { return x * x + y * y; }
    double dist() const { return sqrt(dist2()); }

    P perp_cw() const { return P(y, -x); }
    P perp_ccw() const { return P(-y, x); }

    P unit() const { return *this / dist(); }
    P normal() const { return perp_ccw().unit(); }

    P unit_int() const { return x || y ? *this / gcd(x, y) : *this; }
    P normal_int() const { return perp_ccw().unit_int(); }

    bool same_dir(const P& p) const { return cross(p) == 0 && dot(p) > 0; }
    int side_of(const P& s, const P& e) const {
        if constexpr (is_integral_v<T>) {
            return sign(s.cross(e, *this));
        } else {
            auto res = (e - s).cross(*this - s);
            double l = (e - s).dist() * EPS;
            return (res > l) - (res < -l);
        }
    }

    double angle() const { return atan2(y, x); }
    P rotate(double radian) const {
        return P(x * cos(radian) - y * sin(radian), x * sin(radian) + y * cos(radian));
    }
};
}; // namespace geo