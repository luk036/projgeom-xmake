#pragma once

#include <array>

#include "pg_plane.hpp"

namespace fun {
/**
 * @brief C-K plane Concept
 *
 * @tparam P Point
 * @tparam L Line
 */
template <class P, class L = typename P::Dual>
concept CKPlanePrim =   //
    ProjPlanePrim<P, L> //
    && requires(const P &p, const L &l) {
         { p.perp() } -> concepts::convertible_to<L>;
       };

/**
 * @brief C-K plane Concept (full)
 *
 * @tparam P Point
 * @tparam L Line
 */
template <class P, class L = typename P::Dual>
concept CKPlanePrimDual = CKPlanePrim<P, L> && CKPlanePrim<L, P>;

/**
 * @brief
 *
 * @tparam P Point
 * @tparam L Line
 */
template <class L, class P = typename L::Dual>
  requires CKPlanePrimDual<L, P>
constexpr auto is_perpendicular(const L &m1, const L &m2) -> bool {
  return m1.perp().incident(m2);
}

/**
 * @brief
 *
 * @tparam P Point
 * @tparam L Line
 */
template <class P, class L>
  requires CKPlanePrimDual<P, L>
constexpr auto altitude(const P &p, const L &m) -> L {
  return m.perp().circ(p);
}

/**
 * @brief
 *
 * @param[in] tri
 * @return std::arrary<L, 3>
 */
template <class P>
  requires CKPlanePrimDual<P>
constexpr auto orthocenter(const std::array<P, 3> &tri) -> P {
  const auto &[a1, a2, a3] = tri;
  assert(!coincident(a1, a2, a3));
  const auto t1 = altitude(a1, a2.circ(a3));
  const auto t2 = altitude(a2, a3.circ(a1));
  return t1.circ(t2);
  // return {a2.circ(a3), a1.circ(a3), a1.circ(a2)};
}

/**
 * @brief
 *
 * @param[in] tri
 * @return std::arrary<L, 3>
 */
template <class P, class L>
  requires CKPlanePrimDual<P, L>
constexpr auto tri_altitude(const std::array<P, 3> &tri) -> std::array<L, 3> {
  const auto [l1, l2, l3] = tri_dual(tri);
  const auto &[a1, a2, a3] = tri;
  assert(!coincident(a1, a2, a3));
  auto &&t1 = altitude(a1, l1);
  auto &&t2 = altitude(a2, l2);
  auto &&t3 = altitude(a3, l3);
  return {t1, t2, t3};
}

/**
 * @brief C-K plane Concept
 *
 * @tparam P Point
 * @tparam L Line
 */
template <typename V, class P, class L = typename P::Dual>
concept CKPlane = ProjPlane<V, P, L> && CKPlanePrim<P, L>;

/**
 * @brief C-K plane dual Concept
 *
 * @tparam P Point
 * @tparam L Line
 */
template <typename V, class P, class L = typename P::Dual>
concept CKPlaneDual = CKPlane<V, P, L> && CKPlane<L, P, V>;

template <typename V, class P, class L = typename P::Dual>
  requires CKPlaneDual<V, P, L>
constexpr auto reflect(const P &origin, const L &mirror, const P &p) -> P {
  return involution(mirror.perp(), mirror, p);
}

/*
axiom(P p, P q, P r, L l) {
  l == L{p, q} => I(p, l) and I(q, l);
}
*/

} // namespace fun
