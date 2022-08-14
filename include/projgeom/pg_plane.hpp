#pragma once

#include <array>
#include <cassert>

#include "common_concepts.h"

namespace fun {
    /**
     * @brief Projective plane Concept
     *
     * @tparam P Point
     * @tparam L Line
     */
    template <class P, class L>
    concept ProjPlanePrim
        // = STD_ALT::equality_comparable<P> && requires(const P& p, const P& q, const L& l) {
        = requires(const P& p, const P& q, const L& l) {
        { p.incident(l) } -> STD_ALT::convertible_to<bool>;  // incidence
        { p.circ(q) } -> STD_ALT::convertible_to<L>;         // join or meet
    };

    /**
     * @brief Projective plane Concept (full)
     *
     * @tparam P Point
     * @tparam L Line
     */
    template <class P, class L>
    concept ProjPlanePrimDual = ProjPlanePrim<P, L> && ProjPlanePrim<L, P>;

    /**
     * @brief Check Projective plane Axiom
     *
     * @tparam P Point
     * @tparam L Line
     * @param[in] p
     * @param[in] q
     * @param[in] l
     */
    template <class P, class L>
    requires ProjPlanePrimDual<P, L>
    inline auto check_axiom(const P& p, const P& q, const L& l) -> void {
        assert(p == p);
        assert((p == q) == (q == p));
        assert(p.incident(l) == l.incident(p));
        assert(p.circ(q) == q.circ(p));
        const auto m = p.circ(q);
        assert(m.incident(p) && m.incident(q));
    }

    /**
     * @brief Coincident
     *
     * @tparam P
     * @param[in] p
     * @param[in] q
     * @param[in] r
     * @return true
     * @return false
     */
    template <class P, class L = typename P::Dual>
    requires ProjPlanePrimDual<P, L>
    inline constexpr auto coincident(const P& p, const P& q, const P& r) -> bool {
        return p.circ(q).incident(r);
    }

    /**
     * @brief Check Pappus Theorem
     *
     * @tparam P Point
     * @param[in] co1
     * @param[in] co2
     * @return true
     * @return false
     */
    template <class P, class L = typename P::Dual>
    requires ProjPlanePrimDual<P, L>
    inline constexpr auto check_pappus(const std::array<P, 3>& co1, const std::array<P, 3>& co2)
        -> bool {
        const auto& [a, b, c] = co1;
        const auto& [d, e, f] = co2;
        const auto g = (a.circ(e)).circ(b.circ(d));
        const auto h = (a.circ(f)).circ(c.circ(d));
        const auto i = (b.circ(f)).circ(c.circ(e));
        return coincident(g, h, i);
    }

    /**
     * @brief Dual of triangle
     *
     * @tparam P Point
     * @tparam L Line
     * @param[in] tri
     * @return std::array<L, 3>
     */
    template <class P, class L = typename P::Dual>
    requires ProjPlanePrimDual<P, L>
    inline constexpr auto tri_dual(const std::array<P, 3>& tri) -> std::array<L, 3> {
        const auto& [a1, a2, a3] = tri;
        assert(!coincident(a1, a2, a3));
        return {a2.circ(a3), a1.circ(a3), a1.circ(a2)};
    }

    /**
     * @brief return whether two triangles are perspective
     *
     * @tparam P Point
     * @param[in] tri1
     * @param[in] tri2
     * @return true
     * @return false
     */
    template <class P, class L = typename P::Dual>
    requires ProjPlanePrimDual<P, L>
    inline constexpr auto persp(const std::array<P, 3>& tri1, const std::array<P, 3>& tri2)
        -> bool {
        const auto& [a, b, c] = tri1;
        const auto& [d, e, f] = tri2;
        const auto& o = a.circ(d).circ(b.circ(e));
        return c.circ(f).incident(o);
    }

    /**
     * @brief Check Desargue's Theorem
     *
     * @tparam P Point
     * @param[in] tri1
     * @param[in] tri2
     * @return true
     * @return false
     */
    template <class P, class L = typename P::Dual>
    requires ProjPlanePrimDual<P, L>
    inline constexpr auto check_desargue(const std::array<P, 3>& tri1, const std::array<P, 3>& tri2)
        -> bool {
        const auto trid1 = tri_dual(tri1);
        const auto trid2 = tri_dual(tri2);
        const auto b1 = persp(tri1, tri2);
        const auto b2 = persp(trid1, trid2);
        return (b1 && b2) || (!b1 && !b2);
    }

    /**
     * @brief Projective plane Concept
     *
     * @tparam V
     * @tparam P Point
     * @tparam L Line
     */
    template <typename V, class P, class L>
    concept ProjPlane = STD_ALT::equality_comparable<P> && ProjPlanePrim<P, L>  //
        && requires(const P& p, const P& q, const L& l, const V& a) {
        { p.aux() } -> STD_ALT::convertible_to<L>;                 // line not incident with p
        { p.dot(l) } -> STD_ALT::convertible_to<V>;                // for basic measurement
        { P::plucker(a, p, a, q) } -> STD_ALT::convertible_to<P>;  // module computation
    };

    /**
     * @brief Projective plane dual Concept
     *
     * @tparam V
     * @tparam P Point
     * @tparam L Line
     */
    template <typename V, class P, class L>
    concept ProjPlaneDual = ProjPlane<V, P, L> && ProjPlane<L, P, V>;

    /**
     * @brief Check Projective plane Axiom 2
     *
     * @tparam P Point
     * @tparam L Line
     */

    /**
     * @brief Check Axiom
     *
     * @tparam V
     * @tparam P
     * @tparam P::Dual
     * @param[in] p
     * @param[in] q
     * @param[in] l
     * @param[in] a
     * @param[in] b
     */
    template <typename V, class P, class L>
    requires ProjPlaneDual<V, P, L>
    inline auto check_axiom2(const P& p, const P& q, const L& l, const V& a, const V& b) -> void {
        assert(p.dot(l) == l.dot(p));
        assert(!p.aux().incident(p));
        const auto m = p.circ(q);
        assert(m.incident(P::plucker(a, p, b, q)));
    }

    /**
     * @brief harmonic conjugate
     *
     * @tparam V
     * @tparam P
     * @param[in] a
     * @param[in] b
     * @param[in] c
     * @return P
     */
    template <typename V, class P, class L = typename P::Dual>
    requires ProjPlaneDual<V, P, L>
    inline constexpr auto harm_conj(const P& a, const P& b, const P& c) -> P {
        assert(coincident(a, b, c));
        const auto ab = a.circ(b);
        const auto lc = ab.aux().circ(c);
        return P::plucker(lc.dot(a), a, lc.dot(b), b);
    }

    /**
     * @brief Involution
     *
     * @tparam V
     * @tparam P
     * @tparam P::Dual
     * @param[in] origin
     * @param[in] mirror
     * @param[in] p
     * @return P
     */
    template <typename V, class P, class L>
    requires ProjPlaneDual<V, P, L>
    inline constexpr auto involution(const P& origin, const L& mirror, const P& p) -> P {
        const auto po = p.circ(origin);
        const auto b = po.circ(mirror);
        return harm_conj(origin, b, p);
    }

    /*
    axiom(P p, P q, P r, L l) {
      l == L{p, q} => I(p, l) and I(q, l);
    }
    */

}  // namespace fun
