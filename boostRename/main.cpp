#include <iostream>
#include "boost/filesystem.hpp"

namespace fs = boost::filesystem;

int main()
{
    fs::rename("rtb/testFile", "rotated/testFile");
    if(!fs::exists("tempFile.txt"))
    {
	std::cout << "tempFile.txt does not exist" << std::endl;
    }
    else
    {
	std::cout << "tempFile.txt does exist" << std::endl;
    }
}
