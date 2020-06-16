#include <iostream>
#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;


string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}


string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}


// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}


float LinuxParser::MemoryUtilization() {
    std::ifstream stream(kProcDirectory + kMeminfoFilename);
    int i = 0;
    float mem_total, mem_free;
    if (stream.is_open()) {
        std::string line;
        std::string key, value, kb;

        while(std::getline(stream, line)) {
            std::replace(line.begin(), line.end(), ':', ' ');

            std::istringstream linestream(line);

            while (linestream >> key >> value >> kb) {
                if (key == "MemTotal") {
                    mem_total = std::stof(value);
                    i++;
                }
                if (key == "MemFree") {
                    mem_free = std::stof(value);
                    i++;
                }

                // once we have both, no need to proceed further
                if (i==2) {
                    return (mem_total - mem_free) / mem_total;
                }
            }
        }
    }

    return 0.0;
}


long LinuxParser::UpTime() {
    std::ifstream stream(kProcDirectory + kUptimeFilename);
    std::string line, s_uptime, s_idletime;
    long uptime;

    if (stream.is_open()) {
        std::getline(stream, line);
        std::istringstream linestream(line);

        while (linestream >> s_uptime >> s_idletime) {
            uptime = std::stol(s_uptime);
        }

        return uptime;
    }
    return 0.0;
}


long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }


long LinuxParser::ActiveJiffies() {
    vector<string> cpuvalues = CpuUtilization();

    long user = std::stol(cpuvalues[0]);
    long nice = std::stol(cpuvalues[1]);
    long system = std::stol(cpuvalues[2]);
    long irq = std::stol(cpuvalues[5]);
    long softirq = std::stol(cpuvalues[6]);
    long steal = std::stol(cpuvalues[7]);

    return user + nice + system + irq + softirq + steal;
}


long LinuxParser::IdleJiffies() {
    vector<string> cpuvalues = CpuUtilization();

    /*
     * 0 user
     * 1 nice
     * 2 system
     * 3 idle
     * 4 iowait
     * 5 irq
     * 6 softirq
     * 7 steal
     * 8 guest
     * 9 guestnice
     */

    long idle = std::stol(cpuvalues[3]);
    long iowait = std::stol(cpuvalues[4]);

    return idle + iowait;
}


vector<string> LinuxParser::CpuUtilization() {

    std::string line;
    std::string key;
    std::vector<std::string> cpuvalues;

    std::ifstream stream(kProcDirectory + kStatFilename);

    if (stream.is_open()) {
        // aggregated cpu info is in first line
        std::getline(stream, line);

        std::istringstream linestream(line);

        while(linestream >> key) {
            if (key != "cpu") {
                cpuvalues.push_back(key);
            }
        }

        return cpuvalues;
    }

    return cpuvalues;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
    // we have a file to read from /proc/stat
    // the key is processes
    // value is an int number after a space after processes

    std::ifstream stream(kProcDirectory + kStatFilename);

    if (stream.is_open()) {
        std::string line;
        std::string key, value;

        while (std::getline(stream, line)) {
            std::istringstream linestream(line);

            while(linestream >> key >> value) {
                if (key == "processes") {
                    return std::stoi(value);
                }
            }
        }
    }
    return 0;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
    std::ifstream stream(kProcDirectory + kStatFilename);

    if (stream.is_open()) {
        std::string line;
        std::string key, value;

        while (std::getline(stream, line)) {
            std::istringstream linestream(line);

            while(linestream >> key >> value) {
                if (key == "procs_running") {
                    return std::stoi(value);
                }
            }
        }
    }

    return 0;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }
