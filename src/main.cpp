#include "BufferReader.hpp"
#include "Tokenizer.hpp"
#include "VersionIndex.hpp"
#include "QueryProcessor.hpp"
#include "AnalyzerException.hpp"

#include <iostream>
#include <string>
#include <memory>
#include <chrono>

using namespace std;

// Helper function to build index from file
VersionIndex buildIndex(const string& file, const string& version, int bufferSize) {
    BufferReader br(file, bufferSize);
    Tokenizer tokenizer(br);
    VersionIndex index(version);
    string token;
    while (tokenizer.getNextToken(token)) {
        index.addWord(token);
    }
    return index;
}

void printHelp() {
    cout << "Usage: analyzer [OPTIONS]\n"
         << "Analyze and query word occurrences across text files incrementally.\n\n"
         << "Options:\n"
         << "  -h, --help               Display this help and exit\n"
         << "  --file, --file1 <FILE>   Specify the main input text file\n"
         << "  --file2 <FILE>           Specify the second input file (for diff query)\n"
         << "  --version, --version1 <V>  Specify version name for the first file\n"
         << "  --version2 <V>           Specify version name for the second file\n"
         << "  --buffer <KB>            Set buffer size in KB (256 to 1024, default 256)\n"
         << "  --query <TYPE>           Specify the query type: 'word', 'diff', or 'top'\n"
         << "  --word <WORD>            Specify target word for 'word' or 'diff' query\n"
         << "  --top <K>                Specify K value for 'top' query\n\n"
         << "Examples:\n"
         << "  analyzer --file data.txt --version v1 --query word --word search\n"
         << "  analyzer --file v1.txt --version1 V1 --file2 v2.txt --version2 V2 --query diff --word change\n"
         << "  analyzer --file data.txt --version v1 --query top --top 10\n";
}

int main(int argc, char* argv[]) {
    try {
        if (argc == 1) {  // If user provides no arguments it means he doesn't know how to use the program so we are printing help
            printHelp();
            return 0;
        }

        auto start_time = chrono::high_resolution_clock::now();

        string file1, file2, version1, version2, queryType, targetWord;
        int bufferSize = 256;
        int topK = 0;

        for (int i = 1; i < argc; i++) {
            string arg = argv[i];
            if (arg == "--help" || arg == "-h") {
                printHelp();
                return 0;
            } else if (arg == "--file" || arg == "--file1") {
                if (i + 1 < argc) file1 = argv[++i];
            } else if (arg == "--file2") {
                if (i + 1 < argc) file2 = argv[++i];
            } else if (arg == "--version" || arg == "--version1") {
                if (i + 1 < argc) version1 = argv[++i];
            } else if (arg == "--version2") {
                if (i + 1 < argc) version2 = argv[++i];
            } else if (arg == "--buffer") {
                if (i + 1 < argc) bufferSize = stoi(argv[++i]);
            } else if (arg == "--query") {
                if (i + 1 < argc) queryType = argv[++i];
            } else if (arg == "--word") {
                if (i + 1 < argc) {
                    targetWord = argv[++i];
                    for (char& c : targetWord) c = tolower(c);
                }
            } else if (arg == "--top") {
                if (i + 1 < argc) topK = stoi(argv[++i]);
            }
        }

        unique_ptr<QueryProcessor> processor;

        if (queryType == "word") {
            processor = make_unique<WordQuery>(targetWord);
            processor->addVersion(buildIndex(file1, version1, bufferSize));
        } else if (queryType == "diff") {
            processor = make_unique<DiffQuery>(targetWord);
            processor->addVersion(buildIndex(file1, version1, bufferSize));
            processor->addVersion(buildIndex(file2, version2, bufferSize));
        } else if (queryType == "top") {
            processor = make_unique<TopKQuery>(topK);
            processor->addVersion(buildIndex(file1, version1, bufferSize));
        } else {
            throw AnalyzerException("Unknown or missing query type");
        }

        processor->execute();

        cout << "Allocated buffer size: " << bufferSize << " KB\n";
        auto end_time = chrono::high_resolution_clock::now();
        chrono::duration<double> diff = end_time - start_time;
        cout << "Total execution time: " << diff.count() << " seconds\n";

    } catch (const std::exception& e) {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
