#ifndef GLOBALATTRIB
#define GLOBALATTRIB
#include <unordered_map>
#include <SDL_Headers.hpp>

extern const std::unordered_map<std::string, Uint8> keymap;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
#endif