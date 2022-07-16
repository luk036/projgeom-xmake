#pragma once

#include "ck_plane.hpp"
#include "pg_object.hpp"

class EllPoint;
class EllLine;

class EllPoint : public PgObject<EllPoint, EllLine> {
  public:
    constexpr explicit EllPoint(std::array<int64_t, 3> coord)
        : PgObject<EllPoint, EllLine>{coord} {}

    constexpr auto perp() const -> EllLine;
};

class EllLine : public PgObject<EllLine, EllPoint> {
  public:
    constexpr explicit EllLine(std::array<int64_t, 3> coord) : PgObject<EllLine, EllPoint>{coord} {}

    constexpr auto perp() const -> EllPoint;
};

inline constexpr auto EllPoint::perp() const -> EllLine { return EllLine{this->coord}; }

inline constexpr auto EllLine::perp() const -> EllPoint { return EllPoint{this->coord}; }

// impl CKPlanePrim<EllLine> for EllPoint {
//     #[inline]
//     fn perp(&self) -> EllLine {
//         EllLine::new(self.coord)
//     }
// }
//
// impl CKPlanePrim<EllPoint> for EllLine {
//     #[inline]
//     fn perp(&self) -> EllPoint {
//         EllPoint::new(self.coord)
//     }
// }
//
// impl CKPlane<EllLine, i128> for EllPoint {}
//
// impl CKPlane<EllPoint, i128> for EllLine {}
