#include <SDL2/SDL.h>

class SoundWave {
public:
  SoundWave (SDL_Renderer*, int, int, int);
  void drawWave (SDL_Color);
  void drawWave (SDL_Color, int, int);
  void drawDoubleWave (SDL_Color, SDL_Color);
  SoundWave& operator=(const SoundWave&);
private:
  SDL_Renderer* renderer;
  int width;
  int maxAmp;
  int center;
  int heightOdds[20];
  const int span = 6;
  const int evenOrOdd[2] = {-1, 1};
};
