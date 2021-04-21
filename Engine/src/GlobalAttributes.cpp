#include <unordered_map>
#include <SDL_Headers.hpp>
#include "GlobalAttributes.hpp"

const std::unordered_map<std::string, Uint8> keymap({
	{"A", SDLK_a},
	{"S", SDLK_s},
	{"D", SDLK_d},
	{"W", SDLK_w}
});

const std::unordered_map<Uint8, std::string> keymapinv({
	{SDLK_a, "A"},
	{SDLK_s, "S"},
	{SDLK_d, "D"},
	{SDLK_w, "W"}
});

const Uint8* keystate = SDL_GetKeyboardState(NULL);

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;