#include "VersionIndex.hpp"

VersionIndex::VersionIndex(const std::string& name) : versionName(name) {}

const std::string& VersionIndex::getName() const { return versionName; }

void VersionIndex::addWord(const std::string& word) {
    wordCounts[word]++;
}

void VersionIndex::addWord(const std::string& word, int count) {
    wordCounts[word] += count;
}

int VersionIndex::getCount(const std::string& word) const {
    auto it = wordCounts.find(word);
    return it != wordCounts.end() ? it->second : 0;
}

const std::unordered_map<std::string, int>& VersionIndex::getCounts() const {
    return wordCounts;
}
