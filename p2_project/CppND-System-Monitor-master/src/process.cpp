#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
    long active_time, up_time;

    active_time = LinuxParser::ActiveJiffies(pid_);
    up_time = LinuxParser::UpTime(pid_);

    return (float)active_time / (float)up_time;
}

string Process::Command() {
    return LinuxParser::Command(pid_);
}

string Process::Ram() {
    return LinuxParser::Ram(pid_);
}

string Process::User() {
    return LinuxParser::User(pid_);
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return 0; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }
