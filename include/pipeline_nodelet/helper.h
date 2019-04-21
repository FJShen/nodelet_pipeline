#include <chrono>

inline void print_time_stamp(std::string comment="na"){
  std::cout<< comment<<" "<<std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count()<<"\t";
}
