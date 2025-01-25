#include "metadata.h"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_version.h>
#include <SDL3/SDL_video.h>

int main() {
  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Welcome to GameTheGame\n");
  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%s\n", SDL_GetRevision());
  if (!SetAppMetadata()) {
    goto exit;
  }
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    goto exit;
  }
  SDL_Window *window = SDL_CreateWindow("GameTheGame", 1280, 720, 0);
  if (!window) {
    goto quitSDL;
  }
  SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);
  if (!renderer) {
    goto cleanupWindow;
  }
  bool running = true;
  while (running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
        goto exitGameLoop;
        break;
      }
    }
    SDL_SetRenderDrawColorFloat(renderer, 0, 0, 0, 1);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
  }
exitGameLoop:
cleanupWindow:
  SDL_DestroyWindow(window);
quitSDL:
  SDL_Quit();
exit:
  SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s\n", SDL_GetError());
}