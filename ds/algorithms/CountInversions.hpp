#pragma once
#include "../storage/LinkedListStorage.hpp"
#include <vector>
#include <iterator>

namespace ds {

namespace internal {
    // Helper to merge and count split inversions
    template <typename T, typename Comparator>
    long long mergeAndCount(std::vector<T>& vec, int left, int mid, int right, Comparator cmp) {
        std::vector<T> leftSub(vec.begin() + left, vec.begin() + mid + 1);
        std::vector<T> rightSub(vec.begin() + mid + 1, vec.begin() + right + 1);

        size_t i = 0;
        size_t j = 0;
        int k = left;
        long long inversions = 0;

        while (i < leftSub.size() && j < rightSub.size()) {
            if (cmp(rightSub[j], leftSub[i])) {
                // right element is smaller (or whatever cmp defines as "inversion" context)
                // If we are sorting ascendingly (cmp = less), and right < left, it's an inversion.
                // Inversions are all remaining elements in left subarray
                vec[k++] = rightSub[j++];
                inversions += (leftSub.size() - i);
            } else {
                vec[k++] = leftSub[i++];
            }
        }

        while (i < leftSub.size()) vec[k++] = leftSub[i++];
        while (j < rightSub.size()) vec[k++] = rightSub[j++];

        return inversions;
    }

    template <typename T, typename Comparator>
    long long sortAndCount(std::vector<T>& vec, int left, int right, Comparator cmp) {
        if (left >= right) return 0;

        int mid = left + (right - left) / 2;
        long long count = 0;

        count += sortAndCount(vec, left, mid, cmp);
        count += sortAndCount(vec, mid + 1, right, cmp);
        count += mergeAndCount(vec, left, mid, right, cmp);

        return count;
    }
}

/**
 * Count Inversions: Counts how many pairs (i, j) exist such that i < j but a[i] > a[j].
 * Uses O(N log N) Merge Sort approach.
 * Note: This function copies the data into a vector for efficient indexing during the count.
 */
template <typename Container, typename Comparator = std::less<typename Container::value_type>>
long long countInversions(const Container& input, Comparator cmp = Comparator{}) {
    using T = typename Container::value_type;
    
    // Copy to vector for random access required by efficient inversion counting
    std::vector<T> vec;
    for (const auto& item : input) {
        vec.push_back(item);
    }

    if (vec.empty()) return 0;
    return internal::sortAndCount(vec, 0, (int)vec.size() - 1, cmp);
}

} // namespace ds

