#pragma once

#include "ck_plane.hpp"
#include "pg_object.hpp"

class HypPoint;
class HypLine;

class HypPoint : public PgObject<HypPoint, HypLine> {
  public:
    constexpr explicit HypPoint(std::array<int64_t, 3> coord)
        : PgObject<HypPoint, HypLine>{coord} {}
         
    constexpr auto perp() const -> HypLine;
}; 

class HypLine : public PgObject<HypLine, HypPoint> {
  public:
    constexpr explicit HypLine(std::array<int64_t, 3> coord)
        : PgObject<HypLine, HypPoint>{coord} {}
         
    constexpr auto perp() const -> HypPoint;
}; 

inline constexpr auto HypPoint::perp() const -> HypLine {
    return HypLine({this->coord[0], this->coord[1], -this->coord[2]});
}

inline constexpr auto HypLine::perp() const -> HypPoint {
    return HypPoint({this->coord[0], this->coord[1], -this->coord[2]});
}
