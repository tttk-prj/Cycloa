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

#endif  // __SPRESENSE_PORT_H__
