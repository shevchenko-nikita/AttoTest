#include <iostream>

#include "file_generator.h"

int main()
{

    FileGenerator generator("test.txt", 1024 * 1024 * 1024);

    if(!generator.Generate())
    {
        std::cerr << "Failed to generate the file" << std::endl;
        return 1;
    }

    std::cout << "File was successfully generated" << std::endl;

    return 0;
}
