#include <iostream>
#include <sstream>
#include <fstream>
#include <string>


int main(void)
{
    std::ifstream stream("/proc/stat");

    if (stream.is_open())
    {
        std::string line;
        std::getline(stream, line);

        std::cout << line << std::endl;

        // the first line gets us the aggregate cpu info
        // we need to tokenize

        /*
         * user: normal processes executing in user mode
           nice: niced processes executing in user mode
           system: processes executing in kernel mode
           idle: twiddling thumbs
           iowait: In a word, iowait stands for waiting for I/O to complete. But there are several problems:
           Cpu will not wait for I/O to complete, iowait is the time that a task is waiting for I/O to complete. When cpu goes into idle state for outstanding task io, another task will be scheduled on this CPU.
           In a multi-core CPU, the task waiting for I/O to complete is not running on any CPU, so the iowait of each CPU is difficult to calculate.
           The value of iowait field in /proc/stat will decrease in certain conditions. So, the iowait is not reliable by reading from /proc/stat.
           irq: servicing interrupts
           softirq: servicing softirqs
           steal: involuntary wait
           guest: running a normal guest
           guest_nice: running a niced guest
        */

        std::string key;
        std::string user, nice, system, irq, softirq, steal;
        std::string idle, iowait;

        int total_nonidle, total_idle, total_cpu;

        std::istringstream linestream(line);

        linestream >> key >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;
        std::cout << user << std::endl;
        std::cout << nice << std::endl;
        std::cout << system << std::endl;
        std::cout << idle << std::endl;
        std::cout << iowait << std::endl;
        std::cout << irq << std::endl;
        std::cout << softirq << std::endl;
        std::cout << steal << std::endl;

        total_nonidle = std::stoi(user) + std::stoi(nice) + std::stoi(system) + std::stoi(irq) + std::stoi(softirq) + std::stoi(steal);
        total_idle = std::stoi(idle) + std::stoi(iowait);
        total_cpu = total_nonidle + total_idle;

        std::cout << total_nonidle << "  " << total_idle << "  " << total_cpu << std::endl;

        float cpu_util;
        cpu_util = (float)total_nonidle / (float)total_cpu;

        std::cout << cpu_util << std::endl;
    }
}
