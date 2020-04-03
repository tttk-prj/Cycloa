#ifndef __NOIO_GAMEPAD_FAIRY_H__
#define __NOIO_GAMEPAD_FAIRY_H__

#include "../../emulator/fairy/GamepadFairy.h"

class NOIOGamepadFairy : public GamepadFairy {
public:
  NOIOGamepadFairy();
  ~NOIOGamepadFairy();

  void onVBlank();
  void onUpdate();
  bool isPressed(uint8_t keyIdx);
};


#endif  // __NOIO_GAMEPAD_FAIRY_H__
