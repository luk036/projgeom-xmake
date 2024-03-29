#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <projgeom/ck_plane.hpp>
#include <projgeom/ell_object.hpp>
#include <projgeom/hyp_object.hpp>
#include <projgeom/myck_object.hpp>
#include <projgeom/persp_object.hpp>
#include <projgeom/pg_object.hpp>
#include <projgeom/pg_plane.hpp>

TEST_CASE("it works") {
  auto p = PerspPoint({3, 4, 5});
  auto q = PerspPoint({0, 4, 1});
  auto m = PerspLine({1, 0, 4});
  bool is_ok = fun::check_axiom(p, q, m);
  CHECK(is_ok);
  auto t = fun::altitude(p, m);
  bool res = fun::is_perpendicular(t, m);
  CHECK(res);
}
