#include "processor.h"
#include "linux_parser.h"
#include <iostream>


// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
    long idle = LinuxParser::IdleJiffies();
    long nonidle = LinuxParser::ActiveJiffies();
    long total = idle + nonidle;

    return (float)nonidle / (float)total;
}
