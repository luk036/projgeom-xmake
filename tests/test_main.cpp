#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <projgeom/ck_plane.hpp>
#include <projgeom/pg_plane.hpp>
#include <projgeom/pg_object.hpp>
#include <projgeom/ell_object.hpp>
#include <projgeom/hyp_object.hpp>

TEST_CASE("it works") {
    auto p = HypPoint({3, 4, 5});
    CHECK(p == p);
}
