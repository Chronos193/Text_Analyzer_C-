#ifndef BUFFER_READER_HPP
#define BUFFER_READER_HPP

#include <string>
#include <fstream>
#include <vector>

class BufferReader {
private:
    std::ifstream file;
    size_t bufSize;
    std::vector<char> buffer; //  Here didn't use using namespace std as the github project from which this project's structure is copied mentioned that on using namespace std in header the setting will be applied to every cpp file in which this header is used.
    size_t currentPos;
    size_t bytesRead;
    bool eofReached;

    void loadNextChunk();

public:
    // Use of constructors and destructor shown here.
    BufferReader();   // Non paramaterized constructor
    BufferReader(const std::string& filename, size_t kbSize); // Paramaterized constructor
    ~BufferReader(); // Destructor

    bool hasNext() const; // Check if there are more characters to read
    int getNextChar(); // Get the next character
};

#endif // BUFFER_READER_HPP
