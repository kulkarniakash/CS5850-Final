// pybind taken from Akash's and Kimin's lab
//Engine class taken from Sumanth's assignment-2, written by Shreyas Shivashankar
//frame capping taken from Danny's lab
#include <Engine.hpp>
#include<math.h>
#include <iostream>
#include "ResourceManager.hpp"
#include "GlobalAttributes.hpp"
#include "ControllerComponent.hpp"
#include "Camera.hpp"
#include <chrono>
#include <time.h>

class ControllerComponent;
class ResourceManager;
const int FRAMECAP = 1000/60;
float dt = 0.0f;
int countedFrames = 0;

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
	TTF_Font *font = NULL;
	SDL_Color tcolor;

	SDL_Surface *txt_surf = NULL;
	SDL_Texture *txt_texture = NULL;

	SDL_Surface *image;
	SDL_RWops *rwop;

	SDL_Texture *img_texture = NULL;

	Mix_Music *bgMusic = NULL;
	quit = false;
    // Initialize SDL with video
    SDL_Init(SDL_INIT_VIDEO);
	SDL_Renderer* gRenderer = NULL;

	if (ResourceManager::getInstance().addWindow("window", "The Team", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL)) {
		printf("Error: Could not load window\n");
		quit = true;
		return -1;
	}

    // Create an SDL window
    // window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
	SDL_Window* window = ResourceManager::getInstance().getResourceSDLWindow("window");
    gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (TTF_Init() < 0)
	{
		printf("SDL TTF error: could not initialize SDL_ttf\n");
		quit = true;
		return -1;
	}

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        exit(1);
    }

   
	if (ResourceManager::getInstance().addRenderer("gRenderer", gRenderer)) {
		printf("Error: Could not load renderer\n");
		return -1;
	}

	if (ResourceManager::getInstance().addResource("assets/bgmusic.wav", ResourceType::BackgroundMusic)) {
		printf("Error: Could not load background music\n");
		return -1;
	}
    return 0;
}

void Engine::addUFCallback(py::object func) {
	uforce.addCallback(func);
}

void Engine::addTileManager(TileManager* tm) {
	GameObject** tiles = tm->convertToGameObjects();
	int tilesCount = tm->getTileCount();

	if (tiles == nullptr) {
		std::cout << "Error: could not convert tiles to game objects\n";
		return;
	}

	for (int i = 0; i < tilesCount; i++) {
		gameObjs.push_back(tiles[i]);
	}
}

void Engine::update() {
	for (auto obj : playerObjs) {
		// std::cout << "PlayerObj name" << obj->getGameObjectName() <<"\n";
		ControllerComponent* contcomp = obj->getControllerComponent();

		if (contcomp != nullptr) {
			// std::string* keys = contcomp->getKeys();
			// int size = contcomp->getKeysNum();
			// for (int i = 0; i < size; i++) {
				contcomp->executeCallback();
				contcomp->executeUnCallback();
			// }
		}
		obj->updateSprite();
		obj->updateTransform();
	}

	for (auto obj : animateObjs) {
		obj->updateSprite();
		obj->updateTransform();
	}

	// convertToGameObjects(playerObjs, animateObjs);
	
	uforce.applyForces(&animateObjs);
	uforce.applyForces(&playerObjs);
	for (auto obj : animateObjs) {
		obj->handleCollision(gameObjs, animateObjs);
	}
	
	for (auto obj : playerObjs) {
		obj->handleCollision(gameObjs, animateObjs);
	}

	Camera::getInstance().update();
}

void Engine::Input()
{
	SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        // determine if the user still wants to have the window open
        // (this basically checks if the user has pressed 'X')
        quit = event.type == SDL_QUIT;
		
		if (e.type == SDL_QUIT) {
			quit = true;
		}
		else if (e.type == SDL_KEYDOWN)
				{
					if (e.key.keysym.sym == SDLK_q) {
						quit = true;
					}
					else {
						for (auto obj : playerObjs) {
							ControllerComponent* contcomp = obj->getControllerComponent();
							std::string* keys = contcomp->getKeys();
							int size = contcomp->getKeysNum();
							for (int i = 0; i < size; i++) {
								contcomp->setKeyTo(e.key.keysym.sym, true);
							}
						}
					}
				}
		else if (e.type == SDL_KEYUP)
				{
					for (auto obj : playerObjs) {
						ControllerComponent* contcomp = obj->getControllerComponent();
						std::string* keys = contcomp->getKeys();
						int size = contcomp->getKeysNum();
						for (int i = 0; i < size; i++) {
							contcomp->setKeyTo(e.key.keysym.sym, false);
						}
					}
				}

		// const Uint8* keystate = SDL_GetKeyboardState(NULL);

		/*if (keystate[SDL_SCANCODE_Q]) {
			quit = true;
		}

		for (auto obj : gameObjs) {
			ControllerComponent* contcomp = obj->getControllerComponent();
			std::string* keys = contcomp->getKeys();
			int size = contcomp->getKeysNum();
			for (int i = 0; i < size; i++) {
				if (keystate[keymap.at(keys[i])]) {
					contcomp->executeCallback(keys[i]);
				}
			}
		}*/
    }
}

bool Engine::programEnded() {
	return quit;
}

void Engine::clear() {
	SDL_Renderer* gRenderer = ResourceManager::getInstance().getResourceSDLRenderer("gRenderer");
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);
	SDL_RenderClear(gRenderer);
}

void Engine::Render()
{
	clear();
	for (auto obj : animateObjs) {
		if (destroyedObjs.find(obj->getGameObjectName()) == destroyedObjs.end()) {
			obj->render();
		}
	}

	for (auto obj : playerObjs) {
		if (destroyedObjs.find(obj->getGameObjectName()) == destroyedObjs.end()) {
			obj->render();
		}
	}

	for (auto obj : gameObjs) {
		if (destroyedObjs.find(obj->getGameObjectName()) == destroyedObjs.end()) {
			obj->render();
		}
	}
	for (auto comp : uiComponents) {
		comp->render();
	}

	SDL_RenderPresent(ResourceManager::getInstance().getResourceSDLRenderer("gRenderer"));
}

void Engine::delay(int seconds) {
 	Uint32 startTicks = SDL_GetTicks();
    
    float avgFPS = countedFrames / (startTicks / 1000.f);
    countedFrames++;
    
    int endTicks = SDL_GetTicks();

    //delays updating and rendering to a specified frame rate
    if ((endTicks - startTicks) < FRAMECAP) {
        SDL_Delay(FRAMECAP - (endTicks - startTicks));
    }
    
    dt = std::chrono::duration<float, std::chrono::milliseconds::period>(endTicks - startTicks).count();
}

// Only meant for inanimate objects!!!
void Engine::addGameObject(GameObject* obj) {
	gameObjs.push_back(obj);
}

void Engine::addAnimateObject(AnimateObject* obj) {
	animateObjs.push_back(obj);
}

void Engine::addPlayerObject(PlayerObject* obj) {
	playerObjs.push_back(obj);
}

void Engine::addUIComponent(UIComponent* ui) {
	uiComponents.push_back(ui);
}

void Engine::MainGameLoop()
{
	// Mix_Music* bgMusic = ResourceManager::getInstance().getResourceBackgroundMusic(musicPath);
	// if (Mix_PlayingMusic() == 0)
	// {
	// 	//Play the music
	// 	Mix_VolumeMusic(30);
	// 	Mix_PlayMusic(bgMusic, -1);
	// }

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

void Engine::destroyObject(std::string objectName) {
	destroyedObjs.insert(std::make_pair(objectName, 1));
}

float Engine::getTime() {
	float time = m_timer;
	if (!m_timerStopped) {
		time -= SDL_GetTicks();
	}
	if (time <= 0) {
		time = 0.0f;
	}
	time = (float) time / (float) 1000.0f;
	time = (int) (time * 100 + .5);
	time = (float) time/100;
	return time;
}

void Engine::setTimer(float miliseconds) {
	m_timer = miliseconds;
	m_init_timer = m_timer;
}

void Engine::resetTimer() {
	m_timer = m_init_timer;
}

void Engine::stopTimer() {
	m_timerStopped = true;
	m_timer -= SDL_GetTicks();
}

void Engine::reset() {
	playerObjs = {};
	animateObjs = {};
	gameObjs = {};
	destroyedObjs = {};
	resetTimer();
}
