#include "BufferReader.hpp"
#include "AnalyzerException.hpp"

BufferReader::BufferReader() : bufSize(0), currentPos(0), bytesRead(0), eofReached(true) {}

BufferReader::BufferReader(const std::string& filename, size_t kbSize) : currentPos(0), bytesRead(0), eofReached(false) {
    if (kbSize < 256 || kbSize > 1024) {
        throw AnalyzerException("Buffer size must be between 256 and 1024 KB");
    }
    bufSize = kbSize * 1024;
    buffer.resize(bufSize);
    file.open(filename, std::ios::binary);
    if (!file.is_open()) {
        throw AnalyzerException("Failed to open file: " + filename);
    }
    loadNextChunk();
}

BufferReader::~BufferReader() {
    if (file.is_open()) file.close();
}

void BufferReader::loadNextChunk() {
    if (eofReached || !file.is_open()) return;
    file.read(buffer.data(), bufSize);
    bytesRead = file.gcount();
    currentPos = 0;
    if (bytesRead < bufSize) {
        eofReached = true;
        file.close();
    }
}

bool BufferReader::hasNext() const {
    return currentPos < bytesRead || !eofReached;
}

// Here int is used as return type due to EOF as EOF is -1 and will over lap with signed int
int BufferReader::getNextChar() {
    if (currentPos >= bytesRead) {
        if (eofReached) return EOF;
        loadNextChunk();
        if (bytesRead == 0) return EOF;
    }
    return static_cast<int>(static_cast<unsigned char>(buffer[currentPos++]));    // Here we first convert to unsigned so char goes between 0 to 255 and EOF can use -1 and then we convert it to int to return
}
