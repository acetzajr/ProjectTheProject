#include "PTP/init.h"

#include "PTP/state.h"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_version.h>
#include <glib-2.0/glib.h>

bool PTP_init() {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    PTP_SDLError = true;
    return false;
  }
  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%s\n", SDL_GetRevision());
  GArray *array;
  int i;

  // We create a new array to store int values.
  // We don't want it zero-terminated or cleared to 0's.
  array = g_array_new(FALSE, FALSE, sizeof(int));

  for (i = 0; i < 10000; i++) {
    g_array_append_val(array, i);
  }

  for (i = 0; i < 10000; i++) {
    if (g_array_index(array, int, i) != i)
      g_print("ERROR: got %d instead of %d\n", g_array_index(array, int, i), i);
  }

  g_array_free(array, TRUE);
  return true;
}

void PTP_quit() {
  if (PTP_SDLError) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s\n", SDL_GetError());
  }
  SDL_Quit();
}