#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include <iomanip>

#include "ds/algorithms.hpp"
#include "ds/storage/LinkedListStorage.hpp"
#include "utils/FileIO.hpp"
#include "ds/containers/Queue.hpp"
#include "ds/containers/Stack.hpp"

// --- Helper Functions ---

void clearScreen() {
    // ANSI escape code for clear screen, works in most modern terminals
    std::cout << "\033[2J\033[1;1H";
}

void pressEnterToContinue() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

// --- Numeric Mode Handler ---
void runNumericMode() {
    ds::LinkedListStorage<int> data;
    bool running = true;

    while (running) {
        clearScreen();
        std::cout << "=== NUMERIC MODE ===\n";
        std::cout << "Current Data Size: " << data.size() << "\n";
        if (!data.empty()) {
            std::cout << "Preview: ";
            int count = 0;
            ds::forEach(data, [&](int x) { if(count++ < 10) std::cout << x << " "; });
            if (data.size() > 10) std::cout << "...";
            std::cout << "\n";
        }
        std::cout << "--------------------\n";
        std::cout << "1. Load Integers from File\n";
        std::cout << "2. Enter Integers Manually\n";
        std::cout << "3. Filter (Keep > X)\n";
        std::cout << "4. Map (Multiply by X)\n";
        std::cout << "5. Sort (Ascending)\n";
        std::cout << "6. Sort (Descending)\n";
        std::cout << "7. Aggregate: Average\n";
        std::cout << "8. Aggregate: Count Inversions\n";
        std::cout << "9. Back to Main Menu\n";
        std::cout << "Select: ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (choice == 1) {
            std::cout << "Enter filename: ";
            std::string fname;
            std::cin >> fname;
            // Reuse FileHandler readWords but parse as int
            auto words = utils::FileHandler::readWords(fname);
            data = ds::map(words, [](const std::string& s) {
                try { return std::stoi(s); } catch(...) { return 0; }
            });
            std::cout << "Loaded " << data.size() << " integers.\n";
            pressEnterToContinue();
        } else if (choice == 2) {
            std::cout << "Enter numbers (non-number to stop): ";
            int val;
            while (std::cin >> val) {
                data.push_back(val);
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else if (choice == 3) {
            std::cout << "Filter values greater than: ";
            int threshold;
            std::cin >> threshold;
            data = ds::filter(data, [=](int x) { return x > threshold; });
            std::cout << "Filtered.\n";
        } else if (choice == 4) {
            std::cout << "Multiply all by: ";
            int factor;
            std::cin >> factor;
            data = ds::map(data, [=](int x) { return x * factor; });
            std::cout << "Mapped.\n";
        } else if (choice == 5) {
            data = ds::sort(data);
            std::cout << "Sorted Ascending.\n";
        } else if (choice == 6) {
            data = ds::sort(data, std::greater<int>{});
            std::cout << "Sorted Descending.\n";
        } else if (choice == 7) {
            if (data.empty()) {
                std::cout << "No data.\n";
            } else {
                long long sum = ds::reduce(data, 0LL, [](long long acc, int x) { return acc + x; });
                double avg = (double)sum / data.size();
                std::cout << "Average: " << std::fixed << std::setprecision(2) << avg << "\n";
            }
            pressEnterToContinue();
        } else if (choice == 8) {
            long long inversions = ds::countInversions(data);
            std::cout << "Inversion Count: " << inversions << "\n";
            pressEnterToContinue();
        } else if (choice == 9) {
            running = false;
        }
    }
}

// --- Text Mode Handler ---
void runTextMode() {
    ds::LinkedListStorage<std::string> data;
    bool running = true;

    while (running) {
        clearScreen();
        std::cout << "=== TEXT MODE ===\n";
        std::cout << "Current Data Size: " << data.size() << " words\n";
         if (!data.empty()) {
            std::cout << "Preview: ";
            int count = 0;
            ds::forEach(data, [&](const std::string& x) { if(count++ < 5) std::cout << x << " "; });
            if (data.size() > 5) std::cout << "...";
            std::cout << "\n";
        }
        std::cout << "-----------------\n";
        std::cout << "1. Load Words from File\n";
        std::cout << "2. Search / Filter (Contains Substring)\n";
        std::cout << "3. Map (To Uppercase)\n";
        std::cout << "4. Sort (Alphabetical)\n";
        std::cout << "5. Sort (By Length)\n";
        std::cout << "6. Aggregate: Longest Word\n";
        std::cout << "7. Back to Main Menu\n";
        std::cout << "Select: ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (choice == 1) {
            std::cout << "Enter filename: ";
            std::string fname;
            std::cin >> fname;
            data = utils::FileHandler::readWords(fname);
            std::cout << "Loaded " << data.size() << " words.\n";
            pressEnterToContinue();
        } else if (choice == 2) {
            std::cout << "Keep words containing: ";
            std::string sub;
            std::cin >> sub;
            data = ds::filter(data, [=](const std::string& s) {
                return s.find(sub) != std::string::npos;
            });
            std::cout << "Filtered.\n";
        } else if (choice == 3) {
            data = ds::map(data, [](const std::string& s) {
                std::string upper = s;
                for(auto& c : upper) c = toupper(c);
                return upper;
            });
            std::cout << "Converted to Uppercase.\n";
        } else if (choice == 4) {
            data = ds::sort(data);
            std::cout << "Sorted Alphabetically.\n";
        } else if (choice == 5) {
            data = ds::sort(data, [](const std::string& a, const std::string& b) {
                return a.length() < b.length();
            });
            std::cout << "Sorted by Length.\n";
        } else if (choice == 6) {
            if (data.empty()) {
                std::cout << "No data.\n";
            } else {
                std::string longest = ds::reduce(data, std::string(""), [](const std::string& acc, const std::string& curr) {
                    return curr.length() > acc.length() ? curr : acc;
                });
                std::cout << "Longest Word: " << longest << " (Length: " << longest.length() << ")\n";
            }
            pressEnterToContinue();
        } else if (choice == 7) {
            running = false;
        }
    }
}

int main() {
    bool running = true;
    while (running) {
        clearScreen();
        std::cout << "==========================================\n";
        std::cout << "   FUNCTIONAL DATA PROCESSING CLI SYSTEM  \n";
        std::cout << "==========================================\n";
        std::cout << "1. Numeric Data Processing Mode\n";
        std::cout << "2. Text Data Processing Mode\n";
        std::cout << "3. Exit\n";
        std::cout << "Select Mode: ";
        
        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (choice == 1) {
            runNumericMode();
        } else if (choice == 2) {
            runTextMode();
        } else if (choice == 3) {
            running = false;
        }
    }
    std::cout << "Goodbye.\n";
    return 0;
}

