#pragma once

#include "batch_controller.h"

class FileSorter {
public:
    FileSorter(const std::string& inputFile, const std::string& outputFile);
    bool Sort();

private:
    bool SplitFile();

    std::string originFileName;
    std::string targetFileName;

    BatchController batchController;

    const uint32_t BATCH_SIZE = 1000000;
};