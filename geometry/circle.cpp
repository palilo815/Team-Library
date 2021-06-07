/**
 * @link
 *      https://github.com/kth-competitive-programming/kactl/blob/main/content/geometry/circumcircle.h
 * @return
 *      (radius / centre) of the circle going through points A, B and C
 */
template <class P = point2D<double>>
double circle_radius(const P& A, const P& B, const P& C) {
    return (B - A).dist() * (C - B).dist() * (A - C).dist() / Abs((B - A).cross(C - A)) / 2;
}
template <class P = point2D<double>>
point2D<double> circle_centre(const P& A, const P& B, const P& C) {
    auto b = C - A, c = B - A;
    return A + (b * c.dist2() - c * b.dist2()).perp_ccw() / b.cross(c) / 2;
}