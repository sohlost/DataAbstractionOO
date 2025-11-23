#pragma once
#include "storage/LinkedListStorage.hpp"
#include <functional>
#include <algorithm>

namespace ds {

// --------------------------------------------------------------------------
// Functional Primitives
// --------------------------------------------------------------------------

/**
 * Map: Transforms a list of T into a list of U using a transformer function.
 * Pure function: Returns a new list, does not modify input.
 */
template <typename T, typename Func>
auto map(const LinkedListStorage<T>& input, Func f) -> LinkedListStorage<decltype(f(std::declval<T>()))> {
    using U = decltype(f(std::declval<T>()));
    LinkedListStorage<U> result;
    for (const auto& item : input) {
        result.push_back(f(item));
    }
    return result;
}

/**
 * Filter: Returns a new list containing only elements that satisfy the predicate.
 */
template <typename T, typename Predicate>
LinkedListStorage<T> filter(const LinkedListStorage<T>& input, Predicate p) {
    LinkedListStorage<T> result;
    for (const auto& item : input) {
        if (p(item)) {
            result.push_back(item);
        }
    }
    return result;
}

/**
 * Reduce (Fold Left): Collapses the list into a single value.
 */
template <typename T, typename U, typename BinaryOp>
U reduce(const LinkedListStorage<T>& input, U initial, BinaryOp op) {
    U accumulator = initial;
    for (const auto& item : input) {
        accumulator = op(accumulator, item);
    }
    return accumulator;
}

/**
 * ForEach: Applies a function to every element (for side effects like printing).
 */
template <typename T, typename Func>
void forEach(const LinkedListStorage<T>& input, Func f) {
    for (const auto& item : input) {
        f(item);
    }
}

/**
 * FlatMap: Maps each element to a list, then flattens the result.
 * Useful for processing lines in files -> words.
 */
template <typename T, typename Func>
auto flatMap(const LinkedListStorage<T>& input, Func f) -> decltype(f(std::declval<T>())) {
    using ResultListType = decltype(f(std::declval<T>())); // e.g. LinkedListStorage<String>
    ResultListType result;
    for (const auto& item : input) {
        ResultListType sublist = f(item);
        for (const auto& subItem : sublist) {
            result.push_back(subItem);
        }
    }
    return result;
}

// --------------------------------------------------------------------------
// Sorting (Merge Sort)
// --------------------------------------------------------------------------

namespace internal {
    // Helper to merge two sorted lists
    template <typename T, typename Comparator>
    LinkedListStorage<T> merge(const LinkedListStorage<T>& left, const LinkedListStorage<T>& right, Comparator cmp) {
        LinkedListStorage<T> result;
        auto itL = left.begin();
        auto itR = right.begin();
        
        while (itL != left.end() && itR != right.end()) {
            if (cmp(*itL, *itR)) {
                result.push_back(*itL);
                ++itL;
            } else {
                result.push_back(*itR);
                ++itR;
            }
        }
        while (itL != left.end()) { result.push_back(*itL); ++itL; }
        while (itR != right.end()) { result.push_back(*itR); ++itR; }
        return result;
    }
}

/**
 * Sort: Returns a NEW sorted list using Merge Sort.
 * Time Complexity: O(N log N)
 */
template <typename T, typename Comparator = std::less<T>>
LinkedListStorage<T> sort(const LinkedListStorage<T>& input, Comparator cmp = Comparator{}) {
    if (input.size() <= 1) return input;

    // Split
    LinkedListStorage<T> left;
    LinkedListStorage<T> right;
    std::size_t mid = input.size() / 2;
    std::size_t i = 0;
    
    for (const auto& item : input) {
        if (i < mid) left.push_back(item);
        else right.push_back(item);
        i++;
    }

    // Recurse
    return internal::merge(sort(left, cmp), sort(right, cmp), cmp);
}

} // namespace ds

