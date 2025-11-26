#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <functional>
#include <map>
#include <limits>
#include <algorithm>

#include "ds/algorithms.hpp"
#include "ds/storage/LinkedListStorage.hpp"
#include "utils/FileIO.hpp"

// --- Helper: Split string by delimiter ---
std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        // Trim whitespace
        size_t first = token.find_first_not_of(" \t");
        if (first == std::string::npos) continue; // Skip empty
        size_t last = token.find_last_not_of(" \t");
        tokens.push_back(token.substr(first, (last - first + 1)));
    }
    return tokens;
}

int main() {
    ds::LinkedListStorage<int> data;
    bool running = true;

    std::cout << "===================================================\n";
    std::cout << "   FUNCTIONAL PIPELINE CLI (Int Mode)              \n";
    std::cout << "===================================================\n";
    std::cout << "Available Commands (chain with '|'):\n";
    std::cout << "  load <file>         : Load integers from file\n";
    std::cout << "  manual <n1> <n2>... : Load numbers manually\n";
    std::cout << "  filter > <val>      : Keep elements > val\n";
    std::cout << "  filter < <val>      : Keep elements < val\n";
    std::cout << "  map * <val>         : Multiply all by val\n";
    std::cout << "  map + <val>         : Add val to all\n";
    std::cout << "  sort asc            : Sort ascending\n";
    std::cout << "  sort desc           : Sort descending\n";
    std::cout << "  count               : Show count of elements\n";
    std::cout << "  show                : Print current list\n";
    std::cout << "  sum                 : Calculate sum\n";
    std::cout << "  inversions          : Count inversions\n";
    std::cout << "  exit                : Quit\n";
    std::cout << "Example: manual 5 1 10 2 | filter > 3 | map * 2 | sort asc | show\n";
    std::cout << "---------------------------------------------------\n";

    while (running) {
        std::cout << "> ";
        std::string line;
        if (!std::getline(std::cin, line)) break;
        if (line == "exit") break;

        auto commands = split(line, '|');
        
        for (const auto& cmdStr : commands) {
            std::stringstream ss(cmdStr);
            std::string action;
            ss >> action;

            if (action == "load") {
                std::string fname;
                ss >> fname;
                auto rawWords = utils::FileHandler::readWords(fname);
                // Parse ints
                ds::LinkedListStorage<int> newData = ds::map(rawWords, [](const std::string& s) {
                    try { return std::stoi(s); } catch(...) { return 0; }
                });
                // Append to current data or replace? Let's replace for "load", append is easy to change.
                data = newData; 
                std::cout << "[Loaded " << data.size() << " items]\n";

            } else if (action == "manual") {
                int val;
                ds::LinkedListStorage<int> newData;
                while (ss >> val) newData.push_back(val);
                data = newData;
                std::cout << "[Loaded " << data.size() << " items manually]\n";

            } else if (action == "filter") {
                std::string op;
                int val;
                ss >> op >> val;
                if (op == ">") {
                    data = ds::filter(data, [=](int x) { return x > val; });
                } else if (op == "<") {
                    data = ds::filter(data, [=](int x) { return x < val; });
                } else if (op == "==") {
                    data = ds::filter(data, [=](int x) { return x == val; });
                }
                std::cout << "[Filtered -> " << data.size() << " items]\n";

            } else if (action == "map") {
                std::string op;
                int val;
                ss >> op >> val;
                if (op == "*") {
                    data = ds::map(data, [=](int x) { return x * val; });
                } else if (op == "+") {
                    data = ds::map(data, [=](int x) { return x + val; });
                } else if (op == "-") {
                    data = ds::map(data, [=](int x) { return x - val; });
                }
                std::cout << "[Mapped]\n";

            } else if (action == "sort") {
                std::string order;
                ss >> order;
                if (order == "desc") {
                    data = ds::sort(data, std::greater<int>{});
                } else {
                    data = ds::sort(data); // Default asc
                }
                std::cout << "[Sorted]\n";

            } else if (action == "show") {
                std::cout << "Data: ";
                ds::forEach(data, [](int x) { std::cout << x << " "; });
                std::cout << "\n";

            } else if (action == "count") {
                std::cout << "Count: " << data.size() << "\n";

            } else if (action == "sum") {
                long long sum = ds::reduce(data, 0LL, [](long long acc, int x) { return acc + x; });
                std::cout << "Sum: " << sum << "\n";

            } else if (action == "inversions") {
                 long long inv = ds::countInversions(data);
                 std::cout << "Inversions: " << inv << "\n";
            } else {
                std::cout << "Unknown command: " << action << "\n";
            }
        }
    }

    std::cout << "Goodbye.\n";
    return 0;
}

