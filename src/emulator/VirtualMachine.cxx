#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include "VirtualMachine.h"

VirtualMachine::VirtualMachine(VideoFairy &videoFairy, AudioFairy &audioFairy, GamepadFairy *player1,
                               GamepadFairy *player2) :
    ram(*this),
    processor(*this),
    audio(*this, audioFairy),
    video(*this, videoFairy),
    cartridge(NULL),
    ioPort(*this, player1, player2),
    clockDelta(0),
    resetFlag(false),
    hardResetFlag(false),
    irqLine(0) {
  //ctor

  total_processor_time = 0;
  total_video_time = 0;
  total_cartridge_time = 0;
  total_audio_time = 0;
}

VirtualMachine::~VirtualMachine() {
  if (this->cartridge != NULL) {
    delete this->cartridge;
  }
}

void VirtualMachine::run() {
  if (this->hardResetFlag) {
    this->clockDelta = 0;
    this->hardResetFlag = false;

    this->processor.onHardReset();

    this->cartridge->onHardReset();

    this->video.onHardReset();

    this->audio.onHardReset();

    return;
  } else if (this->resetFlag) {
    this->clockDelta = 0;
    this->resetFlag = false;

    this->processor.onReset();

    this->cartridge->onReset();

    this->video.onReset();

    this->audio.onReset();

    return;
  }

  PERFORMANCE_INIT();
  const int32_t cpuClockDelta = this->clockDelta / CPU_CLOCK_FACTOR;
  const int32_t videoClockDelta = this->clockDelta / VIDEO_CLOCK_FACTOR;
  this->clockDelta = 0;

  PERFORMANCE_START();
  this->processor.run(cpuClockDelta);
  PERFORMANCE_END(total_processor_time);

  PERFORMANCE_START();
  this->video.run(videoClockDelta);
  PERFORMANCE_END(total_video_time);

  PERFORMANCE_START();
  this->cartridge->run(cpuClockDelta);
  PERFORMANCE_END(total_cartridge_time);

  PERFORMANCE_START();
  this->audio.run(cpuClockDelta);
  PERFORMANCE_END(total_audio_time);

}

void VirtualMachine::doReport() {
  printf(" TotalProcessor:%d, TotalVideo:%d, TotalCartridge:%d, TotalAudio:%d\n",
          total_processor_time,
          total_video_time,
          total_cartridge_time,
          total_audio_time);
        
  total_processor_time = 0;
  total_video_time = 0;
  total_cartridge_time = 0;
  total_audio_time = 0;
}

void VirtualMachine::consumeClock(uint32_t clock) {
  this->clockDelta += clock;
}

void VirtualMachine::sendVBlank() {
  this->ioPort.onVBlank();
}

void VirtualMachine::sendNMI() {
  this->processor.sendNMI();
}

void VirtualMachine::reserveIRQ(uint8_t device) {
  this->irqLine |= device;
  this->processor.reserveIRQ();
}

void VirtualMachine::releaseIRQ(uint8_t device) {
  this->irqLine &= ~(device);
  if (irqLine == 0) {
    this->processor.releaseIRQ();
  }
}

bool VirtualMachine::isIRQpending(uint8_t device) {
  return (irqLine & device) == device;
}

void VirtualMachine::sendHardReset() {
  this->hardResetFlag = true;
}

void VirtualMachine::sendReset() {
  this->resetFlag = true;
}

namespace {

struct cartridge_data * readAllFromFile(const char *fileName) {
  struct stat ss;
  stat(fileName, &ss);
  int fileSize = ss.st_size;
  FILE *const file = fopen(fileName, "rb");
  if (!file) {
    EXCEPTION_THROW("Error to open file %s : (%d)\n", fileName, errno);
  }
  struct cartridge_data *dat = new cartridge_data;
  dat->data = new uint8_t[fileSize];
  dat->size = fileSize;
  size_t readed = fread(dat->data, 1, fileSize, file);
  if (readed < fileSize) {
    fclose(file);
    EXCEPTION_THROW("Error to read all contents from the file %s : (%d)\n", fileName, errno);
  }
  fclose(file);
  return dat;
}

}

void VirtualMachine::loadCartridge(const char * filename) {
  VirtualMachine::loadCartridge(readAllFromFile(filename), filename);
}

void VirtualMachine::loadCartridge(struct cartridge_data * data, const char *name) {
  if(this->cartridge) {
    delete this->cartridge;
  }
  this->cartridge = Cartridge::loadCartridge(*this, data, name);
  this->video.connectCartridge(this->cartridge);
}
