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

int Process::Pid() { return pid_; }


float Process::CpuUtilization() const {
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

long int Process::UpTime() {
    return LinuxParser::UpTime(pid_);
}

bool Process::operator<(Process const& a) const {

    return  (CpuUtilization() - a.CpuUtilization()) < 0;
}

