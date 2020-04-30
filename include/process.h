#ifndef PROCESS_H
#define PROCESS_H
#include <linux_parser.h>
#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid) : pid_(pid){
    
    cpu_ram_utilization_= std::stol(LinuxParser::Ram(pid_));
    cpu_proc_utilization_=Process::CpuUtilization();
  }
    
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  // TODO: Declare any necessary private members
 private:
    int pid_;
    float cpu_proc_utilization_;
    long cpu_ram_utilization_;
};

#endif