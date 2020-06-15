#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

int main(void)
{
    std::ifstream stream("/proc/uptime");

    if (stream.is_open())
    {
        std::string line;
        std::getline(stream, line);
        long uptime;
        std::string s_uptime, s_idletime;

        std::cout << line << std::endl;

        std::istringstream linestream(line);

        while (linestream >> s_uptime >> s_idletime)
        {
            uptime = std::stol(s_uptime);
        }

        std::cout << uptime << std::endl;
    }
    else
    {
        return 1;
    }
}
