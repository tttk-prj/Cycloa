#ifndef __SPRESENSE_PORT_H__
#define __SPRESENSE_PORT_H__

#include <stdio.h>

#define EXCEPTION_THROW(...)  do{ \
  printf(__VA_ARGS__);  \
  while(1); \
}while(0)

#endif  // __SPRESENSE_PORT_H__
