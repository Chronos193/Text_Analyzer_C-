#ifndef QUERY_PROCESSOR_HPP
#define QUERY_PROCESSOR_HPP

#include "VersionIndex.hpp"
#include <vector>
#include <string>

class QueryProcessor {
protected:
    std::vector<VersionIndex> versions;
public:
    // Use of virtual destructor shown here.
    virtual ~QueryProcessor() = default;
    
    void addVersion(const VersionIndex& v);
    // A pure virtual function use is shown here.
    virtual void execute() const = 0;
};

class WordQuery : public QueryProcessor {
    std::string targetWord;
public:
    WordQuery(const std::string& word);
    void execute() const override;
};

class DiffQuery : public QueryProcessor {
    std::string targetWord;
public:
    DiffQuery(const std::string& word);
    void execute() const override;
};

class TopKQuery : public QueryProcessor {
    int k;
public:
    TopKQuery(int k_val);
    void execute() const override;
};

#endif // QUERY_PROCESSOR_HPP
