/**
 * @link 
 *      https://github.com/ngthanhtrung23/ACM_Notebook_new
 * @warning
 *      ccw, no collinear points
 * @return
 *      whether point lies inside the convex hull
 *      if `strict` is true, points on the boundary aren't included.
 */
template <typename T>
bool in_hull(const vector<point2D<T>>& hull, point2D<T> p, bool strict) {
    int a = 1, b = hull.size() - 1, r = !strict;
    if (hull.size() < 3) return r && p.on_segment(hull[0], hull.back());
    if (hull[b].side_of(hull[0], hull[a]) > 0) swap(a, b);
    if (p.side_of(hull[0], hull[a]) >= r || p.side_of(hull[0], hull[b]) <= -r) return false;

    while (abs(a - b) > 1) {
        int c = (a + b) / 2;
        (p.side_of(hull[0], hull[c]) > 0 ? b : a) = c;
    }

    auto c = hull[a].cross(hull[b], p);
    return ((c > 0) - (c < 0)) < r;
}