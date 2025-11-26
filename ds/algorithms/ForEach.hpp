#pragma once
#include "../storage/LinkedListStorage.hpp"

namespace ds {

/**
 * ForEach: Applies a function to every element (for side effects like printing).
 */
template <typename Container, typename Func>
void forEach(const Container& input, Func f) {
    for (const auto& item : input) {
        f(item);
    }
}

} // namespace ds
