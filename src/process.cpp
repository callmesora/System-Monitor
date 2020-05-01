#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include "linux_parser.h"
#include "process.h"
#include "processor.h"
#include <iostream>

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
  long activejiffies = LinuxParser::ActiveJiffies(pid_);
  long processuptime= LinuxParser::UpTime(pid_);
  long systemuptime= LinuxParser::UpTime();
  long seconds= systemuptime - processuptime ;
 

  if (seconds != 0){
  return static_cast<float>((float)activejiffies/(float)seconds); }
   //Ask Mentor is this is how static_cast works
  //https://stackoverflow.com/questions/16726779/how-do-i-get-the-total-cpu-usage-of-an-application-from-proc-pid-stat/16736599#16736599

  else {
    return 0.0;
  }
  }
// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid_); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
  
  return (this->cpu_proc_utilization_>a.cpu_proc_utilization_); }