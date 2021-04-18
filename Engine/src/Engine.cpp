// pybind taken from Akash's and Kimin's lab
//Engine class taken from Sumanth's assignment-2, written by Shreyas Shivashankar
#include <Engine.hpp>

const std::string fontPath = "assets/lazy.ttf";
const std::string imagePath = "assets/BGSky.jpg";
const std::string musicPath = "assets/bgmusic.wav";

TTF_Font *font = NULL;
SDL_Color tcolor;

SDL_Surface *txt_surf = NULL;
SDL_Texture *txt_texture = NULL;

SDL_Surface *image;
SDL_RWops *rwop;

SDL_Texture *img_texture = NULL;

Mix_Music *bgMusic = NULL;

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

bool running = true; // used to determine if we're running the game

SDL_Event event; // used to store any events from the OS

Engine::Engine()
{
}

// Proper shutdown and destroy initialized objects
Engine::~Engine()
{
}

void Engine::InitializeGraphicsSubSystem()
{
    this->renderer = new GraphicsEngineRenderer(SCREEN_WIDTH, SCREEN_HEIGHT);

    if (nullptr == renderer) {
        exit(1);
    }

    font = TTF_OpenFont(fontPath.c_str(), 28);

    if (!font)
    {
        printf("SDL TTF error: could not load font\n");
    }

    tcolor = SDL_Color();
    tcolor.r = 200;
    tcolor.g = 150;
    tcolor.b = 60;
    txt_surf = TTF_RenderText_Solid(font, "This is a Test!", tcolor);
    txt_texture = SDL_CreateTextureFromSurface(renderer->GetRenderer(), txt_surf);

    rwop = SDL_RWFromFile(imagePath.c_str(), "rb");
    image = IMG_LoadJPG_RW(rwop);
    if (!image)
    {
        printf("SDL Image Error: could not load image\n");
    }

    img_texture = SDL_CreateTextureFromSurface(renderer->GetRenderer(), image);

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        exit(1);
    }

    bgMusic = Mix_LoadMUS(musicPath.c_str());

    if (Mix_PlayingMusic() == 0)
    {
        //Play the music
        Mix_VolumeMusic(30);
        Mix_PlayMusic(bgMusic, -1);
    }
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
    // // glClear(GL_COLOR_BUFFER_BIT);
    // SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
    // SDL_RenderClear(renderer);

    // SDL_RenderCopy(renderer, img_texture, NULL, NULL);
    // SDL_RenderCopy(renderer, txt_texture, NULL, NULL);
    // SDL_RenderPresent(renderer);

    renderer->SetRenderDrawColor(0x0, 0x0, 0x0, 0xFF);
    renderer->RenderClear();
    SDL_RenderCopy(renderer->GetRenderer(), img_texture, NULL, NULL);
    SDL_RenderCopy(renderer->GetRenderer(), txt_texture, NULL, NULL);
    renderer->RenderPresent();
}

void Engine::MainGameLoop()
{
    while (running)
    {
        Input();

        Render();
    }
}

void Engine::Start()
{
    if (renderer != nullptr)
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
    delete renderer;
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

