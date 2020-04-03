#ifndef __VIDEOFAIRY_H__
#define __VIDEOFAIRY_H__
/*
 * VideoFairy.h
 *
 *  Created on: 2011/08/23
 *      Author: psi
 */

#include <stdint.h>

#include "../../../../video_config.h"

class VideoFairy {
public:
  enum {
    screenWidth = 256,
    screenHeight = 240
  };
  // static const uint32_t nesPaletteARGB[64];

  explicit VideoFairy() {}

  virtual ~VideoFairy() {}

  virtual uint8_t *dispatchRendering(const uint8_t (*nesBuffer)[screenWidth], const uint8_t paletteMask) = 0;
};

class DummyVideoFairy : public VideoFairy {
public:
  explicit DummyVideoFairy() {}

  virtual ~DummyVideoFairy() {}
};
#endif  // __VIDEOFAIRY_H__
