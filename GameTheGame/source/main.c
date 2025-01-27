#include "metadata.h"

#include <SDL3/SDL_error.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_version.h>
#include <SDL3/SDL_video.h>

#include <cairo/cairo.h>

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define clean(f) __attribute__((cleanup(f)))

int surface_width = 360;
int surface_height = 180;
int window_width = 1024;
int window_height = 512;

void
ejemplo ()
{
  void clean1 (void *ptr)
  {
    printf ("Destroying 1\n");
  }
  void clean2 (void *ptr)
  {
    printf ("Destroying 2\n");
  }
  int clean (clean1) a;
  int clean (clean2) b;
}

int
main_1 ()
{
  void destroy_window (SDL_Window ** window)
  {
    if (*window)
      {
        SDL_DestroyWindow (*window);
      }
    SDL_Quit ();
  }
  printf ("Welcome to GameTheGame\n");
  printf ("%s\n", SDL_GetRevision ());
  if (!set_app_metadata ())
    {
      fprintf (stderr, "!set_app_metadata()\n");
      goto exit;
    }
  if (!SDL_Init (SDL_INIT_VIDEO))
    {
      fprintf (stderr, "!SDL_Init(SDL_INIT_VIDEO)\n");
      goto exit;
    }
  SDL_Window *clean (destroy_window) window =
    SDL_CreateWindow ("GameTheGame", window_width, window_height, 0);
  if (!window)
    {
      fprintf (stderr, "!window\n");
      goto exit;
    }
  SDL_Renderer *renderer = SDL_CreateRenderer (window, nullptr);
  if (!renderer)
    {
      fprintf (stderr, "!renderer\n");
      goto exit;
    }
  if (!SDL_SetRenderVSync (renderer, 2))
    {
      fprintf (stderr, "!SDL_SetRenderVSync(renderer, 2)\n");
      goto destroy_renderer;
    }
  SDL_Texture *texture = SDL_CreateTexture (renderer, SDL_PIXELFORMAT_ARGB32,
                                            SDL_TEXTUREACCESS_STREAMING,
                                            surface_width, surface_height);
  if (!texture)
    {
      fprintf (stderr, "!texture\n");
      goto destroy_renderer;
    }
  if (!SDL_SetTextureScaleMode (texture, SDL_SCALEMODE_NEAREST))
    {
      fprintf (stderr,
               "!SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST)\n");
      goto destroy_texture;
    }
  cairo_surface_t *surface =
    cairo_image_surface_create (CAIRO_FORMAT_ARGB32, surface_width,
                                surface_height);
  if (cairo_surface_status (surface) != CAIRO_STATUS_SUCCESS)
    {
      fprintf (stderr,
               "cairo_surface_status(surface) != CAIRO_STATUS_SUCCESS\n");
      goto destroy_surface;
    }
  cairo_t *context = cairo_create (surface);
  if (cairo_status (context) != CAIRO_STATUS_SUCCESS)
    {
      fprintf (stderr, "cairo_status(context) != CAIRO_STATUS_SUCCESS\n");
      goto destroy_context;
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
              goto exit_game_loop;
              break;
            }
        }
      // cairo_set_line_width(context, 0);
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
          goto exit_game_loop;
        }
      int stride = cairo_image_surface_get_stride (surface);
      if (!stride)
        {
          fprintf (stderr, "!stride\n");
          goto exit_game_loop;
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
exit_game_loop:
  fprintf (stderr, "cairo_surface_status -> %s\n",
           cairo_status_to_string (cairo_surface_status (surface)));
  fprintf (stderr, "cairo_status -> %s\n",
           cairo_status_to_string (cairo_status (context)));
destroy_context:
  cairo_destroy (context);
destroy_surface:
  cairo_surface_destroy (surface);
destroy_texture:
  SDL_DestroyTexture (texture);
destroy_renderer:
  SDL_DestroyRenderer (renderer);
exit:
  fprintf (stderr, "SDL_GetError -> %s\n", SDL_GetError ());
  return 0;
}

int
main ()
{
  ejemplo ();
  return main_1 ();
}
