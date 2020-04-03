#pragma once
/*
 * SDLVideoFairy.h
 *
 *  Created on: 2011/08/23
 *      Author: psi
 */

#include <SDL.h>
#include <string>
#include "../../emulator/VirtualMachine.h"
#include "../../emulator/fairy/VideoFairy.h"

class SDLVideoFairy : public VideoFairy {
public:
  explicit SDLVideoFairy(
      std::string const &windowTitle,
      int width = Video::screenWidth * 2,
      int height = Video::screenHeight * 2);

  ~SDLVideoFairy();

  uint8_t * dispatchRendering(const uint8_t (*nesBuffer)[screenWidth], const uint8_t paletteMask);

  int getWidth() {
    return this->width;
  }

  int getHeight() {
    return this->width;
  }

  uint8_t *getScreenBuffer()
  {
    return (uint8_t *)renderBuff;
  }

private:
  const int width;
  const int height;
  bool isFullscreen;
  uint32_t nextTime;

  uint32_t fpsTime;
  uint32_t fpsCnt;
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *tex;

  uint8_t renderBuff[screenHeight][screenWidth];

protected:
  void dispatchRenderingImpl(const uint8_t (*nesBuffer)[screenWidth], uint8_t paletteMask,
                             SDL_Renderer *renderer, SDL_Texture *tex);
};
