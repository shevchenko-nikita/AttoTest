#include "../include/file_sorter.h"

#include <algorithm>
#include <vector>

FileSorter::FileSorter(const std::string& inputFile, const std::string& outputFile)
: originFileName(inputFile), targetFileName(outputFile), batchController()
{
}

bool FileSorter::Sort()
{
    if(!SplitFile())
    {
        return false;
    }

    return batchController.MergeFiles(targetFileName);
}

bool FileSorter::SplitFile()
{
    std::fstream in(originFileName);

    if(!in.is_open())
    {
        return false;
    }

    std::vector<double> buffer;
    buffer.reserve(BATCH_SIZE);

    while(!in.eof())
    {
        double val;
        in >> val;

        buffer.push_back(val);

        if(buffer.size() >= BATCH_SIZE)
        {
            std::sort(std::begin(buffer), std::end(buffer));

            if(!batchController.WriteData(buffer))
            {
                return false;
            }

            buffer.clear();
        }
    }

    if(!buffer.empty())
    {
        std::sort(std::begin(buffer), std::end(buffer));
        if (!batchController.WriteData(buffer))
        {
            return false;
        }

        buffer.clear();
    }

    in.close();

    return true;
}