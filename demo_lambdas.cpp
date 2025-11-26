#include <iostream>
#include <string>
#include <vector>
#include "ds/storage/LinkedListStorage.hpp"
#include "ds/algorithms.hpp"

// 1. Standard Function
bool isEven(int n) {
    return n % 2 == 0;
}

// 2. Functor (Function Object)
struct Multiplier {
    int factor;
    explicit Multiplier(int f) : factor(f) {}
    
    int operator()(int n) const {
        return n * factor;
    }
};

int main() {
    std::cout << "--- Higher Order Functions & Lambdas Demo ---\n\n";

    // Initial Data
    ds::LinkedListStorage<int> numbers;
    for (int i = 1; i <= 10; ++i) numbers.push_back(i);

    std::cout << "Original Data: ";
    ds::forEach(numbers, [](int n) { std::cout << n << " "; });
    std::cout << "\n\n";

    // ---------------------------------------------------------
    // Example A: Passing a Standard Function Pointer
    // ---------------------------------------------------------
    std::cout << "[A] Filtering Evens using function pointer 'isEven':\n";
    auto evens = ds::filter(numbers, isEven);
    
    ds::forEach(evens, [](int n) { std::cout << n << " "; });
    std::cout << "\n\n";

    // ---------------------------------------------------------
    // Example B: Passing a Functor (Object with state)
    // ---------------------------------------------------------
    std::cout << "[B] Mapping using Functor (Multiply by 10):\n";
    Multiplier x10(10); 
    auto decades = ds::map(numbers, x10);
    
    ds::forEach(decades, [](int n) { std::cout << n << " "; });
    std::cout << "\n\n";

    // ---------------------------------------------------------
    // Example C: Inline Lambda
    // ---------------------------------------------------------
    std::cout << "[C] Inline Lambda (Square numbers):\n";
    auto squares = ds::map(numbers, [](int n) { 
        return n * n; 
    });

    ds::forEach(squares, [](int n) { std::cout << n << " "; });
    std::cout << "\n\n";

    // ---------------------------------------------------------
    // Example D: Capturing Lambda (The most powerful version)
    // ---------------------------------------------------------
    int threshold;
    std::cout << "[D] Enter a threshold for filtering (e.g., 5): ";
    // Hardcoding input for non-interactive execution, but normally std::cin >> threshold
    threshold = 5; 
    std::cout << threshold << "\n";

    std::cout << "    Filtering numbers > " << threshold << " using captured variable:\n";
    
    // [=] captures 'threshold' by value so it's visible inside
    auto largeNumbers = ds::filter(numbers, [=](int n) {
        return n > threshold; 
    });

    ds::forEach(largeNumbers, [](int n) { std::cout << n << " "; });
    std::cout << "\n\n";

    // ---------------------------------------------------------
    // Example E: Lambda with Mutable State (in forEach)
    // ---------------------------------------------------------
    std::cout << "[E] Accumulating sum using external reference capture [&]:\n";
    int runningSum = 0;
    
    // [&] captures runningSum by reference so we can modify it
    ds::forEach(numbers, [&](int n) {
        runningSum += n;
    });

    std::cout << "    Total Sum: " << runningSum << "\n";

    return 0;
}

