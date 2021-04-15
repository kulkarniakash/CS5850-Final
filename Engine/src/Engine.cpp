// pybind taken from Akash's and Kimin's lab
#include <Engine.hpp>
#include "ResourceManager.hpp"

const std::string fontPath = "assets/lazy.ttf";
const std::string imagePath = "assets/BGSky.jpg";
const std::string musicPath = "assets/bgmusic.wav";

bool running = true; // used to determine if we're running the game

SDL_Event event; // used to store any events from the OS

Engine::Engine()
{
}

// Proper shutdown and destroy initialized objects
Engine::~Engine()
{
}

int Engine::InitializeGraphicsSubSystem()
{
    // Initialize SDL with video
    SDL_Init(SDL_INIT_VIDEO);
	SDL_Renderer* gRenderer = NULL;

	if (ResourceManager::getInstance().addWindow("window", "The Team", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL)) {
		printf("Error: Could not load window\n");
		return -1;
	}

    // Create an SDL window
    // window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
	SDL_Window* window = ResourceManager::getInstance().getResourceSDLWindow("window");
    gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	

    // if failed to create a window
    /*if (!window)
    {
        // we'll print an error message and exit
        std::cerr << "Error failed to create window!\n";
        return 1;
    }*/

    if (TTF_Init() < 0)
    {
        printf("SDL TTF error: could not initialize SDL_ttf\n");
        return -1;
    }

   /* font = TTF_OpenFont(fontPath.c_str(), 28);

    if (!font)
    {
        printf("SDL TTF error: could not load font\n");
        return -1;
    }*/

   

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        exit(1);
    }

   
	if (ResourceManager::getInstance().addRenderer("gRenderer", gRenderer)) {
		printf("Error: Could not load renderer\n");
		return -1;
	}

	if (ResourceManager::getInstance().addJPG(imagePath, "gRenderer")) {
		printf("Error: Could not load background image\n");
		return -1;
	}

	if (ResourceManager::getInstance().addResource("assets/bgmusic.wav", ResourceType::BackgroundMusic)) {
		printf("Error: Could not load background music\n");
		return -1;
	}

	if (ResourceManager::getInstance().addResource(fontPath, ResourceType::Font, 40)) {
		printf("Error: Could not load font\n");
		return -1;
	}

	

    return 0;
}

void Engine::Input()
{
    while (SDL_PollEvent(&event))
    {
        // determine if the user still wants to have the window open
        // (this basically checks if the user has pressed 'X')
        running = event.type != SDL_QUIT;
    }
}

void Engine::Render()
{
	SDL_Texture* bgimage = ResourceManager::getInstance().getResourceSDLTexture(imagePath.c_str());
	TTF_Font* font = ResourceManager::getInstance().getResourceFont(fontPath);
	SDL_Renderer* gRenderer = ResourceManager::getInstance().getResourceSDLRenderer("gRenderer");
	SDL_Color tcolor = SDL_Color();
	tcolor.r = 200;
	tcolor.g = 150;
	tcolor.b = 60;
	SDL_Surface* txt_surf = TTF_RenderText_Solid(font, "This is a Test!", tcolor);
	SDL_Texture* txt_texture = SDL_CreateTextureFromSurface(gRenderer, txt_surf);

    SDL_SetRenderDrawColor(gRenderer, 0x0, 0x0, 0x0, 0xFF);
    SDL_RenderClear(gRenderer);

	SDL_RenderCopy(gRenderer, bgimage, NULL, NULL);
    SDL_RenderCopy(gRenderer, txt_texture, NULL, NULL);
    SDL_RenderPresent(gRenderer);

	SDL_DestroyTexture(txt_texture);
	SDL_FreeSurface(txt_surf);
}

void Engine::MainGameLoop()
{
	Mix_Music* bgMusic = ResourceManager::getInstance().getResourceBackgroundMusic(musicPath);
	if (Mix_PlayingMusic() == 0)
	{
		//Play the music
		Mix_VolumeMusic(30);
		Mix_PlayMusic(bgMusic, -1);
	}

    while (running)
    {
        Input();

        Render();
    }
}

void Engine::Start()
{
	SDL_Renderer* gRenderer = ResourceManager::getInstance().getResourceSDLRenderer("gRenderer");
    if (gRenderer != nullptr)
    {
        std::cout << "Initializing Graphics Subsystem\n";
    }
    else
    {
        std::cout << "No Graphics Subsystem initialized\n";
    }
}

void Engine::Shutdown()
{
    // TTF_CloseFont(font);
    TTF_Quit();

    // Destroy the context
    //SDL_GL_DeleteContext(context);

    // Destroy the window
    // SDL_DestroyWindow(window);

    // And quit SDL
    SDL_Quit();
}



// Include the pybindings
#include <pybind11/pybind11.h>

namespace py = pybind11;


// NOTE: the following code has not been tested!! It most likely won't work 
// but just serves as a template

// Creates a macro function that will be called
// whenever the module is imported into python
// 'mygameengine' is what we 'import' into python.
// 'm' is the interface (creates a py::module object)
//      for which the bindings are created.
//  The magic here is in 'template metaprogramming'
PYBIND11_MODULE(Engine, m) {
	m.doc() = "our game engine as a library"; // Optional docstring
	py::class_<Engine>(m, "Engine")
		.def(py::init<>())   // our constructor
		.def("input", &Engine::Input) // Expose member methods
		.def("render", &Engine::Render)
		.def("main_game_loop", &Engine::MainGameLoop)
		.def("start", &Engine::Start)
		.def("shutdown", &Engine::Shutdown)
		.def("initialize_graphics_subsystem", &Engine::InitializeGraphicsSubSystem);
	// We do not need to expose everything to our users!
	//            .def("getSDLWindow", &SDLGraphicsProgram::getSDLWindow, py::return_value_policy::reference) 
}

