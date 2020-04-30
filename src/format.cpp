#include <string>
#include <iomanip>
#include <sstream>
#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    

    long hour= seconds/3600;
    long min= seconds/60;
    long sec= seconds;

    std::ostringstream stream;
  stream << std::setw(2) << std::setfill('0') << hour << ":" 
     << std::setw(2) << std::setfill('0') << min << ":"
     << std::setw(2) << std::setfill('0') << sec;
  return stream.str();


    //https://stackoverflow.com/questions/48310746/converting-time-into-hours-minutes-and-seconds
 }