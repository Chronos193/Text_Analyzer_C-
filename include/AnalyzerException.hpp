#ifndef ANALYZER_EXCEPTION_HPP // In python check is automatic but here we do it ourselves because c++ compiler just copy pastes codes and if we include it two time it will fail
#define ANALYZER_EXCEPTION_HPP

#include <exception>
#include <string>

class AnalyzerException : public std::exception {        // This made using exception class blueprints in c++ documentation to handle all exceptions in our project
private:
    std::string msg;
public:
    explicit AnalyzerException(const std::string& m) : msg(m) {}
    const char* what() const noexcept override { return msg.c_str(); }
};

#endif // ANALYZER_EXCEPTION_HPP
