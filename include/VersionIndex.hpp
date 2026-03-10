#ifndef VERSION_INDEX_HPP
#define VERSION_INDEX_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

class VersionIndex {
private:
    std::string versionName;
    std::unordered_map<std::string, int> wordCounts;
public:
    VersionIndex(const std::string& name);

    const std::string& getName() const;
    void addWord(const std::string& word);
    void addWord(const std::string& word, int count);
    int getCount(const std::string& word) const;
    const std::unordered_map<std::string, int>& getCounts() const;
};

template<typename K, typename V>
std::vector<std::pair<K, V>> getSortedTopK(const std::unordered_map<K, V>& map, int k) {
    std::vector<std::pair<K, V>> vec(map.begin(), map.end());
    std::sort(vec.begin(), vec.end(), [](const std::pair<K, V>& a, const std::pair<K, V>& b) {
        if (a.second != b.second) return a.second > b.second;
        return a.first < b.first;
    });
    if (static_cast<int>(vec.size()) > k) vec.resize(k);
    return vec;
}

#endif // VERSION_INDEX_HPP
