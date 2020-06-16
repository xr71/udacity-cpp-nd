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

long LinuxParser::ActiveJiffies(int pid) {

    std::vector<string> values;
    long utime,stime,cutime,cstime;

    std::ifstream stream(kProcDirectory + "/" + std::to_string(pid) + kStatFilename);

    if (stream.is_open()) {
        std::string line;
        std::string key;
        std::getline(stream, line);

        std::istringstream linestream(line);
        while(linestream >> key) {
            values.push_back(key);
        }
    }

    utime=stol(values[13]);
    stime=stol(values[14]);
    cutime=stol(values[15]);
    cstime=stol(values[16]);

    /* std::cout << utime << stime << cutime << cstime << std::endl; */

    return utime + stime + cutime + cstime;
}


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


// individual PID related section //

string LinuxParser::Command(int pid) {
    std::ifstream stream(kProcDirectory + "/" + std::to_string(pid) + kCmdlineFilename);

    if (stream.is_open()) {
        std::string line;
        std::string key, value;

        std::getline(stream, line);

        return line;
    }

    return " ";
}

string LinuxParser::Ram(int pid) {
    std::string key, value;

    // there is a key called VmSize that we can use to get mem usage of a pid

    std::ifstream stream(kProcDirectory + "/" + std::to_string(pid) + kStatusFilename);

    if (stream.is_open()) {
        // loop over lines looking for vmSize
        std::string line;

        while(std::getline(stream, line)) {
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream linestream(line);

            while (linestream >> key >> value) {
                if (key == "VmSize") {
                    // we need to covert the value to MB
                    long mb_value = std::stol(value) / 1024;

                    return std::to_string(mb_value);
                }
            }
        }
    }

    return " ";
}

// Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) {

    std::ifstream stream(kProcDirectory + "/" + std::to_string(pid) + kStatusFilename);

    // looking for key Uid

    if(stream.is_open()) {
        std::string line;
        std::string key, value;

        while(std::getline(stream, line)) {
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream linestream(line);

            while(linestream >> key >> value) {
                if (key == "Uid") {
                    return value;
                }
            }
        }
    }

    return " ";
}

string LinuxParser::User(int pid) {
    std::string uid = Uid(pid);

    // we are looking in the /etc/passwd path

    std::ifstream stream(kPasswordPath);

    if (stream.is_open()) {
        // each line is in the format of u:x:id...

        std::string line;
        std::string uname, key, value;


        while (std::getline(stream, line)) {
            std::replace(line.begin(), line.end(), ':', ' ');

            std::istringstream linestream(line);

            while (linestream >> uname >> key >> value) {

                if (value == uid) {
                    return uname;
                }
            }
        }
    }

    return " ";
}

long LinuxParser::UpTime(int pid) {

    long start_time, up_time;

    std::ifstream stream(kProcDirectory + "/" + std::to_string(pid) + kStatFilename);
    if (stream.is_open()) {
        std::string line,value,kPidDirectory;
        std::getline(stream, line);
        std::istringstream linestream(line);
        for (int count = 0; count < 22; count++) {
            linestream >> value ;
        }

    start_time = std::stol(value) / sysconf(_SC_CLK_TCK);

    up_time = UpTime() -start_time;

    return up_time;
    }

    return 0.0;
}
