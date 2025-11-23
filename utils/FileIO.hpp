#pragma once
#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>
#include "../ds/storage/LinkedListStorage.hpp"

namespace utils {

namespace fs = std::filesystem;

class FileHandler {
public:
    /**
     * Reads a file and returns a list of words (separated by whitespace).
     */
    static ds::LinkedListStorage<std::string> readWords(const std::string& filepath) {
        ds::LinkedListStorage<std::string> words;
        std::ifstream file(filepath);
        if (!file.is_open()) {
            std::cerr << "Warning: Could not open file " << filepath << "\n";
            return words;
        }

        std::string word;
        while (file >> word) {
            // Optional: Clean punctuation here if needed, but assignment says "mixed quantitative and qualitative"
            // so raw words might be safer unless specified otherwise.
            words.push_back(word);
        }
        return words;
    }

    /**
     * Lists all regular files in a directory.
     */
    static ds::LinkedListStorage<std::string> listFiles(const std::string& dirPath) {
        ds::LinkedListStorage<std::string> files;
        try {
            if (!fs::exists(dirPath) || !fs::is_directory(dirPath)) {
                std::cerr << "Error: Directory does not exist -> " << dirPath << "\n";
                return files;
            }

            for (const auto& entry : fs::directory_iterator(dirPath)) {
                if (entry.is_regular_file()) {
                    files.push_back(entry.path().string());
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Filesystem error: " << e.what() << "\n";
        }
        return files;
    }
    
    /**
     * Read all lines from a file (useful for keyword file where keywords might be space separated or line separated)
     * This function treats the whole file contents as a source of whitespace-separated tokens.
     * (Same as readWords, but provided for semantic clarity if needed).
     */
    static ds::LinkedListStorage<std::string> readKeywords(const std::string& filepath) {
        return readWords(filepath);
    }
};

} // namespace utils

