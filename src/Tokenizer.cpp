#include "Tokenizer.hpp"
#include <cctype>

Tokenizer::Tokenizer(BufferReader& br) : reader(br) {}

bool Tokenizer::getNextToken(std::string& token) {
    token.clear();
    char c;
    while (reader.hasNext()) {
        c = reader.getNextChar();
        if (c == EOF) break;
        
        if (std::isalnum(c)) {
            token += std::tolower(c);
        } else if (!token.empty()) {
            return true;
        }
    }
    return !token.empty();
}
