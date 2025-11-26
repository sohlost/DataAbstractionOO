#pragma once
#include "../storage/LinkedListStorage.hpp"
#include <utility>

namespace ds {

/**
 * FlatMap: Maps each element to a list, then flattens the result.
 * Returns a LinkedListStorage of the inner type.
 */
template <typename Container, typename Func>
auto flatMap(const Container& input, Func f) -> decltype(f(std::declval<typename Container::value_type>())) {
    using T = typename Container::value_type;
    using ResultListType = decltype(f(std::declval<T>())); // Expected to be a LinkedListStorage-like
    
    ResultListType result;
    for (const auto& item : input) {
        ResultListType sublist = f(item);
        for (const auto& subItem : sublist) {
            result.push_back(subItem);
        }
    }
    return result;
}

} // namespace ds
