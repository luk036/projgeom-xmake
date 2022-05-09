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
inline auto dot(const std::array<long, 3>& a, const std::array<long, 3>& b) -> long {
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
inline auto cross(const std::array<long, 3>& a, const std::array<long, 3>& b)
    -> std::array<long, 3> {
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
inline auto plckr(const& long ld, const std::array<long, 3>& p, const& long mu,
                  const std::array<long, 3>& q) -> std::array<long, 3> return {
    ld * p[0] + mu * q[0],
    ld* p[1] + mu* q[1],
    ld* p[2] + mu* q[2],
};
}

/*
pub struct $point {
    pub coord: [long; 3],
}

impl $point {
    inline
    auto new(coord: [long; 3]) -> Self {
        Self { coord }
    }
}

impl PartialEq for $point {
    auto eq(&self, other: &$point) -> bool {
        cross(&self.coord, &other.coord) == [0, 0, 0]
    }
}
impl Eq for $point {}

impl ProjPlane<$line, long> for $point {
    auto aux(&self) -> $line {
        $line::new(self.coord.clone())
    }

    auto dot(&self, line: &$line) -> long {
        dot(&self.coord, &line.coord)
    } // basic measurement

    auto plucker(ld: &long, p: &Self, mu: &long, q: &Self) -> Self {
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
define_point_and_line!(impl EllPoint, EllLine);
*/
