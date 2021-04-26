// pybind taken from Akash's and Kimin's lab
//Engine class taken from Sumanth's assignment-2, written by Shreyas Shivashankar
#include <Engine.hpp>
#include <iostream>
#include "ResourceManager.hpp"
#include "GlobalAttributes.hpp"
#include "ControllerComponent.hpp"
#include "Camera.hpp"

class ControllerComponent;
class ResourceManager;

const std::string fontPath = "assets/lazy.ttf";
const std::string imagePath = "assets/BGSky.jpg";
const std::string musicPath = "assets/bgmusic.wav";


	/*TTF_Font *font = NULL;
	SDL_Color tcolor;

	SDL_Surface *txt_surf = NULL;
	SDL_Texture *txt_texture = NULL;

	SDL_Surface *image;
	SDL_RWops *rwop;

	SDL_Texture *img_texture = NULL;

	Mix_Music *bgMusic = NULL;*/

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

    // this->renderer = new GraphicsEngineRenderer(SCREEN_WIDTH, SCREEN_HEIGHT);

    /*if (nullptr == renderer) {
        exit(1);

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

// void Engine::convertToGameObjects(std::vector<PlayerObject*> playerObjs, std::vector<AnimateObject*> animateObjs) {
// 	for (auto pObj: playerObjs) {
// 		GameObject* obj = dynamic_cast<GameObject*>(pObj);
// 		playerAsGameObjs.push_back(obj);
// 	}
// 	for (auto aObj: animateObjs) {
// 		GameObject* obj = dynamic_cast<GameObject*>(aObj);
// 		animAsGameObjs.push_back(obj);
// 	}
// }

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
	/*SDL_Texture* bgimage = ResourceManager::getInstance().getResourceSDLTexture(imagePath.c_str());
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
	SDL_FreeSurface(txt_surf);*/
	clear();
	for (auto obj : animateObjs) {
		obj->render();
	}

	for (auto obj : playerObjs) {
		obj->render();
	}

	for (auto obj : gameObjs) {
		obj->render();
	}


	/*renderer->SetRenderDrawColor(0x0, 0x0, 0x0, 0xFF);
	renderer->RenderClear();
	SDL_RenderCopy(renderer->GetRenderer(), img_texture, NULL, NULL);
	SDL_RenderCopy(renderer->GetRenderer(), txt_texture, NULL, NULL);
	renderer->RenderPresent();*/
	
	SDL_RenderPresent(ResourceManager::getInstance().getResourceSDLRenderer("gRenderer"));
}

void Engine::delay(int seconds) {
	SDL_Delay(seconds);
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



