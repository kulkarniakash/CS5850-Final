#include <stdlib.h>
#include <string>

#include <iostream>
#include <SDL_Headers.hpp>

/*#if defined(MINGW) || defined(LINUX)
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#else
#include <SDL.h>
#include <SDL_opengl.h>
#endif*/

using namespace std;

const string fontPath = "assets/lazy.ttf";
const string imagePath = "assets/BGSky.jpg";
const string musicPath = "assets/bgmusic.wav";
TTF_Font* font = NULL;

 // otherwise we want to use OpenGL


int main(int argc, char* argv[])
{
	// Initialize SDL with video
	SDL_Init(SDL_INIT_VIDEO);

	// Create an SDL window
	SDL_Window* window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
	SDL_Renderer* gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// if failed to create a window
	if (!window)
	{
		// we'll print an error message and exit
		std::cerr << "Error failed to create window!\n";
		return 1;
	}

	// Create an OpenGL context (so we can use OpenGL functions)
	SDL_GLContext context = SDL_GL_CreateContext(window);

	// if we failed to create a context
	if (!context)
	{
		// we'll print out an error message and exit
		std::cerr << "Error failed to create a context\n!";
		return 2;
	}

	if (TTF_Init() < 0) {
		printf("SDL TTF error: could not initialize SDL_ttf\n");
		return -1;
	}

	font = TTF_OpenFont(fontPath.c_str(), 28);

	if (!font) {
		printf("SDL TTF error: could not load font\n");
		return -1;
	}

	SDL_Color tcolor = SDL_Color();
	tcolor.r = 200;
	tcolor.g = 150;
	tcolor.b = 60;
	SDL_Surface* txt_surf = TTF_RenderText_Solid(font, "This is a Test!", tcolor);
	SDL_Texture* txt_texture = SDL_CreateTextureFromSurface(gRenderer, txt_surf);

	SDL_Surface* image;
	SDL_RWops* rwop;
	
	rwop = SDL_RWFromFile(imagePath.c_str(), "rb");
	image = IMG_LoadJPG_RW(rwop);
	if (!image) {
		printf("SDL Image Error: could not load image\n");
	}

	SDL_Texture* img_texture = SDL_CreateTextureFromSurface(gRenderer, image);

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		exit(1);
	}

	Mix_Music* bgMusic = Mix_LoadMUS(musicPath.c_str());

	if (Mix_PlayingMusic() == 0) {
		//Play the music
		Mix_VolumeMusic(30);
		Mix_PlayMusic(bgMusic, -1);
	}

	SDL_Event event;	 // used to store any events from the OS
	bool running = true; // used to determine if we're running the game

	// glClearColor(1, 0, 0, 1);
	while (running)
	{
		// poll for events from SDL
		while (SDL_PollEvent(&event))
		{
			// determine if the user still wants to have the window open
			// (this basically checks if the user has pressed 'X')
			running = event.type != SDL_QUIT;
		}

		
		// glClear(GL_COLOR_BUFFER_BIT);
		SDL_SetRenderDrawColor(gRenderer, 0x0, 0x0, 0x0, 0xFF);
		SDL_RenderClear(gRenderer);

		SDL_RenderCopy(gRenderer, img_texture, NULL, NULL);
		SDL_RenderCopy(gRenderer, txt_texture, NULL, NULL);
		SDL_RenderPresent(gRenderer);

		// Swap OpenGL buffers
		// SDL_GL_SwapWindow(window);
	}

	TTF_CloseFont(font);
	TTF_Quit();

	// Destroy the context
	SDL_GL_DeleteContext(context);

	// Destroy the window
	SDL_DestroyWindow(window);

	// And quit SDL
	SDL_Quit();

	return 0;
}
