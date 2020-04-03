#include <stdio.h>
#include <stdlib.h>

#include "NOIOVideoFairy.h"
#include "NOIOAudioFairy.h"
#include "NOIOGamepadFairy.h"
#include "../../emulator/VirtualMachine.h"

int main(int argc, char **argv)
{
  if (argc <= 1) {
    printf("Plase input file\n");
    return -1;
  }

  NOIOVideoFairy videoFairy;
  NOIOAudioFairy audioFairy;
  NOIOGamepadFairy player1;

  VirtualMachine vm(videoFairy, audioFairy, &player1, NULL);
  vm.loadCartridge(argv[1]);
  vm.sendHardReset();

  while(true) {
    vm.run();
  }

  return 0;
}

