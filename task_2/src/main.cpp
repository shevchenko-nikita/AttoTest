#include "../include/file_sorter.h"
#include "../include/timer.h"

#include <iostream>

#include <windows.h>
#include <psapi.h>

int main(int argc, char* argv[])
{
    Timer timer;

    if(argc != 3)
    {
        std::cerr << "There should be three arguments" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];

    FileSorter sorter(inputFile, outputFile);

    if (!sorter.Sort())
    {
        std::cerr << "Can't sort file" << std::endl;
    }

    PROCESS_MEMORY_COUNTERS memInfo;
    GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo));
    std::cout << "Peak working set: " << memInfo.PeakWorkingSetSize / (1024 * 1024) << " MB\n";

    return 0;
}