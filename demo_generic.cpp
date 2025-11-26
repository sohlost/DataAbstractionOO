#include <iostream>
#include <vector>
#include <list>
#include "ds/storage/LinkedListStorage.hpp"
#include "ds/algorithms.hpp"

int main() {
    std::cout << "--- Generic Functional Algorithms Demo ---\n\n";

    // 1. Using std::vector (Standard Library Container)
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::cout << "Input (std::vector): ";
    for(int x : vec) std::cout << x << " ";
    std::cout << "\n";

    auto mappedVec = ds::map(vec, [](int x) { return x * 10; });
    std::cout << "Mapped (Vector -> List): ";
    ds::forEach(mappedVec, [](int x) { std::cout << x << " "; });
    std::cout << "\n\n";

    // 2. Using std::list
    std::list<int> stdList = {10, 20, 30};
    auto reducedList = ds::reduce(stdList, 0, [](int acc, int x) { return acc + x; });
    std::cout << "Reduced (std::list sum): " << reducedList << "\n\n";

    // 3. Using Custom LinkedListStorage (Our Container)
    ds::LinkedListStorage<int> customList;
    customList.push_back(5);
    customList.push_back(1);
    customList.push_back(3);

    auto sortedCustom = ds::sort(customList);
    std::cout << "Sorted (LinkedListStorage): ";
    ds::forEach(sortedCustom, [](int x) { std::cout << x << " "; });
    std::cout << "\n\n";

    // 4. Cross-Container Chaining
    // Vector -> Filter -> Map -> List
    std::vector<int> mixed = {1, 2, 3, 4, 5, 6};
    auto result = ds::map(
        ds::filter(mixed, [](int x) { return x % 2 == 0; }), // Returns LinkedListStorage
        [](int x) { return x * x; }                          // Input is LinkedListStorage
    );

    std::cout << "Chained (Vector -> Filter -> Map): ";
    ds::forEach(result, [](int x) { std::cout << x << " "; });
    std::cout << "\n";

    return 0;
}

