#include <iostream>
#include <string>
#include <vector>
#include "ds/algorithms.hpp"
#include "utils/FileIO.hpp"
#include "ds/storage/LinkedListStorage.hpp"

// Structure to hold keyword counts
struct KeywordFrequency {
    std::string word;
    int count;

    // Define operator< for sorting (needed if not using custom comparator)
    bool operator<(const KeywordFrequency& other) const {
        return count < other.count;
    }
};

int main(int argc, char* argv[]) {
    // 1. Argument Parsing
    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " <keyword_file> <data_directory>\n";
        return 1;
    }

    std::string keywordFile = argv[1];
    std::string dataDir = argv[2];

    std::cout << "--- Keyword Frequency Analyzer (Functional Paradigm) ---\n\n";

    // 2. Load Keywords
    // Input: "keyword file" separated by whitespace
    std::cout << "[1] Loading Keywords from: " << keywordFile << "\n";
    ds::LinkedListStorage<std::string> keywords = utils::FileHandler::readWords(keywordFile);
    std::cout << "    Loaded " << keywords.size() << " keywords.\n";

    // 3. Load Data Files
    // Input: "Directory full of text files"
    std::cout << "[2] Scanning Data Directory: " << dataDir << "\n";
    ds::LinkedListStorage<std::string> filePaths = utils::FileHandler::listFiles(dataDir);
    std::cout << "    Found " << filePaths.size() << " files.\n";

    // 4. "Scrape all of it": Read ALL words from ALL files
    // Transformation: List<FilePath> -> List<Word> (FlatMap)
    std::cout << "[3] Scraping all words from files...\n";
    auto allWords = ds::flatMap(filePaths, [](const std::string& path) {
        return utils::FileHandler::readWords(path);
    });
    std::cout << "    Total words scanned: " << allWords.size() << "\n";

    // 5. Count Frequencies for each keyword
    // This is the "Aggregation" step.
    // Approach: Map each keyword to a (Word, Count) pair by counting its occurrences in 'allWords'
    // Note: In a purely functional list-based approach, this is O(K * N), which can be slow for huge datasets.
    // Ideally, we'd convert 'allWords' to a frequency map/hash first for O(N) + O(K), but let's stick to our lists.
    
    std::cout << "[4] Calculating frequencies...\n";
    auto frequencies = ds::map(keywords, [&](const std::string& k) {
        // For each keyword, count how many times it appears in allWords
        // This inner reduction counts occurrences of 'k'
        int count = ds::reduce(allWords, 0, [&](int acc, const std::string& word) {
            return (word == k) ? acc + 1 : acc;
        });
        return KeywordFrequency{k, count};
    });

    // 6. Sort by Frequency (Descending)
    // "Decreasing order of their occurence frequencies"
    std::cout << "[5] Sorting by frequency (descending)...\n";
    auto sortedFrequencies = ds::sort(frequencies, [](const KeywordFrequency& a, const KeywordFrequency& b) {
        return a.count > b.count; // Descending order
    });

    // 7. Output Results
    std::cout << "\n--- Final Results ---\n";
    std::cout << "Keyword : Frequency\n";
    std::cout << "-------------------\n";
    
    ds::forEach(sortedFrequencies, [](const KeywordFrequency& kf) {
        // Only print if it actually appeared (optional, but cleaner)
        if (kf.count >= 0) { 
            std::cout << kf.word << " : " << kf.count << "\n";
        }
    });

    return 0;
}

