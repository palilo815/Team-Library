/**
 * @brief
 *      calculate the distance^2 of two objects
 *      return types may be various
 */
namespace geo::distance2 {
/**
 * @link 
 *      https://codeforces.com/blog/entry/48868
 * @warning
 *      ccw, no duplicate/collinear points
 * @return
 *      maximum distance of two points on the convex hull
 */
template <typename T>
T hull_diameter(const vector<point2D<T>>& hull) {
    T diameter = 0;
    int n = hull.size();
    for (int i = 0, j = n > 1; i < j; ++i) {
        for (;; j = j == n - 1 ? 0 : j + 1) {
            chmax(diameter, (hull[i] - hull[j]).dist2());
            if ((hull[(j + 1) % n] - hull[j]).cross(hull[i + 1] - hull[i]) >= 0)
                break;
        }
    }
    return diameter;
}
}; // namespace geo::distance2