/**
 * @author
 *      palilo
 * @brief
 *      get intersection point of the two objects
 * @warning
 *      precision in `sign(cross)`. it can be greater than `EPS`
 * @return
 *      pair(# of intersection points, point)
 *           -1 means infinity
 */
namespace geo::intersection {
template <typename T>
pair<int, point2D<double>> segment_segment(const pair<point2D<T>, point2D<T>>& u, const pair<point2D<T>, point2D<T>>& v) {
    auto oa = v.first.cross(v.second, u.first), ob = v.first.cross(v.second, u.second),
         oc = u.first.cross(u.second, v.first), od = u.first.cross(u.second, v.second);
    if (sign(oa) * sign(ob) < 0 && sign(oc) * sign(od) < 0)
        return {1, (point2D<double>(u.first) * ob - point2D<double>(u.second) * oa) / (ob - oa)};

    vector<point2D<T>> pts;
    if (point_in::segment(u.first, v)) pts.emplace_back(u.first);
    if (point_in::segment(u.second, v)) pts.emplace_back(u.second);
    if (point_in::segment(v.first, u)) pts.emplace_back(v.first);
    if (point_in::segment(v.second, u)) pts.emplace_back(v.second);

    if (pts.empty()) return {0, point2D<double>()};
    if (any_of(pts.begin() + 1, pts.end(), [&](const auto& p) { return sign((p - pts.front()).dist()); }))
        return {-1, point2D<double>()};
    return {1, point2D<double>(pts.front())};
}
}; // namespace geo::intersection