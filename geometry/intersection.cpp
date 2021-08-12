/**
 * @author  palilo
 * @brief   get intersection point of the two objects
 * @warning precision in `sign(cross)`. it can be greater than `EPS`
 *          `line_line`: it is assumed they're MUST be intersected
 * @return  intersection point
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

template <typename T>
point2D<double> line_line(const pair<point2D<T>, point2D<T>>& u, const pair<point2D<T>, point2D<T>>& v) {
    return (u.first * v.first.cross(u.second, v.second) + u.second * v.first.cross(v.second, u.first)) /
           (u.second - u.first).cross(v.second - v.first);
}
}; // namespace geo::intersection