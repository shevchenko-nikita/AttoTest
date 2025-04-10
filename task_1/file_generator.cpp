#include "file_generator.h"

#include <iostream>
#include <sstream>

FileGenerator::FileGenerator(const std::string &filename_, uint32_t targetFileSize_)
: filename(filename_), targetFileSize(targetFileSize_)
{
    std::random_device rd;
    randomEng.seed(rd());
    distr = std::uniform_real_distribution<double>(
            std::numeric_limits<double>::min(),
            std::numeric_limits<double>::max());
}

bool FileGenerator::Generate()
{
    std::ofstream out(filename, std::ios::binary);

    if(!out.is_open())
    {
        return false;
    }

    uint32_t curFileSize = 0;
    std::uniform_int_distribution<int> distSign(0, 1);

    while(curFileSize < targetFileSize)
    {
        double randVal = distr(randomEng);
        int signType = distSign(randomEng);

        randVal *= (signType == 0) ? 1 : -1;

        std::stringstream str;
        str << randVal << '\n';

        auto data = str.str();
        curFileSize += data.size();
        out << data;
    }

    return true;
}