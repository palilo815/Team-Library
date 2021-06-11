/**
 * @link 
 *      https://github.com/stjepang/snippets/blob/master/convex_hull.cpp
 * @warning
 *      points on the edge of the hull will be ignored
 * @return
 *      points of the hull in ccw order
 */
namespace geo {
template <typename T>
vector<point2D<T>> convex_hull(vector<point2D<T>> pts) {
    if (pts.size() <= 1) return pts;
    sort(pts.begin(), pts.end());
    vector<point2D<T>> hull(pts.size() + 1);
    int s = 0, t = 0;
    for (int it = 2; it--; s = --t, reverse(pts.begin(), pts.end()))
        for (const auto& p : pts) {
            while (t >= s + 2 && hull[t - 2].cross(hull[t - 1], p) <= 0) t--;
            hull[t++] = p;
        }
    return {hull.begin(), hull.begin() + t - (t == 2 && hull[0] == hull[1])};
}
}; // namespace geo