#include "metadata.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL3/SDL.h>

#include <cairo/cairo.h>

#define clean(f) __attribute__ ((cleanup (f)))

int surface_width = 360;
int surface_height = 180;
int window_width = 1024;
int window_height = 512;

void
quit_sdl (bool *sdl_initialized)
{
  if (*sdl_initialized)
    {
      SDL_Quit ();
      *sdl_initialized = false;
      printf ("SDL quitted. %s\n", SDL_GetError ());
    }
}

void
destroy_window (SDL_Window **window)
{
  if (*window)
    {
      SDL_DestroyWindow (*window);
      *window = nullptr;
      printf ("window destroyed\n");
    }
}

void
destroy_renderer (SDL_Renderer **renderer)
{
  if (*renderer)
    {
      SDL_DestroyRenderer (*renderer);
      renderer = nullptr;
      printf ("renderer destroyed\n");
    }
}

void
destroy_texture (SDL_Texture **texture)
{
  if (*texture)
    {
      SDL_DestroyTexture (*texture);
      texture = nullptr;
      printf ("texture destroyed\n");
    }
}

void
destroy_surface (cairo_surface_t **surface)
{
  cairo_surface_destroy (*surface);
  *surface = nullptr;
  printf ("surface destroyed\n");
}

void
destroy_context (cairo_t **context)
{
  cairo_destroy (*context);
  *context = nullptr;
  printf ("context destroyed\n");
}

int
main_1 ()
{

  printf ("Welcome to GameTheGame\n");
  printf ("%s\n", SDL_GetRevision ());
  if (!set_app_metadata ())
    {
      fprintf (stderr, "!set_app_metadata()\n");
      return 1;
    }
  bool clean (quit_sdl) sdl_initialized = SDL_Init (SDL_INIT_VIDEO);
  if (!sdl_initialized)
    {
      fprintf (stderr, "!sdl_initialized\n");
      return 1;
    }
  SDL_Window *clean (destroy_window) window
    = SDL_CreateWindow ("GameTheGame", window_width, window_height, 0);
  if (!window)
    {
      fprintf (stderr, "!window\n");
      return 1;
    }
  SDL_Renderer *clean (destroy_renderer) renderer =
    SDL_CreateRenderer (window, nullptr);
  if (!renderer)
    {
      fprintf (stderr, "!renderer\n");
      return 1;
    }
  if (!SDL_SetRenderVSync (renderer, 2))
    {
      fprintf (stderr, "!SDL_SetRenderVSync(renderer, 2)\n");
      return 1;
    }
  SDL_Texture *clean (destroy_texture) texture =
    SDL_CreateTexture (renderer, SDL_PIXELFORMAT_ARGB32,
                       SDL_TEXTUREACCESS_STREAMING, surface_width,
                       surface_height);
  if (!texture)
    {
      fprintf (stderr, "!texture\n");
      return 1;
    }
  if (!SDL_SetTextureScaleMode (texture, SDL_SCALEMODE_NEAREST))
    {
      fprintf (stderr,
               "!SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST)\n");
      return 1;
    }
  cairo_surface_t *clean (destroy_surface) surface =
    cairo_image_surface_create (CAIRO_FORMAT_ARGB32, surface_width,
                                surface_height);
  if (cairo_surface_status (surface) != CAIRO_STATUS_SUCCESS)
    {
      fprintf (stderr,
               "cairo_surface_status(surface) != CAIRO_STATUS_SUCCESS\n");
      fprintf (stderr, "cairo_surface_status -> %s\n",
               cairo_status_to_string (cairo_surface_status (surface)));
      return 1;
    }
  cairo_t *clean (destroy_context) context = cairo_create (surface);
  if (cairo_status (context) != CAIRO_STATUS_SUCCESS)
    {
      fprintf (stderr, "cairo_status(context) != CAIRO_STATUS_SUCCESS\n");
      fprintf (stderr, "cairo_status -> %s\n",
               cairo_status_to_string (cairo_status (context)));
      return 1;
    }
  SDL_Rect rect = {.x = 0,.y = 0,.w = surface_width,.h = surface_height };
  SDL_FRect srcrect = {.x = 0,.y = 0,.w = surface_width,.h = surface_height };
  SDL_FRect dstrect = {.x = 0,.y = 0,.w = window_width,.h = window_height };
  bool running = true;
  while (running)
    {
      SDL_Event event;
      while (SDL_PollEvent (&event))
        {
          switch (event.type)
            {
            case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
              return 0;
              break;
            }
        }
      cairo_set_source_rgb (context, 1, 1, 1);
      cairo_rectangle (context, 0, 0, surface_width, surface_height);
      cairo_fill (context);
      cairo_set_source_rgb (context, 0, 0, 0);
      cairo_rectangle (context, 64, 32, 64, 32);
      cairo_fill (context);
      cairo_surface_flush (surface);
      void *surface_data = cairo_image_surface_get_data (surface);
      if (!surface_data)
        {
          fprintf (stderr, "!surface_data\n");
          return 1;
        }
      int stride = cairo_image_surface_get_stride (surface);
      if (!stride)
        {
          fprintf (stderr, "!stride\n");
          return 1;
        }
      int pitch;
      void *pixels;
      SDL_LockTexture (texture, &rect, &pixels, &pitch);
      if (stride == pitch)
        {
          memcpy (pixels, surface_data, stride * surface_height);
        }
      else
        {
          unsigned char *surfptr = surface_data;
          unsigned char *pixptr = pixels;
          for (size_t row = 0; row < surface_height; row++)
            {
              memcpy (pixptr, surfptr, surface_width * 4);
              pixptr += pitch;
              surfptr += stride;
            }
        }
      SDL_UnlockTexture (texture);
      // SDL_SetRenderDrawColorFloat(renderer, 0, 0, 0, 1);
      // SDL_RenderClear(renderer);
      SDL_RenderTexture (renderer, texture, &srcrect, &dstrect);
      SDL_RenderPresent (renderer);
    }
  return 0;
}

int
main ()
{
  return main_1 ();
}
