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
using std::stold;

// DONE: An example of how to read data from the filesystem
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

// DONE: An example of how to read data from the filesystem
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

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  string line;
  string key;
  string value;
  float totalmem;
  float freemem;
  std::ifstream stream(kMeminfoFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "MemTotal") {
          totalmem = stof(value);
        } else if (key == "MemFree") {
          freemem = stof(value);
        }
      }
    }
  }
  return ((totalmem - freemem)/totalmem);

  // return 0.0;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  string line;
  string value, value2;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> value >> value2;
    return std::stol(value);
    
  }
  return 0;
  // return 0;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() {
  long sec = LinuxParser::UpTime();
  long jiffie = sec * sysconf(_SC_CLK_TCK);
  return jiffie;

  // return 0;
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) {
  
  std::ifstream filestream(kProcDirectory+std::to_string(pid) +kStatFilename);
  string line;
  string temp;
  long v13, v14, v15,v16;
  if (filestream.is_open()){
    std::getline(filestream,line);
    std::istringstream linestream(line);

    for (int i=13; i<=16;i++) {
      linestream>>temp;
      if (i==13) {
        v13 = std::stol(temp);}
      if (i==14) {
        v14 = std::stol(temp);
    }
    if (i==15) {
        v15 = std::stol(temp);
  }
  if (i==16) {
        v16 = std::stol(temp);}
    }
  }
  return ((v13+v14+v15+v16 )/sysconf(_SC_CLK_TCK)); //ASk Mentor is I should divide here
}
    

  // return 0;


// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() {
  std::ifstream stream(kProcDirectory + kStatFilename);
  vector<string> value;
  long sum = 0;
  string line;

  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    for (int i = 1; i < 11; i++) {
      linestream >> value[i];
    }
  }
  for (int i = 0; i < 10; i++) {
    sum += stoll(value[i], nullptr, 10);

    // return 0;
  }
  return sum;
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() {
  std::ifstream stream(kProcDirectory + "stat");
  string line;
  string key;
  string value1;
  string value2;
  string value3;
  string value4;
  string value5;
  string value6;
  string value7;
  string value8;
  string value9;
  string value10;
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> key >> value1 >> value2 >> value3 >> value4 >> value5 >>
        value6 >> value7 >> value8 >> value9 >> value10;
    
  }
return (stol(value4) + stol(value5));
  // return 0;
}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  std::vector<string> vec_jiffies;
  string line;
  string key;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    while (linestream >> key) {
      if (key != "cpu") {
        vec_jiffies.push_back(key);
      }
    }
    
  }
return vec_jiffies;
  // return {};
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          return stoi(value);
        }
      }
    }
  }
  return 0;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {
          return stoi(value);
        }
      }
    }
  }
  return 0;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  std::ifstream filestream(kProcDirectory+std::to_string(pid) +kCmdlineFilename);
  string line;
  string cmdline;
  if (filestream.is_open()){
    std::getline(filestream,line);
    cmdline=line;
  }
  return cmdline; 
  }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  string line;
  string value;
  string key;
  std::ifstream filestream(kProcDirectory+to_string(pid)+kStatusFilename) ;
    if (filestream.is_open()) {
      while (std::getline(filestream,line)) {
        std::replace(line.begin(),line.end(),':',' ');
        std::istringstream linestream(line);
        while (linestream>>key>>value){
          if( key=="VmSize") {
            return value;
          }
        }
      }
    }
  }
 

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  string line;
  string value;
  string key;
  std::ifstream filestream(kProcDirectory+to_string(pid)+kStatusFilename) ;
    if (filestream.is_open()) {
      while (std::getline(filestream,line)) {
        std::replace(line.begin(),line.end(),':',' ');
        std::istringstream linestream(line);
        while (linestream>>key>>value){
          if( key=="Uid") {
            return value;
          }
        }
      }
    }
 }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {
  string uid = LinuxParser::Uid(pid);
  string line;
  string name;
  string value;
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream,line)){
      std::replace(line.begin(),line.end(),':',' ');
      std::replace(line.begin(),line.end(), 'x',' ');
      std::istringstream linestream(line);
      while (linestream >> name >> value){
        if (value==uid){
          return name;
        }
      }
    }
  return string();} 
 }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
  std::ifstream filestream(kProcDirectory+std::to_string(pid) +kStatFilename);
  string line;
  string temp;
  long uptime;
  if (filestream.is_open()){
    std::getline(filestream,line);
    std::istringstream linestream(line);

    for (int i=0; i<=21;i++) {
      linestream>>temp;
      if (i==21) {
        uptime = std::stol(temp);

      }
    }
  }
  return uptime;
  }

