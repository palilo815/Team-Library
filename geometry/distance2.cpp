/**
 * @brief calculate the distance^2 of two objects
 *        return types may be various
 */
namespace geo::distance2 {
/**
 * @link    https://codeforces.com/blog/entry/48868
 * @brief   rotating calipers
 * @return  maximum distance of two points on the convex hull
 * @warning ccw order, no duplicate/collinear points
 */
template <typename T>
T hull_diameter(const vector<point2D<T>>& hull) {
    if (hull.size() < 2) return 0;
    T diameter = 0;
    const size_t n = hull.size();
    for (size_t i = 0, j = 1, j2; i < j; ++i) {
        for (;; j = j2) {
            j2 = j == n - 1 ? 0 : j + 1;
            chmax(diameter, (hull[i] - hull[j]).dist2());
            if ((hull[j2] - hull[j]).cross(hull[i + 1] - hull[i]) >= 0) {
                break;
            }
        }
    }
    return diameter;
}
}; // namespace geo::distance2