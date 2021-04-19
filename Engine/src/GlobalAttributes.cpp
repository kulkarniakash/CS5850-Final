#include <unordered_map>
#include <SDL_Headers.hpp>
#include "GlobalAttributes.hpp"

const std::unordered_map<std::string, Uint8> keymap({
	{"A", SDL_SCANCODE_A},
	{"S", SDL_SCANCODE_S},
	{"D", SDL_SCANCODE_D},
	{"W", SDL_SCANCODE_W}
});

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;