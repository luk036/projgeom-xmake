#pragma once

#include "ck_plane.hpp"
#include "pg_object.hpp"

class MyCKPoint;
class MyCKLine;

class MyCKPoint : public PgObject<MyCKPoint, MyCKLine> {
  public:
    constexpr explicit MyCKPoint(std::array<int64_t, 3> coord)
        : PgObject<MyCKPoint, MyCKLine>{coord} {}

    constexpr auto perp() const -> MyCKLine;
};

class MyCKLine : public PgObject<MyCKLine, MyCKPoint> {
  public:
    constexpr explicit MyCKLine(std::array<int64_t, 3> coord)
        : PgObject<MyCKLine, MyCKPoint>{coord} {}

    constexpr auto perp() const -> MyCKPoint;
};

inline constexpr auto MyCKPoint::perp() const -> MyCKLine {
    return MyCKLine({-2 * this->coord[0], this->coord[1], -2 * this->coord[2]});
}

inline constexpr auto MyCKLine::perp() const -> MyCKPoint {
    return MyCKPoint({-this->coord[0], 2 * this->coord[1], -this->coord[2]});
}
