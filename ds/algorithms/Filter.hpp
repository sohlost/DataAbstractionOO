#pragma once
#include "../storage/LinkedListStorage.hpp"

namespace ds {

/**
 * Filter: Returns a new list containing only elements that satisfy the predicate.
 */
template <typename Container, typename Predicate>
auto filter(const Container& input, Predicate p) -> LinkedListStorage<typename Container::value_type> {
    using T = typename Container::value_type;
    LinkedListStorage<T> result;
    for (const auto& item : input) {
        if (p(item)) {
            result.push_back(item);
        }
    }
    return result;
}

} // namespace ds
