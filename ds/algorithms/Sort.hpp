#pragma once
#include "../storage/LinkedListStorage.hpp"
#include <functional>

namespace ds {

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
 * Can accept ANY container, but returns a LinkedListStorage<T> to ensure order.
 * Time Complexity: O(N log N)
 */
template <typename Container, typename Comparator = std::less<typename Container::value_type>>
auto sort(const Container& input, Comparator cmp = Comparator{}) -> LinkedListStorage<typename Container::value_type> {
    using T = typename Container::value_type;
    
    // Convert input container to LinkedListStorage if it isn't one already,
    // because our merge sort implementation relies on splitting linked lists.
    LinkedListStorage<T> listInput;
    for(const auto& item : input) {
        listInput.push_back(item);
    }

    if (listInput.size() <= 1) return listInput;

    // Split
    LinkedListStorage<T> left;
    LinkedListStorage<T> right;
    std::size_t mid = listInput.size() / 2;
    std::size_t i = 0;
    
    for (const auto& item : listInput) {
        if (i < mid) left.push_back(item);
        else right.push_back(item);
        i++;
    }

    // Recurse (Note: Recursive calls will use the LinkedListStorage overload implicitly if we had one, 
    // but since we made this generic, it works recursively too)
    return internal::merge(sort(left, cmp), sort(right, cmp), cmp);
}

} // namespace ds
