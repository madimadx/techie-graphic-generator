#include <SDL2/SDL.h>
#include "frameGenerator.h"
#include "soundWave.h"
#include <iostream>

const std::string NAME = "mmaddox";
const int WIDTH = 960;
const int HEIGHT = 540;


void drawCircle(SDL_Renderer* renderer, SDL_Point center, int radius, SDL_Color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  for (int w = 0; w < radius * 2; w++) {
    for (int h = 0; h < radius * 2; h++) {
      int dx = radius - w; // horizontal offset
      int dy = radius - h; // vertical offset
      if ((dx*dx + dy*dy) <= (radius * radius)) {
        SDL_RenderDrawPoint(renderer, center.x + dx, center.y + dy);
      }
    }
  }
}

void drawCircleGradient(SDL_Renderer* renderer, SDL_Point center, int radius, SDL_Color color1, SDL_Color color2) {
  int rDiff, grDiff, bDiff, aDiff;
  float rInc, grInc, bInc, aInc;
  rDiff = color2.r - color1.r;
  grDiff = color2.g - color1.g;
  bDiff = color2.b - color1.b;
  aDiff = color2.a - color1.a;
  rInc = rDiff/(double)(radius*2);
  grInc = grDiff/(double)(radius*2);
  bInc = bDiff/(double)(radius*2);
  aInc = aDiff/(double)(radius*2);
  for (int w = 0 ; w < radius * 2; w++) {
    SDL_SetRenderDrawColor(renderer, color1.r+(int)(w*rInc), color1.g+(int)(w*grInc), color1.b+(int)(w*bInc), color1.a+(int)(w*aInc));
    for (int h = 0; h < radius * 2; h++) {
      int dx = radius - w; // horizontal offset
      int dy = radius - h; // vertical offset
      if ((dx*dx + dy*dy) <= (radius * radius)) {
        SDL_RenderDrawPoint(renderer, center.x + dx, center.y + dy);
      }
    }
  }
}

void drawCircleGradientWithBars(SDL_Renderer* renderer, SDL_Point center, int radius, SDL_Color color1, SDL_Color color2) {
  int rDiff, grDiff, bDiff, aDiff;
  float rInc, grInc, bInc, aInc;
  int interv = (int)radius/4.0;
  rDiff = color2.r - color1.r;
  grDiff = color2.g - color1.g;
  bDiff = color2.b - color1.b;
  aDiff = color2.a - color1.a;
  rInc = rDiff/(double)(radius*2);
  grInc = grDiff/(double)(radius*2);
  bInc = bDiff/(double)(radius*2);
  aInc = aDiff/(double)(radius*2);
  for (int w = 0 ; w < radius * 2; w++) {
    for (int h = 0; h < radius * 2; h++) {
      if (h % interv <= interv/2)
        SDL_SetRenderDrawColor(renderer, color1.r+(int)(w*rInc), color1.g+(int)(w*grInc), color1.b+(int)(w*bInc), 0);
      else
        SDL_SetRenderDrawColor(renderer, color1.r+(int)(w*rInc), color1.g+(int)(w*grInc), color1.b+(int)(w*bInc), color1.a+(int)(w*aInc));
      int dx = radius - w; // horizontal offset
      int dy = radius - h; // vertical offset
      if ((dx*dx + dy*dy) <= (radius * radius)) {
        SDL_RenderDrawPoint(renderer, center.x + dx, center.y + dy);
      }
    }
  }
}

void drawCircleGradientWithBarsInverse(SDL_Renderer* renderer, SDL_Point center, int radius, SDL_Color color1, SDL_Color color2) {
  int rDiff, grDiff, bDiff, aDiff;
  float rInc, grInc, bInc, aInc;
  int interv = (int)radius/4.0;
  rDiff = color2.r - color1.r;
  grDiff = color2.g - color1.g;
  bDiff = color2.b - color1.b;
  aDiff = color2.a - color1.a;
  rInc = rDiff/(double)(radius*2);
  grInc = grDiff/(double)(radius*2);
  bInc = bDiff/(double)(radius*2);
  aInc = aDiff/(double)(radius*2);
  for (int w = 0 ; w < radius * 2; w++) {
    for (int h = 0; h < radius * 2; h++) {
      if (h % interv >= interv/2)
        SDL_SetRenderDrawColor(renderer, color1.r+(int)(w*rInc), color1.g+(int)(w*grInc), color1.b+(int)(w*bInc), 0);
      else
        SDL_SetRenderDrawColor(renderer, color1.r+(int)(w*rInc), color1.g+(int)(w*grInc), color1.b+(int)(w*bInc), color1.a+(int)(w*aInc));
      int dx = radius - w; // horizontal offset
      int dy = radius - h; // vertical offset
      if ((dx*dx + dy*dy) <= (radius * radius)) {
        SDL_RenderDrawPoint(renderer, center.x + dx, center.y + dy);
      }
    }
  }
}

void drawTripleCircleGradientWithBars(SDL_Renderer* renderer, SDL_Point center, int radius, SDL_Color color1, SDL_Color color2) {
  int rDiff, grDiff, bDiff, aDiff;
  float rInc, grInc, bInc, aInc;
  int interv = (int)(radius/4.0);
  rDiff = color2.r - color1.r;
  grDiff = color2.g - color1.g;
  bDiff = color2.b - color1.b;
  aDiff = color2.a - color1.a;
  rInc = rDiff/(float)(radius*2)*2;
  grInc = grDiff/(float)(radius*2)*2;
  bInc = bDiff/(float)(radius*2)*2;
  aInc = aDiff/(float)(radius*2)*2;
  for (int w = 0, split = 0; w < radius * 2; w++) {
    if (w < radius)
      split++;
    else if (w >= radius)
      split--;
    for (int h = 0; h < radius * 2; h++) {
      if (h % interv <= interv/2)
        SDL_SetRenderDrawColor(renderer, color1.r+(int)(rInc*split), color1.g+(int)(grInc*split), color1.b+(int)(bInc*split), 0);
      else
        SDL_SetRenderDrawColor(renderer, color1.r+(int)(rInc*split), color1.g+(int)(grInc*split), color1.b+(int)(bInc*split), (color1.a+(int)(aInc*split))*3/8);
      int dx = radius - w; // horizontal offset
      int dy = radius - h; // vertical offset
      if ((dx*dx + dy*dy) <= (radius * radius)) {
        SDL_RenderDrawPoint(renderer, center.x + dx, center.y + dy);
      }
    }
  }
}

void drawFillCouch(SDL_Renderer* renderer, SDL_Color colorLine, SDL_Color colorFill) {
  SDL_Rect leg1, leg2, leg3, bottomBar, leftCush, rightCush, leftArm, rightArm, leftPill, rightPill;

  leg1.x = 275;
  leg2.x = 475;
  leg3.x = 675;
  leg1.y = leg2.y = leg3.y = 490;
  leg1.w = leg2.w = leg3.w = 10;
  leg1.h = leg2.h = leg3.h = 20;

  bottomBar.x = 250;
  bottomBar.y = 480;
  bottomBar.w = 460;
  bottomBar.h = 10;

  leftCush.x = leftArm.x = 240;
  leftCush.y = 440;
  leftCush.w = rightCush.w = 240;
  leftCush.h = rightCush.h = 40;

  rightCush.x = rightPill.x = 480;
  rightCush.y = 440;

  leftArm.y = rightArm.y = 390;
  leftArm.w = rightArm.w = 40;
  leftArm.h = rightArm.h = 50;
  rightArm.x = 680;

  leftPill.x = 280;
  leftPill.y = rightPill.y = 320;
  leftPill.w = rightPill.w = 200;
  leftPill.h = rightPill.h = 120;

  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

  SDL_SetRenderDrawColor(renderer, colorFill.r, colorFill.g, colorFill.b, colorFill.a);
  SDL_RenderFillRect(renderer, &leg1);
  SDL_RenderFillRect(renderer, &leg2);
  SDL_RenderFillRect(renderer, &leg3);
  SDL_RenderFillRect(renderer, &bottomBar);
  SDL_RenderFillRect(renderer, &leftCush);
  SDL_RenderFillRect(renderer, &rightCush);
  SDL_RenderFillRect(renderer, &leftArm);
  SDL_RenderFillRect(renderer, &rightArm);
  SDL_RenderFillRect(renderer, &leftPill);
  SDL_RenderFillRect(renderer, &rightPill);

  SDL_SetRenderDrawColor(renderer, colorLine.r, colorLine.g, colorLine.b, colorLine.a);
  SDL_RenderDrawRect(renderer, &leg1);
  SDL_RenderDrawRect(renderer, &leg2);
  SDL_RenderDrawRect(renderer, &leg3);
  SDL_RenderDrawRect(renderer, &bottomBar);
  SDL_RenderDrawRect(renderer, &leftCush);
  SDL_RenderDrawRect(renderer, &rightCush);
  SDL_RenderDrawRect(renderer, &leftArm);
  SDL_RenderDrawRect(renderer, &rightArm);
  SDL_RenderDrawRect(renderer, &leftPill);
  SDL_RenderDrawRect(renderer, &rightPill);
}

void colorBackground(SDL_Renderer* renderer, SDL_Color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_Rect bkgrd;
  bkgrd.x = 0;
  bkgrd.y = 0;
  bkgrd.w = WIDTH;
  bkgrd.h = HEIGHT;
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SDL_RenderFillRect(renderer, &bkgrd);
}

int main(void) {
  SDL_Renderer *renderer;
  SDL_Window *window;

  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer( WIDTH, HEIGHT, 0, &window, &renderer );

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255 );
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

  SDL_Color red = {255,0,0,255};
  SDL_Color blue = {0,0,255,255};
  SDL_Color yellow = {255, 215, 0, 255};
  SDL_Color black = {0, 0, 0, 255};
  SDL_Color yellowDark = {63, 53, 0, 255};

  colorBackground(renderer, black);
  drawTripleCircleGradientWithBars(renderer, {480, 400}, 420, blue, red);
  drawFillCouch(renderer, yellow, yellowDark);

  int maxAmp = 110;
  int soundCenter = 140;
  SoundWave boomBoom = SoundWave(renderer, WIDTH, maxAmp, soundCenter);
  boomBoom.drawDoubleWave(red, blue);

  SDL_RenderPresent(renderer);
  FrameGenerator frameGen(renderer, window, WIDTH, HEIGHT, NAME);
  frameGen.makeFrame();

  SDL_Event event;
  const Uint8* keystate;
  while ( true ) {
    keystate = SDL_GetKeyboardState(0);
    if (keystate[SDL_SCANCODE_ESCAPE]) { break; }
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        break;
      }
    }
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return EXIT_SUCCESS;
}
