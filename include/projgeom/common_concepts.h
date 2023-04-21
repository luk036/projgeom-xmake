#pragma once

#include <cmath>
#include <concepts>
#include <numeric>
#include <type_traits>
#include <utility>
// #include <ranges>
// namespace std = concepts;
// namespace std = std;

#include <concepts/concepts.hpp>

namespace fun {

template <typename T> using Value_type = typename T::value_type;

template <typename T>
using Element_type =
    typename std::decay<decltype(back(std::declval<T>()))>::type;

/**
 * @brief Sequence
 *
 * @tparam T
 */
template <typename T>
concept Sequence = //
    requires(T t, Element_type<T> x) {
      { t.size() } -> concepts::convertible_to<std::size_t>;
      { t.empty() } -> concepts::convertible_to<bool>;
      { t.back() } -> concepts::same_as<Element_type<T>>;
      { t.push_back(x) };
    };

template <typename K>
concept ring =                       //
    concepts::equality_comparable<K> //
    && requires(K a, K b) {
         { a + b } -> concepts::convertible_to<K>;
         { a - b } -> concepts::convertible_to<K>;
         { a *b } -> concepts::convertible_to<K>;
         { a += b } -> concepts::same_as<K &>;
         { a -= b } -> concepts::same_as<K &>;
         { a *= b } -> concepts::same_as<K &>;
         { -a } -> concepts::convertible_to<K>;
         { K(a) } -> concepts::convertible_to<K>;
         { K(0) } -> concepts::convertible_to<K>;
       };

template <typename K>
concept ordered_ring = ring<K> && concepts::totally_ordered<K>;

template <typename Z>
concept Integral =  //
    ordered_ring<Z> //
    && requires(Z a, Z b) {
         { a % b } -> concepts::convertible_to<Z>;
         { a / b } -> concepts::convertible_to<Z>;
         { a %= b } -> concepts::same_as<Z &>;
         { a /= b } -> concepts::same_as<Z &>;
       };

} // namespace fun
