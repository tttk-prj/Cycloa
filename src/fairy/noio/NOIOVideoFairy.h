#ifndef __NOIO_VIDEO_FAIRY_H__
#define __NOIO_VIDEO_FAIRY_H__


#include "../../emulator/fairy/VideoFairy.h"

class NOIOVideoFairy : public VideoFairy {
public:
  NOIOVideoFairy();
  ~NOIOVideoFairy();
  void dispatchRendering(const uint8_t (&nesBuffer)[screenHeight][screenWidth], const uint8_t paletteMask);
};


#endif  // __NOIO_VIDEO_FAIRY_H__
