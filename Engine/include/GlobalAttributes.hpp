#ifndef GLOBALATTRIB
#define GLOBALATTRIB
#include <unordered_map>
#include <SDL_Headers.hpp>
#include <string>

extern const std::unordered_map<std::string, Uint8> keymap;
extern const std::unordered_map<Uint8, std::string> keymapinv;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern const Uint8* keystate;

#endif
