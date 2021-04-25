#include "tst_Engine.hpp"
#include <TileEditor.hpp>
// I recommend a map for filling in the resource manager
#include <map>
#include <string>
#include <memory>
#include <iterator>
#include<Direction.h>
#include<Timer.h>
#include<stdio.h>
#include<iostream>

// Create a Tile Editor
TileEditor* myTileEditor;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int FPS = 60;
const float SPF = 1000 / FPS;

const string DRY_TILE_SRC = "./Assets/DryTile.bmp";
const string ERASE_TILE_SRC = "./Assets/EraseTile.bmp";
const string COAL_TILE_SRC = "./Assets/CoalTile.bmp";
const string LAVA_TILE_SRC = "./Assets/LavaTile.bmp";
const string ICE_TILE_SRC = "./Assets/IceTile.bmp";
const string GRASS_TILE_SRC = "./Assets/GrassTile.bmp";
const string WOOD_TILE_SRC = "./Assets/WoodTiel.bmp";
const string METAL_TILE_SRC = "./Assets/MetalTile.bmp";
const string BG_SKY_SRC = "./Assets/BGSky.bmp";

const std::string fontfile = "assets/lazy.ttf";


extern string LEVEL_INPUT_FILE;
extern string LEVEL_OUTPUT_FILE;
extern int TILE_WIDTH;
extern int TILE_HEIGHT;

SDL_Surface* bgSkySrf = SDL_LoadBMP(BG_SKY_SRC.c_str());
SDL_Texture* bgSkyTxt = NULL;

// Initialization function
// Returns a true or false value based on successful completion of setup.
// Takes in dimensions of window.
Engine::Engine(){
	camera = new Camera(Vec2(0,0), 10, 10);
	text = NULL;
}


// Proper shutdown and destroy initialized objects
Engine::~Engine(){
	delete camera;
}

// Return Input
void Engine::Input(bool *quit, SDL_Keycode& code){

	static bool leftMouseButtonDown = false;
	static bool rightMouseButtonDown = false;
	static Click click = Click::None;

	int mouseX = 0, mouseY = 0;

    // Event handler that handles various events in SDL
    // that are related to input and output
    SDL_Event e;
    // Enable text input
    SDL_StartTextInput();
      //Handle events on queue
      while(SDL_PollEvent( &e ) != 0){
        // User posts an event to quit
        // An example is hitting the "x" in the corner of the window.
        if(e.type == SDL_QUIT){
          *quit = true;
		}
		else if (e.type == SDL_KEYDOWN) {
			code = SDL_Keycode(e.key.keysym.sym);
		}
		else {
			code = SDLK_0;
		}

		if (e.type == SDL_MOUSEBUTTONDOWN) {
			if (e.button.button == SDL_BUTTON_LEFT) {
				click = Click::Left;

			}
			else if (e.button.button == SDL_BUTTON_RIGHT) {
				click = Click::Right;
			}
		}
		else if (e.type == SDL_MOUSEBUTTONUP) {
			click = Click::None;
		}
		
      }

	  if (click != Click::None) {
		  SDL_GetMouseState(&mouseX, &mouseY);

		  Vec2 tmPos = camera->getObjectPos(myTileEditor->getPos());
		  int width = myTileEditor->getWidth() * TILE_WIDTH;
		  int height = myTileEditor->getHeight() * TILE_HEIGHT;

		  int row = -1;
		  int col = -1;
		  if (!(mouseX < tmPos.x || mouseX > tmPos.x + width || mouseY < tmPos.y || mouseY > tmPos.y + height)) {
			  if (text != NULL) {
				  SDL_DestroyTexture(text);
			  }

			  row = int(mouseY - tmPos.y) / TILE_HEIGHT;
			  col = int(mouseX - tmPos.x) / TILE_WIDTH;

			  TTF_Font* font = ResourceManager::getInstance().getResourceFont(fontfile);
			  if (!font) {
				  std::cout << "Error: Could not load font\n";
			  }
			  SDL_Color tcolor = SDL_Color();
			  tcolor.r = 0;
			  tcolor.g = 20;
			  tcolor.b = 0;
			  std::string position = "(" + std::to_string(row) + "," + std::to_string(col) + ")";
			  SDL_Surface* txt_surf = TTF_RenderText_Solid(font, position.c_str(), tcolor);
			  SDL_Texture* txt_texture = SDL_CreateTextureFromSurface(m_renderer->GetRenderer(), txt_surf);

			  std::cout << "row: " << row << " col: " << col << std::endl;

			  text = txt_texture;
			  SDL_FreeSurface(txt_surf);
		  }

		  // sends coordinates of the click to be handled by the tile editor
		  myTileEditor->handleClick(Vec2(mouseX, mouseY), camera, click);
	  }
}

// Update SDL
void Engine::Update(SDL_Keycode code)
{
    static int frame =0 ;
    
    // Increment the frame that
    // the sprite is playing
    frame++;
    if(frame>6){
        frame=0;
    }
    
	switch (code) {
	case SDLK_LEFT:
		camera->update(Direction::Left);
		break;
	case SDLK_RIGHT:
		camera->update(Direction::Right);
		break;
	case SDLK_UP:
		camera->update(Direction::Up);
		break;
	case SDLK_DOWN:
		camera->update(Direction::Down);
		break;
	}

    // iterate through each of our characters
    /*for(int i =0; i < CHARACTERS; i++){
        characters[i].Update(20,20, frame);
    }*/
}


// Render
// The render function gets called once per loop
void Engine::Render(){
    // Set the color of the empty framebuffer
    m_renderer->SetRenderDrawColor(110, 130,170,0xFF);
    // Clear the screen to the color of the empty framebuffer
    m_renderer->RenderClear();

	SDL_RenderCopy(m_renderer->GetRenderer(), bgSkyTxt, NULL, NULL);

    // Render the tile map
    myTileEditor->render(m_renderer->GetRenderer(), camera);

	SDL_Rect dest = SDL_Rect{};
	dest.x = SCREEN_WIDTH - 400;
	dest.y = 0;
	dest.w = 300;
	dest.h = 30;

	if (text != NULL) {
		SDL_RenderCopy(m_renderer->GetRenderer(), text, NULL, &dest);
	}

	// Render each of the character(s)
	/*for (int i = 0; i < CHARACTERS; i++) {
		characters[i].Render(m_renderer->GetRenderer(), camera);
	}*/

    // Flip the buffer to render
    m_renderer->RenderPresent();
}



//Loops forever!
void Engine::MainGameLoop(){
    // Main loop flag
    // If this is quit = 'true' then the program terminates.
    bool quit = false;
	SDL_Keycode code = SDLK_0;
	MyTimer timer = MyTimer();
	
    // While application is running
    while(!quit){

		timer.start();
      // Get user input
      Input(&quit, code);
      
      // Update our scene
      Update(code);
      // Render using OpenGL

	  Uint8 seconds = timer.getTicks();
	  if (seconds < SPF) {
		  SDL_Delay(SPF - seconds);
	  }

      Render();
      //Update screen of our specified window
    }
    //Disable text input
    SDL_StopTextInput();
}

void Engine::Start(){
    // Report which subsystems are being initialized
    if(m_renderer!=nullptr){
        std::cout << "Initializing Graphics Subsystem\n";
    }else{
        std::cout << "No Graphics Subsystem initialized\n";
    }

    // Move Sprite to initial position
    // characters[0].SetPosition(128,508);
    // Load an image for our character
    // characters[0].LoadImage("./images/sprite.bmp",m_renderer->GetRenderer());

    // Setup our TileMap
    // This tile map is 20x11 in our game
    // It is using a 'reference' tilemap with 8x8 tiles
    // that are each 64x64 pixels.
	/*const string LAVA_TILE_SRC = "./Assets/LavaTile.bmp";
	const string ICE_TILE_SRC = "./Assets/IceTile.bmp";
	const string GRASS_TILE_SRC = "./Assets/GrassTile.bmp";
	const string WOOD_TILE_SRC = "./Assets/WoodTiel.bmp";
	const string METAL_TILE_SRC = "./Assets/MetalTile.bmp";

	bgSkyTxt = SDL_CreateTextureFromSurface(m_renderer->GetRenderer(), bgSkySrf);

	SDL_Surface* lavaTileSrf = SDL_LoadBMP(LAVA_TILE_SRC.c_str());
	SDL_Texture* lavaTileTxt = SDL_CreateTextureFromSurface(m_renderer->GetRenderer(), lavaTileSrf);

	SDL_Surface* iceTileSrf = SDL_LoadBMP(ICE_TILE_SRC.c_str());
	SDL_Texture* iceTileTxt = SDL_CreateTextureFromSurface(m_renderer->GetRenderer(), iceTileSrf);

	SDL_Surface* grassTileSrf = SDL_LoadBMP(GRASS_TILE_SRC.c_str());
	SDL_Texture* grassTileTxt = SDL_CreateTextureFromSurface(m_renderer->GetRenderer(), grassTileSrf);

	SDL_Surface* woodTileSrf = SDL_LoadBMP(WOOD_TILE_SRC.c_str());
	SDL_Texture* woodTileTxt = SDL_CreateTextureFromSurface(m_renderer->GetRenderer(), woodTileSrf);

	SDL_Surface* metalTileSrf = SDL_LoadBMP(METAL_TILE_SRC.c_str());
	SDL_Texture* metalTileTxt = SDL_CreateTextureFromSurface(m_renderer->GetRenderer(), metalTileSrf);

	SDL_Surface* dryTileSrf = SDL_LoadBMP(DRY_TILE_SRC.c_str());
	SDL_Texture* dryTileTxt = SDL_CreateTextureFromSurface(m_renderer->GetRenderer(), dryTileSrf);

	SDL_Surface* coalTileSrf = SDL_LoadBMP(COAL_TILE_SRC.c_str());
	SDL_Texture* coalTileTxt = SDL_CreateTextureFromSurface(m_renderer->GetRenderer(), coalTileSrf);

	unordered_map<TileType, SDL_Texture*>* textures = new unordered_map<TileType, SDL_Texture*>({{TileType::Empty, NULL}, {TileType::Metal, metalTileTxt}, {TileType::Wood, woodTileTxt}, {TileType::Grass, grassTileTxt}, {TileType::Ice, iceTileTxt}, {TileType::Lava, lavaTileTxt}, {TileType::Coal, coalTileTxt}, {TileType::Dry, dryTileTxt}});
	TileType** grid = new TileType*[10];
	for (int i = 0; i < 10; i++) {
		grid[i] = new TileType[20];
		for (int j = 0; j < 20; j++) {
			grid[i][j] = TileType::Empty;
		}
	}*/
	
	if (ResourceManager::getInstance().addResource(fontfile, ResourceType::Font, 20) > 1) {
		std::cout << "Error: could not add font in resource manager\n";
	}


	TileEditor::loadTileTypes("./assets/Tiles", m_renderer->GetRenderer());
	myTileEditor = new TileEditor(Vec2(0, 0), 0, 0, TILE_WIDTH, TILE_HEIGHT);
	std::cout << "entering loadlevelmap\n";
	myTileEditor->loadLevelMap(LEVEL_INPUT_FILE);
	std::cout << "exited loadlelvelmap\n";

}

void Engine::Shutdown(){
    // Shut down our Tile Systems
	printf("PLEASE DO NOT CLOSE, SHUTTING DOWN...\n");
    if(nullptr!=m_renderer){
        delete m_renderer;
    } 

	myTileEditor->saveLevelToFile(LEVEL_OUTPUT_FILE);

    // Destroy our tilemap
    if(nullptr!=myTileEditor){
        delete myTileEditor;
    }

	printf("Okay, now you can close the window.\n");
}

void Engine::InitializeGraphicsSubSystem(){
    // Setup our Renderer
    m_renderer = new GraphicsEngineRenderer(SCREEN_WIDTH ,SCREEN_HEIGHT);
    if(nullptr == m_renderer){
        exit(1); // Terminate program if renderer 
                 // cannot be created.
                 // (Optional) TODO:   Could put an error 
                 //                    messeage, or try to 
                 //                    reinitialize the engine 
                 //                    with a different render
    }
}
