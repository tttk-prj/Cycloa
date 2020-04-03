#ifndef __SPRESENSE_PORT_H__
#define __SPRESENSE_PORT_H__

#include <stdio.h>

#define EXCEPTION_THROW(...)  do{ \
  printf(__VA_ARGS__);  \
  while(1); \
}while(0)

struct cartridge_data {
  uint8_t *data;
  int size;
};

class VirtualMachine;

class IF_VM {
public:
  IF_VM() : vm(NULL){};
  ~IF_VM() {};

  void setVM(VirtualMachine *v) { vm = v; };
  void doReport();

  VirtualMachine *vm;
};

#ifdef PERFORMANCE_CHECK
#define PERFORMANCE_INIT()  struct timeval start_time, end_time
#define PERFORMANCE_START() gettimeofday(&start_time, NULL)
#define PERFORMANCE_END(val) do { \
    gettimeofday(&end_time, NULL);  \
    val += (end_time.tv_sec  - start_time.tv_sec ) * 1000000L + \
           (end_time.tv_usec - start_time.tv_usec); \
  }while(0)
#else
#define PERFORMANCE_INIT()
#define PERFORMANCE_START()
#define PERFORMANCE_END(val)
#endif


#endif  // __SPRESENSE_PORT_H__
