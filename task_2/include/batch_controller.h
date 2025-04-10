#pragma once

#include <fstream>
#include <memory>
#include <vector>

struct BatchStream
{
    BatchStream();

    bool OpenFile(const std::string& fileName);
    bool ReadNext();

    std::ifstream file;
    double curValue;
};

struct BatchCmp
{
    bool operator()(
            const std::shared_ptr<BatchStream>& lhs,
            const std::shared_ptr<BatchStream>& rhs);
};

class BatchController
{
public:
    BatchController();
    ~BatchController();

    bool WriteData(const std::vector<double>& data);
    bool MergeFiles(const std::string& targetFileName);
    std::string GetFilePath(int id) const;

private:
    void CreateTempDirectory(const std::string& dirName);
    void RemoveTempDirectory();

    std::string tempDirName;
    int batchCount;
};