#include "soundWave.h"
#include <iostream>
#include <ctime>

SoundWave::SoundWave (SDL_Renderer* r, int w, int maxA, int cent) : renderer(r), width(w), maxAmp(maxA), center(cent),
  heightOdds {0, 0, 0, 0, 0, (int)(maxAmp/16.0), (int)(maxAmp/8.0), (int)(maxAmp/4.0), (int)(5*maxAmp/16.0),
    (int)(3*maxAmp/8.0), (int)(maxAmp/2.0), (int)(9*maxAmp/16.0), (int)(5*maxAmp/8.0), (int)(11*maxAmp/16.0),
    (int)(11*maxAmp/16.0), (int)(3*maxAmp/4.0), 0, (int)(3*maxAmp/8.0), (int)(7*maxAmp/8.0), maxAmp} {

    std::srand(std::time(nullptr));
}

void SoundWave::drawWave (SDL_Color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  int plusAmp = 0, oldAmp = 0;
  int i = 0;
  while (i < width) {
    oldAmp = plusAmp;

    if (plusAmp == 0) {
      if (std::rand()%6 == 0) {
        plusAmp = heightOdds[std::rand()%20] * evenOrOdd[std::rand()%2];
      }
    }
    else {
      plusAmp = heightOdds[std::rand()%20] * evenOrOdd[std::rand()%2];
      if (plusAmp == 0) {
        if (std::rand()%6 != 0)
          plusAmp = heightOdds[std::rand()%20] * evenOrOdd[std::rand()%2];
      }
    }
    SDL_RenderDrawLine(renderer, i, center-oldAmp, i+span-1, center-plusAmp);
    i += span;
  }
}

void SoundWave::drawDoubleWave (SDL_Color color1, SDL_Color color2) {
  int plusAmp = 0, oldAmp = 0;
  int i = 0;
  while (i < width) {
    oldAmp = plusAmp;

    if (plusAmp == 0) {
      if (std::rand()%6 == 0) {
        plusAmp = heightOdds[std::rand()%20] * evenOrOdd[std::rand()%2];
      }
    }
    else {
      plusAmp = heightOdds[std::rand()%20] * evenOrOdd[std::rand()%2];
      if (plusAmp == 0) {
        if (std::rand()%6 != 0)
          plusAmp = heightOdds[std::rand()%20] * evenOrOdd[std::rand()%2];
      }
    }
    SDL_SetRenderDrawColor(renderer, color1.r, color1.g, color1.b, color1.a);
    SDL_RenderDrawLine(renderer, i, center-oldAmp, i+span-1, center-plusAmp);
    SDL_SetRenderDrawColor(renderer, color2.r, color2.g, color2.b, color2.a);
    SDL_RenderDrawLine(renderer, i+10, center-oldAmp+10, i+span-1+10, center-plusAmp+10);
    i += span;
  }
}

void SoundWave::drawWave (SDL_Color color, int maxA, int cent) {
  maxAmp = maxA;
  center = cent;
  drawWave(color);
}

SoundWave& SoundWave::operator=(const SoundWave& sw) {
  if (this != &sw) {
    renderer = sw.renderer;
    width = sw.width;
    maxAmp = sw.maxAmp;
    center = sw.center;
    for (int i = 0; i < 20; i++) {
      heightOdds[i] = sw.heightOdds[i];
    }
  }
  return *this;
}
