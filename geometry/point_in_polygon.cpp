/**
 * @link 
 *      https://vlecomte.github.io/cp-geo.pdf
 * @return
 *      whether point lies inside the polygon
 *      if `strict` is true, points on the boundary aren't included.
 */
template <typename T>
bool in_polygon(vector<point2D<T>>& poly, point2D<T> p, bool strict) {
    int cnt = 0, n = poly.size();
    for (int i = 0; i < n; ++i) {
        auto q = poly[(i + 1) % n];
        if (p.on_segment(poly[i], q)) return !strict;
        cnt ^= ((p.y < poly[i].y) - (p.y < q.y)) * p.cross(poly[i], q) > 0;
    }
    return cnt;
}