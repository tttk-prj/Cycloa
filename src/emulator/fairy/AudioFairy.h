#ifndef __AUDIOFAIRY_H__
#define __AUDIOFAIRY_H__
/*
 * AudioFairy.h
 *
 *  Created on: 2011/08/28
 *      Author: psi
 */

// #include <algorithm>
#include <stdint.h>
#include <string.h>

class AudioFairy {
private:
  enum {
#ifdef ORIGINAL_CYCLOA
    INTERNAL_BUFFER_SIZE = 0x40000,
#else
    INTERNAL_BUFFER_SIZE = 0x400,
#endif
  };
  int16_t soundBuffer[INTERNAL_BUFFER_SIZE];
  int lastIndex;
  int firstIndex;
public:
  AudioFairy()
  :lastIndex(0)
  ,firstIndex(0)
  {
    memset(soundBuffer, 0, INTERNAL_BUFFER_SIZE);
  }

  virtual ~AudioFairy() {};

  inline bool pushAudio(int16_t sound) {
    const int nowFirstIndex = firstIndex;
    const int available =
        nowFirstIndex > lastIndex ? nowFirstIndex - lastIndex - 1
                                  : INTERNAL_BUFFER_SIZE - (lastIndex - nowFirstIndex) - 1;
    if (available > 0) {
      soundBuffer[lastIndex] = sound;
      lastIndex = (lastIndex + 1) & (INTERNAL_BUFFER_SIZE - 1);
      return true;
    } else {
      return false;
    }
  }

protected:
  inline int popAudio(int16_t *buff, int maxLength) {
    const int nowLastIndex = lastIndex;
    const int available =
        firstIndex <= nowLastIndex ? nowLastIndex - firstIndex : INTERNAL_BUFFER_SIZE - (firstIndex - nowLastIndex);
    // const int copiedLength = std::min<int>(available, maxLength);
    const int copiedLength = (available > maxLength) ? maxLength : available;
    if (firstIndex + copiedLength < INTERNAL_BUFFER_SIZE) {
      memcpy(buff, &soundBuffer[firstIndex], sizeof(int16_t) * copiedLength);
      firstIndex += copiedLength;
    } else {
      const int first = INTERNAL_BUFFER_SIZE - firstIndex;
      const int last = copiedLength - first;
      memcpy(buff, &soundBuffer[firstIndex], sizeof(int16_t) * first);
      memcpy(&buff[first], &soundBuffer[0], sizeof(int16_t) * last);
      firstIndex = last;
    }

    return copiedLength;
  }
};

class DummyAudioFairy : public AudioFairy {

};
#endif  // __AUDIOFAIRY_H__
