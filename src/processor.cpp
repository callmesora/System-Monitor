#include "processor.h"
#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"


using std::stof;
using std::string;
using std::to_string;
using std::vector;
using std::stoi;
using std::stol;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    vector<string>  keys = LinuxParser::CpuUtilization();
    float user = std::stof(keys[0]);
    float nice = std::stof(keys[1]);
    float system = std::stof(keys[2]);
    float idle = std::stof(keys[3]);
    float iowait = std::stof(keys[4]);
    float irq = std::stof(keys[5]);
    float softirq = std::stof(keys[6]);
    float steal = std::stof(keys[7]);
    float guest = std::stof(keys[8]);

    float PrevIdle = 0.0;
    float Idle = idle + iowait;

    float PrevNonIdle =0.0;
    float NonIdle = user + nice + system + irq + softirq + steal;

    float PrevTotal = 0.0;
    float Total = Idle + NonIdle;

    //# differentiate: actual value minus the previous one
    float totald = Total - PrevTotal;
    float idled = Idle - PrevIdle;

    float CPU_Percentage = (totald - idled)/totald;

    return CPU_Percentage; }
    // I considered Prev = 0 
    //https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux/23376195#23376195