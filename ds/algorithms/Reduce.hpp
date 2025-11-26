#pragma once
#include "../storage/LinkedListStorage.hpp"

namespace ds {

/**
 * Reduce (Fold Left): Collapses the container into a single value.
 */
template <typename Container, typename U, typename BinaryOp>
U reduce(const Container& input, U initial, BinaryOp op) {
    U accumulator = initial;
    for (const auto& item : input) {
        accumulator = op(accumulator, item);
    }
    return accumulator;
}

} // namespace ds
