#include "../include/batch_controller.h"

#include <filesystem>
#include <iostream>
#include <queue>

BatchStream::BatchStream()
: curValue(0)
{
}

bool BatchCmp::operator()(
        const std::shared_ptr<BatchStream>& lhs,
        const std::shared_ptr<BatchStream>& rhs)
{
    return lhs->curValue > rhs->curValue;
}

bool BatchStream::OpenFile(const std::string& fileName)
{
    file.open(fileName, std::ios::binary);
    if(!file.is_open())
    {
        return false;
    }

    return ReadNext();
}

bool BatchStream::ReadNext()
{
    return file.is_open() && file.read(reinterpret_cast<char*>(&curValue), sizeof(double));
}

BatchController::BatchController()
: batchCount(0)
{
    CreateTempDirectory("temp_dir");
}

BatchController::~BatchController()
{
    RemoveTempDirectory();
}

bool BatchController::WriteData(const std::vector<double> &data)
{
    batchCount += 1;

    std::string path = GetFilePath(batchCount);
    std::ofstream batchFile(path, std::ios::binary);

    if(!batchFile.is_open())
    {
        return false;
    }

    for(const auto& val : data)
    {
        if(!batchFile.write(reinterpret_cast<const char*>(&val), sizeof(val)))
        {
            return false;
        }
    }

    return true;
}

bool BatchController::MergeFiles(const std::string &targetFileName)
{
    std::ofstream out(targetFileName);
    if(!out.is_open())
    {
        return false;
    }

    std::priority_queue<
            std::shared_ptr<BatchStream>,
            std::vector<std::shared_ptr<BatchStream>>,
            BatchCmp> batches;

    for(int i = 1; i <= batchCount; ++i)
    {
        std::string path = GetFilePath(i);

        auto batchStream = std::make_shared<BatchStream>();
        if(batchStream->OpenFile(path))
        {
            batches.push(std::move(batchStream));
        }
    }

    while(!batches.empty())
    {
        auto top = batches.top();
        batches.pop();

        out << top->curValue << '\n';

        if(top->ReadNext())
        {
            batches.push(top);
        }
    }

    return true;
}

std::string BatchController::GetFilePath(int id) const
{
    return tempDirName + "/batch_" + std::to_string(id) + ".bin";
}

void BatchController::CreateTempDirectory(const std::string &dirName)
{
    tempDirName = dirName;
    try
    {
        std::filesystem::create_directory(tempDirName);
    }
    catch(const std::exception& ex)
    {
        std::cerr << "ERROR: " << ex.what() << std::endl;
    }
}

void BatchController::RemoveTempDirectory()
{
    try
    {
        std::filesystem::remove_all(tempDirName);
    }
    catch(std::exception& ex)
    {
        std::cerr << "ERROR: " << ex.what() << std::endl;
    }
}