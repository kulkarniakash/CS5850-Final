#ifndef SDLHEADERS
#define SDLHEADERS
#if defined(LINUX) || defined(MINGW)
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_mixer.h>
	#include <SDL2/SDL_ttf.h>
	#include <SDL2/SDL_image.h>
#else // This works for Mac
	#include <SDL.h>
	#include <SDL_mixer.h>
	#include <SDL_ttf.h>
	#include <SDL_image.h>
#endif
#endif
