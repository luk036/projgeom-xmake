/*
 *  Distributed under the MIT License (See accompanying file /LICENSE )
 */
#include <doctest/doctest.h>  // for ResultBuilder

#include <ostream>                           // for operator<<

#include "projgeom/common_concepts.h"  // for fun
#include "projgeom/fractions.hpp"      // for Fraction

using namespace fun;

TEST_CASE("undefined behavior") {
    int a = 125;
    int c = 32;
    [[maybe_unused]] int b = a >> c;  // see if your tool can catch the problem
    // std::cout << "125 >> 32 = " << b << "\n";
}

TEST_CASE("Fraction") {
    static_assert(Integral<int>);

    const auto a = int{3};
    const auto b = int{4};
    const auto c = int{5};
    const auto d = int{6};
    const auto f = int{-30};
    const auto g = int{40};
    const auto z = int{0};
    const auto h = int{-g};

    const auto p = Fraction{a, b};
    // std::cout << p << '\n';
    const auto q = Fraction{c, d};

    CHECK(p == Fraction<int>(30, 40));
    CHECK(p + q == Fraction<int>(19, 12));
    CHECK(p - q == Fraction<int>(-1, 12));
    CHECK(p != int(0));
}

TEST_CASE("Fraction Special Cases") {
    const auto p = Fraction{3, 4};
    const auto inf = Fraction{1, 0};
    const auto nan = Fraction{0, 0};
    const auto zero = Fraction{0, 1};

    CHECK(-inf < zero);
    CHECK(zero < inf);
    CHECK(-inf < p);
    CHECK(p < inf);
    CHECK(inf == inf);
    CHECK(-inf < inf);
    CHECK(inf == inf * p);
    CHECK(inf == inf * inf);
    CHECK(inf == p / zero);
    CHECK(inf == inf / zero);
    CHECK(nan == nan);
    CHECK(nan == inf * zero);
    CHECK(nan == -inf * zero);
    CHECK(nan == inf / inf);
    CHECK(nan == nan * zero);
    CHECK(nan == nan * nan);
    CHECK(inf == inf + inf);
    CHECK(nan == inf - inf);
    // CHECK( inf + p == nan ); // ???
    // CHECK( -inf + p == nan ); // ???
}
