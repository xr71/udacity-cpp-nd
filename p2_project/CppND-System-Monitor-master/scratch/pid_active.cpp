#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

int main(void)
{
    int pid = 203;

    std::vector<std::string>  values ;
    long utime,stime,cutime,cstime;

    std::ifstream stream("/proc/203/stat");

    if (stream.is_open()) {
        std::string line;
        std::string key;

        std::getline(stream, line);
        std::istringstream linestream(line);

        std::cout << line << std::endl;

        while(linestream >> key) {
             values.push_back(key);
        }

    }

    utime=stol(values[13]);
    stime=stol(values[14]);
    cutime=stol(values[15]);
    cstime=stol(values[16]);

    return utime+stime+cutime+cstime;

}
