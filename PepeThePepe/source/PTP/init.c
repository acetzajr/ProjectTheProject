#include "PTP/init.h"

#include "PTP/state.h"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_version.h>

bool PTP_init() {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    PTP_SDLError = true;
    return false;
  }
  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%s\n", SDL_GetRevision());
  return true;
}

void PTP_quit() {
  if (PTP_SDLError) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s\n", SDL_GetError());
  }
  SDL_Quit();
}