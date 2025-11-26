#pragma once
#include "../storage/LinkedListStorage.hpp"
#include <utility>

namespace ds {

/**
 * Map: Transforms a Container<T> into a LinkedListStorage<U> using a transformer function.
 * Pure function: Returns a new list, does not modify input.
 */
template <typename Container, typename Func>
auto map(const Container& input, Func f) -> LinkedListStorage<decltype(f(std::declval<typename Container::value_type>()))> {
    using T = typename Container::value_type;
    using U = decltype(f(std::declval<T>()));
    LinkedListStorage<U> result;
    for (const auto& item : input) {
        result.push_back(f(item));
    }
    return result;
}

} // namespace ds
