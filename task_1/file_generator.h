#pragma once

#include <fstream>
#include <random>

class FileGenerator
{
public:
    FileGenerator(const std::string& filename_, uint32_t targetFileSize_);

    bool Generate();
private:
    uint32_t targetFileSize; // number of bytes
    std::string filename;

    std::mt19937 randomEng;
    std::uniform_real_distribution<double> distr;
};