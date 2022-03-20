/*
 *  Distributed under the MIT License (See accompanying file /LICENSE )
 */
#include <doctest/doctest.h>  // for ResultBuilder

#include <array>                             // for operator==
#include <boost/multiprecision/cpp_int.hpp>  // for cpp_int
#include <ostream>                           // for operator<<
#include <tuple>                             // for get, tuple
#include <type_traits>                       // for move

#include "projgeom/ck_plane.hpp"       // for ellck, hyck
#include "projgeom/common_concepts.h"  // for Value_type
#include "projgeom/fractions.hpp"      // for operator*
#include "projgeom/pg_common.hpp"      // for cross
#include "projgeom/pg_line.hpp"        // for pg_line
#include "projgeom/pg_object.hpp"      // for operator*
#include "projgeom/pg_point.hpp"       // for pg_point
#include "projgeom/proj_plane.hpp"     // for tri_dual
// #include <iostream>

using namespace fun;

static const auto Zero = doctest::Approx(0).epsilon(0.01);

/**
 * @brief
 *
 * @param[in] a
 * @return true
 * @return false
 */
template <typename T> inline auto ApproxZero(const T& a) -> bool {
    return a[0] == Zero && a[1] == Zero && a[2] == Zero;
}

/**
 * @brief
 *
 * @tparam PG
 * @param[in] myck
 */
template <typename PG> void chk_tri(const PG& myck) {
    using Point = typename PG::point_t;
    using K = Value_type<Point>;

    auto a1 = Point{1, 3, 1};
    auto a2 = Point{4, 2, 1};
    auto a3 = Point{1, 1, -1};
    auto a4 = plucker(2, a1, 3, a2);

    const auto triangle = std::array{std::move(a1), std::move(a2), std::move(a3)};
    const auto trilateral = tri_dual(triangle);
    const auto& [l1, l2, l3] = trilateral;

    const auto Q = myck.tri_quadrance(triangle);
    const auto S = myck.tri_spread(trilateral);

    if constexpr (Integral<K>) {
        CHECK(myck.perp(myck.perp(a4)) == a4);
        CHECK(myck.perp(myck.perp(l1)) == l1);
        CHECK(myck.perp(myck.perp(l2)) == l2);
        CHECK(myck.perp(myck.perp(l3)) == l3);
        // CHECK(check_cross_law(S, std::get<2>(Q)) == K(0));
        // CHECK(check_cross_law(Q, std::get<2>(S)) == K(0));
    } else {
        CHECK(ApproxZero(cross(myck.perp(myck.perp(a4)), a4)));
        CHECK(ApproxZero(cross(myck.perp(myck.perp(l1)), l1)));
        CHECK(ApproxZero(cross(myck.perp(myck.perp(l2)), l2)));
        CHECK(ApproxZero(cross(myck.perp(myck.perp(l3)), l3)));
        CHECK(check_cross_law(S, std::get<2>(Q)) == Zero);
        CHECK(check_cross_law(Q, std::get<2>(S)) == Zero);
    }
}

/**
 * @brief
 *
 * @tparam PG
 * @param[in] myck
 */
template <typename PG> void chk_tri2(const PG& myck) {
    using Point = typename PG::point_t;
    using K = Value_type<Point>;

    auto a1 = Point{1, 3, 1};
    auto a2 = Point{4, 2, 1};
    auto a4 = plucker(2, a1, 3, a2);

    const auto collin = std::array{std::move(a1), std::move(a2), std::move(a4)};
    const auto Q2 = myck.tri_quadrance(collin);

    if constexpr (Integral<K>) {
        CHECK(check_cross_TQF(Q2) == 0);
    } else {
        CHECK(check_cross_TQF(Q2) == Zero);
    }
}

TEST_CASE("Elliptic/Hyperbolic plane") {
    using boost::multiprecision::cpp_int;

    chk_tri(ellck<pg_point<cpp_int>>());
    chk_tri(ellck<pg_line<cpp_int>>());
    chk_tri(hyck<pg_point<cpp_int>>());
    chk_tri(hyck<pg_line<cpp_int>>());

    chk_tri2(ellck<pg_point<cpp_int>>());
    chk_tri2(ellck<pg_line<cpp_int>>());
    chk_tri2(hyck<pg_point<cpp_int>>());
    chk_tri2(hyck<pg_line<cpp_int>>());
}

TEST_CASE("Elliptic/Hyperbolic plane (double)") {
    chk_tri(ellck<pg_point<double>>());
    chk_tri(ellck<pg_line<double>>());
    chk_tri(hyck<pg_point<double>>());
    chk_tri(hyck<pg_line<double>>());

    chk_tri2(ellck<pg_point<double>>());
    chk_tri2(ellck<pg_line<double>>());
    chk_tri2(hyck<pg_point<double>>());
    chk_tri2(hyck<pg_line<double>>());
}
