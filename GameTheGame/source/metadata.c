#include "metadata.h"

#include <SDL3/SDL_init.h>

bool
set_app_metadata ()
{
  if (!SDL_SetAppMetadataProperty (SDL_PROP_APP_METADATA_NAME_STRING,
                                   "GameTheGame"))
    return false;
  if (!SDL_SetAppMetadataProperty (SDL_PROP_APP_METADATA_VERSION_STRING,
                                   "1.0.0"))
    return false;
  if (!SDL_SetAppMetadataProperty (SDL_PROP_APP_METADATA_IDENTIFIER_STRING,
                                   "org.acetzajr.gamethegame"))
    return false;
  if (!SDL_SetAppMetadataProperty (SDL_PROP_APP_METADATA_CREATOR_STRING,
                                   "acetzajr"))
    return false;
  if (!SDL_SetAppMetadataProperty (SDL_PROP_APP_METADATA_COPYRIGHT_STRING,
                                   "Copyright (c) 2025 acetzajr"))
    return false;
  if (!SDL_SetAppMetadataProperty (SDL_PROP_APP_METADATA_URL_STRING,
                                   "https://github.com/acetzajr"))
    return false;
  if (!SDL_SetAppMetadataProperty (SDL_PROP_APP_METADATA_TYPE_STRING, "game"))
    return false;
  return true;
}
