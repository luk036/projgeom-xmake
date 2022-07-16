#pragma once

#include <array>

#include "common_concepts.h"
#include "pg_plane.hpp"

/**
Dot product

Examples:

```cpp
use projgeom_rs::pg_object::dot;
let a = dot(&[1, 2, 3], &[3, 4, 5]);
assert_eq!(a, 26);
```
*/
inline constexpr auto dot(const std::array<int64_t, 3>& a, const std::array<int64_t, 3>& b)
    -> int64_t {
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

/**
Cross product

Examples:

```cpp
use projgeom_rs::pg_object::cross;
let a = cross(&[1, 2, 3], &[3, 4, 5]);
assert_eq!(a, [-2, 4, -2]);
```
*/
inline constexpr auto cross(const std::array<int64_t, 3>& a, const std::array<int64_t, 3>& b)
    -> std::array<int64_t, 3> {
    return {
        a[1] * b[2] - a[2] * b[1],
        a[2] * b[0] - a[0] * b[2],
        a[0] * b[1] - a[1] * b[0],
    };
}

/**
Plucker operation

Examples:

```cpp
use projgeom_rs::pg_object::plckr;
let a = plckr(&1, &[1, 2, 3], &-1, &[3, 4, 5]);
assert_eq!(a, [-2, -2, -2]);
```
*/
inline constexpr auto plckr(const int64_t& ld, const std::array<int64_t, 3>& p, const int64_t& mu,
                            const std::array<int64_t, 3>& q) -> std::array<int64_t, 3> {
    return {
        ld * p[0] + mu * q[0],
        ld * p[1] + mu * q[1],
        ld * p[2] + mu * q[2],
    };
}

template <typename P, typename L> class PgObject {
  public:
    using Dual = L;

    std::array<int64_t, 3> coord;

    constexpr explicit PgObject(std::array<int64_t, 3> coord) : coord{std::move(coord)} {}

    constexpr auto operator==(const P& other) const -> bool {
        if (this == &other) {
            return true;
        }
        return this->coord[1] * other.coord[2] == this->coord[2] * other.coord[1]
               && this->coord[2] * other.coord[0] == this->coord[0] * other.coord[2]
               && this->coord[0] * other.coord[1] == this->coord[1] * other.coord[0];
    }

    constexpr auto aux() const -> L { return L{this->coord}; }

    constexpr auto dot(const L& other) const -> int64_t { return ::dot(this->coord, other.coord); }

    static constexpr auto plucker(const int64_t& ld, const P& p, const int64_t& mu, const P& q)
        -> P {
        return P{::plckr(ld, p.coord, mu, q.coord)};
    }

    constexpr auto incident(const L& other) const -> bool { return this->dot(other) == 0; }

    constexpr auto circ(const P& rhs) const -> L { return L{::cross(this->coord, rhs.coord)}; }
};

class PgPoint;
class PgLine;

class PgPoint : public PgObject<PgPoint, PgLine> {
  public:
    constexpr explicit PgPoint(std::array<int64_t, 3> coord)
        : PgObject<PgPoint, PgLine>{std::move(coord)} {}
};

class PgLine : public PgObject<PgLine, PgPoint> {
    constexpr explicit PgLine(std::array<int64_t, 3> coord)
        : PgObject<PgLine, PgPoint>{std::move(coord)} {}
};

/*
pub struct $point {
    pub coord: [int64_t; 3],
}

impl $point {
    inline
    auto new(coord: [int64_t; 3]) -> Self {
        Self { coord }
    }
}

impl PartialEq for $point {
    auto eq(&self, other: &$point) -> bool {
        cross(&self.coord, &other.coord) == [0, 0, 0]
    }
}
impl Eq for $point {}

impl ProjPlane<$line, int64_t> for $point {
    auto aux(&self) -> $line {
        $line::new(self.coord.clone())
    }

    auto dot(&self, line: &$line) -> int64_t {
        dot(&self.coord, &line.coord)
    } // basic measurement

    auto plucker(ld: &int64_t, p: &Self, mu: &int64_t, q: &Self) -> Self {
        Self::new(plckr(ld, &p.coord, mu, &q.coord))
    }
}

impl ProjPlanePrim<$line> for $point {
    auto incident(&self, _rhs: &$line) -> bool {
        dot(&self.coord, &_rhs.coord) == 0
    }

    auto circ(&self, _rhs: &Self) -> $line {
        $line::new(cross(&self.coord, &_rhs.coord))
    }
}

define_point_or_line!(impl $point);
define_point_or_line!(impl $line);
define_line_for_point!(impl $line, $point);
define_line_for_point!(impl $point, $line);

define_point_and_line!(impl PgPoint, PgLine);
define_point_and_line!(impl HypPoint, HypLine);
define_point_and_line!(impl PgPoint, PgLine);
*/
