#ifndef GLOBALATTRIB
#define GLOBALATTRIB
#include <unordered_map>
#include <SDL_Headers.hpp>

const std::unordered_map<std::string, Uint8> keymap{
	{"S", SDL_SCANCODE_S}
};
#endif