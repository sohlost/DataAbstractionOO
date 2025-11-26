#include <iostream>
#include <string>
#include "ds/storage/LinkedListStorage.hpp"
#include "ds/algorithms.hpp"
#include "ds/containers/Queue.hpp"

// A simple data structure
struct Task {
    int id;
    std::string description;
    int priority;
};

int main() {
    // 1. Initialize raw data in LinkedListStorage
    ds::LinkedListStorage<Task> rawTasks;
    rawTasks.push_back({1, "Low priority task", 1});
    rawTasks.push_back({2, "High priority task", 10});
    rawTasks.push_back({3, "Medium priority task", 5});
    rawTasks.push_back({4, "Another high priority task", 8});
    rawTasks.push_back({5, "Junk task", -1});

    std::cout << "--- Functional Processing Demo ---\n";
    std::cout << "Initial tasks: " << rawTasks.size() << "\n";

    // 2. Functional Processing Pipeline
    // Keep data in LinkedListStorage during transformation steps.
    
    // Step A: Filter valid tasks (priority > 0)
    auto validTasks = ds::filter(rawTasks, [](const Task& t) {
        return t.priority > 0;
    });
    std::cout << "Filtered tasks (valid only): " << validTasks.size() << "\n";

    // Step B: Map to upgrade priority (e.g., boost all by 1)
    auto boostedTasks = ds::map(validTasks, [](const Task& t) {
        Task newTask = t;
        newTask.priority += 1;
        return newTask;
    });

    // Step C: Sort by priority (descending)
    auto sortedTasks = ds::sort(boostedTasks, [](const Task& a, const Task& b) {
        return a.priority > b.priority; 
    });

    // 3. Move to Container (Queue)
    // Now that processing is done, we move to a Queue for consumption.
    // This separates the "Data Transformation Phase" (Functional) from the "Data Consumption Phase" (OO/Imperative).
    ds::Queue<Task> taskQueue;
    
    // Use forEach to push elements into the Queue
    ds::forEach(sortedTasks, [&](const Task& t) {
        taskQueue.enqueue(t);
    });

    std::cout << "Processed tasks enqueued: " << taskQueue.size() << "\n";

    // 4. Consume from Queue
    std::cout << "\n--- Executing Tasks from Queue ---\n";
    while (!taskQueue.empty()) {
        Task t = taskQueue.front();
        taskQueue.dequeue();
        std::cout << "Processing Task ID: " << t.id 
                  << " [Priority: " << t.priority << "] - " 
                  << t.description << "\n";
    }

    return 0;
}

