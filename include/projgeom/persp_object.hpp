#pragma once

#include "ck_plane.hpp"
#include "pg_object.hpp"

class PerspPoint;
class PerspLine;

class PerspPoint : public PgObject<PerspPoint, PerspLine> {
  public:
    // constexpr static PerspLine L_INF{ {0, -1, 1}};

    constexpr explicit PerspPoint(std::array<int64_t, 3> coord)
        : PgObject<PerspPoint, PerspLine>{coord} {}

    constexpr auto perp() const -> const PerspLine&;
};

class PerspLine : public PgObject<PerspLine, PerspPoint> {
  public:
    // constexpr static PerspPoint I_RE{ {0, 1, 1}};
    // constexpr static PerspPoint I_IM{ {1, 0, 0}};

    constexpr explicit PerspLine(std::array<int64_t, 3> coord)
        : PgObject<PerspLine, PerspPoint>{coord} {}

    constexpr auto perp() const -> PerspPoint;
};

static constexpr PerspLine L_INF({0, -1, 1});
static constexpr PerspPoint I_RE({0, 1, 1});
static constexpr PerspPoint I_IM({1, 0, 0});

inline constexpr auto PerspPoint::perp() const -> const PerspLine& { return L_INF; }

inline constexpr auto PerspLine::perp() const -> PerspPoint {
    const auto alpha = this->dot(I_RE);  // ???
    const auto beta = this->dot(I_IM);   // ???
    return PerspPoint::plucker(alpha, I_RE, beta, I_IM);
}
