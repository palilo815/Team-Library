/**
 * @author
 *      palilo
 * @brief
 *      calculate the distance of two objects
 *      return types must be `double`
 */
namespace geo::distance {
template <typename T>
double point_line(const point2D<T>& u, const pair<point2D<T>, point2D<T>>& v) {
    return abs(u.cross(v.first, v.second)) / (v.second - v.first).dist();
}
} // namespace geo::distance