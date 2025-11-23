#include <iostream>
#include <string>
#include <vector>
#include <utility>

#include "ds/storage/LinkedListStorage.hpp"
#include "ds/algorithms.hpp"
#include "utils/FileIO.hpp"

// Simple Pair struct to avoid std::pair complexity with deep templates if needed, 
// but std::pair is fine.
using WordCount = std::pair<std::string, int>;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " <keyword_file> <data_directory>\n";
        return 1;
    }

    std::string keywordFile = argv[1];
    std::string dataDir = argv[2];

    std::cout << "--- Functional-OO Assignment Demo ---\n";
    std::cout << "1. Loading Keywords from: " << keywordFile << "\n";
    
    // 1. Load Keywords
    auto keywords = utils::FileHandler::readKeywords(keywordFile);
    std::cout << "   Loaded " << keywords.size() << " keywords.\n";

    std::cout << "2. Loading Data Files from: " << dataDir << "\n";
    
    // 2. Load all files in directory
    auto filePaths = utils::FileHandler::listFiles(dataDir);
    std::cout << "   Found " << filePaths.size() << " files.\n";

    // 3. Read ALL words from ALL files into one giant list
    // Use flatMap: List<FilePath> -> List<Word>
    auto allWords = ds::flatMap(filePaths, [](const std::string& path) {
        return utils::FileHandler::readWords(path);
    });
    std::cout << "   Total words scanned: " << allWords.size() << "\n";

    // 4. FILTER: Keep only words that are in the keyword list
    // Optimization: Put keywords in a vector/set for O(1) lookup? 
    // For strict functional purity with our list, we scan. (Slow but correct).
    // To speed it up, let's cache keywords in a std::vector or keep them as is.
    // Let's stick to the assignment spirit: "List structures".
    
    auto relevantWords = ds::filter(allWords, [&](const std::string& w) {
        // Check if w is in keywords list.
        // Since our LinkedListStorage doesn't have 'contains', we use a manual check
        // or helper. For performance, pre-sorting keywords or using a hash set is better,
        // but here is the pure list approach:
        bool found = false;
        for (const auto& k : keywords) {
            if (k == w) { found = true; break; }
        }
        return found;
    });
    std::cout << "   Relevant keywords found: " << relevantWords.size() << "\n";

    // 5. MAP: Transform String -> Pair<String, int>(w, 1)
    auto pairs = ds::map(relevantWords, [](const std::string& w) {
        return std::make_pair(w, 1);
    });

    // 6. SORT: Sort alphabetically to group identical words
    auto sortedPairs = ds::sort(pairs, [](const WordCount& a, const WordCount& b) {
        return a.first < b.first;
    });

    // 7. REDUCE (Group By): Aggregate counts
    // We reduce into a NEW list of unique WordCounts
    ds::LinkedListStorage<WordCount> counts = ds::reduce(
        sortedPairs, 
        ds::LinkedListStorage<WordCount>{}, // Initial empty list
        [](ds::LinkedListStorage<WordCount> acc, const WordCount& current) {
            if (!acc.empty() && acc.back().first == current.first) {
                // Determine if we can modify in place (since acc is a value in reduce)
                // To be purely functional, we'd pop, increment, push.
                // But since we have mutable access to the accumulator copy:
                WordCount last = acc.back();
                acc.pop_back();
                last.second += current.second;
                acc.push_back(last);
            } else {
                acc.push_back(current);
            }
            return acc;
        }
    );

    // 8. FINAL SORT: Sort by frequency (descending)
    auto finalResult = ds::sort(counts, [](const WordCount& a, const WordCount& b) {
        return a.second > b.second; // Descending count
    });

    // 9. Output
    std::cout << "\n--- Results (Keyword: Frequency) ---\n";
    ds::forEach(finalResult, [](const WordCount& wc) {
        std::cout << wc.first << ": " << wc.second << "\n";
    });

    return 0;
}

