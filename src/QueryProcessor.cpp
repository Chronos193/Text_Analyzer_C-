#include "QueryProcessor.hpp"
#include "AnalyzerException.hpp"
#include <iostream>

void QueryProcessor::addVersion(const VersionIndex& v) {
    versions.push_back(v);
}

WordQuery::WordQuery(const std::string& word) : targetWord(word) {}

void WordQuery::execute() const {
    if (versions.empty()) throw AnalyzerException("No versions provided for word query");
    std::cout << "Version: " << versions[0].getName() << "\n";
    std::cout << "Query result: " << versions[0].getCount(targetWord) << "\n";
}

DiffQuery::DiffQuery(const std::string& word) : targetWord(word) {}

void DiffQuery::execute() const {
    if (versions.size() < 2) throw AnalyzerException("Diff query requires two versions");
    std::cout << "Version: " << versions[0].getName() << ", " << versions[1].getName() << "\n";
    int diff = versions[1].getCount(targetWord) - versions[0].getCount(targetWord);
    std::cout << "Query result: Diff (" << versions[1].getName() << " - " << versions[0].getName() << ") = " << diff << "\n";
}

TopKQuery::TopKQuery(int k_val) : k(k_val) {}

void TopKQuery::execute() const {
    if (versions.empty()) throw AnalyzerException("No versions provided for top query");
    std::cout << "Version: " << versions[0].getName() << "\n";
    auto top = getSortedTopK(versions[0].getCounts(), k);
    std::cout << "Query result:\n";
    for (const auto& pair : top) {
        std::cout << pair.first << " -> " << pair.second << "\n";
    }
}
