#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include "BufferReader.hpp"
#include <string>

class Tokenizer {
private:
    BufferReader& reader;
public:
    Tokenizer(BufferReader& br);
    bool getNextToken(std::string& token);
};

#endif // TOKENIZER_HPP
