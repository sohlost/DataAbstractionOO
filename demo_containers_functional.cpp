#include <iostream>
#include <string>
#include "ds/containers/Stack.hpp"
#include "ds/containers/Queue.hpp"
#include "ds/containers/PriorityQueue.hpp"
#include "ds/algorithms.hpp"

int main() {
    std::cout << "--- Containers + Functional Algorithms Demo ---\n\n";

    // 1. STACK -> Filter -> Map -> List
    ds::Stack<int> myStack;
    myStack.push(1);
    myStack.push(2);
    myStack.push(3);
    myStack.push(4);

    std::cout << "[Stack] Contents (LIFO order implied, storage order shown): ";
    // Even though it's a stack, we can peek at it for functional processing
    ds::forEach(myStack, [](int x) { std::cout << x << " "; }); 
    std::cout << "\n";

    auto evenSquares = ds::map(
        ds::filter(myStack, [](int x) { return x % 2 == 0; }),
        [](int x) { return x * x; }
    );

    std::cout << "        Evens Squared: ";
    ds::forEach(evenSquares, [](int x) { std::cout << x << " "; });
    std::cout << "\n\n";


    // 2. PRIORITY QUEUE -> Reduce -> Int
    ds::PriorityQueue<int> myPQ;
    myPQ.push(10);
    myPQ.push(5);
    myPQ.push(20);

    std::cout << "[PriorityQueue] Top is: " << myPQ.top() << "\n";
    
    // Calculate sum of elements inside the PQ without popping them!
    int sum = ds::reduce(myPQ, 0, [](int acc, int x) {
        return acc + x;
    });
    std::cout << "                Sum of all elements: " << sum << "\n\n";


    // 3. QUEUE -> Filter -> Queue (Manual Reload)
    ds::Queue<std::string> taskQueue;
    taskQueue.enqueue("fix_bug");
    taskQueue.enqueue("write_tests");
    taskQueue.enqueue("deploy_prod");
    taskQueue.enqueue("coffee_break");

    std::cout << "[Queue] Original Tasks:\n";
    ds::forEach(taskQueue, [](const std::string& s) { std::cout << "  - " << s << "\n"; });

    // Filter out "coffee_break"
    auto importantTasksList = ds::filter(taskQueue, [](const std::string& s) {
        return s != "coffee_break";
    });

    // Since HOFs return a List, we can reload a new Queue if we want
    ds::Queue<std::string> newQueue;
    ds::forEach(importantTasksList, [&](const std::string& s) {
        newQueue.enqueue(s);
    });

    std::cout << "[Queue] New Filtered Queue:\n";
    while(!newQueue.empty()) {
        std::cout << "  - " << newQueue.front() << "\n";
        newQueue.dequeue();
    }

    return 0;
}

