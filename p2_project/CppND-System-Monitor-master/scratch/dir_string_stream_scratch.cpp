#include <iostream>
#include <istream>
#include <string>
#include <fstream>

int main(void)
{
    std::ifstream myfile ("/proc/version");

    if (myfile.is_open())
    {
        std::cout << "open" << std::endl;
        std::string line;
        std::getline(myfile, line);

        std:: cout << line << std::endl;
    }

    return 0;
}
