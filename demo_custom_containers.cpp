#include <iostream>
#include <string>
#include "ds/storage/LinkedListStorage.hpp"
#include "ds/storage/VectorHeapStorage.hpp"
#include "ds/algorithms.hpp"
#include "ds/containers/Queue.hpp"

// Example Comparator for Max Heap
struct GreaterInt {
    bool operator()(int a, int b) const { return a < b; } // std::push_heap default is max-heap using <
};

int main() {
    std::cout << "--- Custom Containers & Functional Paradigm Demo ---\n";

    // 1. VectorHeapStorage (Your Custom Design)
    // Stores data in a heap structure (Priority Queue semantics)
    ds::VectorHeapStorage<int, GreaterInt> myHeap;
    myHeap.push(10);
    myHeap.push(5);
    myHeap.push(20);
    myHeap.push(1);
    myHeap.push(15);

    std::cout << "1. Heap Pop Order (Proof of Heap Structure): ";
    // We can't iterate to show heap order easily without popping, so let's just peek
    std::cout << "Top is " << myHeap.top() << " (Should be 20)\n";
    
    // 2. Functional Processing on Heap Storage
    // Even though it's a heap, we can iterate over its underlying storage
    // to perform functional transformations.
    
    std::cout << "\n2. Functional Pipeline (Filter -> Map):\n";
    
    // Filter: Keep numbers > 5
    auto bigNumbers = ds::filter(myHeap, [](int x) {
        return x > 5;
    });
    
    // Map: Double them
    auto doubled = ds::map(bigNumbers, [](int x) {
        return x * 2;
    });

    std::cout << "   Result (List): ";
    ds::forEach(doubled, [](int x) { std::cout << x << " "; });
    std::cout << "\n";

    // 3. Moving Result to another Container (Queue)
    ds::Queue<int> resultQueue;
    ds::forEach(doubled, [&](int x) {
        resultQueue.enqueue(x);
    });

    std::cout << "\n3. Final Result in Queue (Size: " << resultQueue.size() << ")\n";
    while(!resultQueue.empty()) {
        std::cout << "   Dequeue: " << resultQueue.front() << "\n";
        resultQueue.dequeue();
    }

    return 0;
}

