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
#ifndef MULTI_CPU_VIDEO_RENDERER
  static const uint16_t nesPaletteRGB565[64];
#endif

  explicit VideoFairy() {}

  virtual ~VideoFairy() {}

#ifdef RENDER_BY_LINE
  virtual void dispatchLineRendering(int line_no, const uint8_t * const linebuff, const uint8_t paletteMask){};
#endif
  virtual void dispatchRendering(const uint8_t (&nesBuffer)[screenHeight][screenWidth], const uint8_t paletteMask) = 0;
};

class DummyVideoFairy : public VideoFairy {
public:
  explicit DummyVideoFairy() {}

  virtual ~DummyVideoFairy() {}
};
#endif  // __VIDEOFAIRY_H__
