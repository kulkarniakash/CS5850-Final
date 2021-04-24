#ifndef TILEMANAGER
#define TILEMANAGER
#include<unordered_map>
#include<string>
#include<Camera.h>
#include<Tile.hpp>

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else // This works for Mac
#include <SDL.h>
#endif


using namespace std;



/**
*class that manages storing the state of, loading and rendering
*of tiles. It serves two functions- 1) to render all the tiles during
*the actual game and 2) to render tiles for the tile editor
*/
class TileManager {
public:
	TileManager();

	static unordered_map<int, SDL_Texture*> tileTextures;

	// Takes in the position of the otp-left corner of the entire grid, width and height of the entire tile grid( width= no. of horizontal tiles in a row, height= no. of vertical tiles in a column), 
	// tileTextures = hashmap of TileType: SDL_Texture*, tileTypeGrid= the grid dhowing the position of tiles (by default is NULL)
	TileManager(Vec2 pos, int width, int height, int tileWidth, int tileHeight);

	int getWidth();
	int getHeight();
	int getTileWidth();
	int getTileHeight();
	Vec2 getPos();

	// Calls the render functions of each individual tile
	virtual void render(SDL_Renderer* ren, Camera* camera);

protected:
	// tileTextures = hashmap of TileType: SDL_Texture*
	
	// array of tile objects
	Tile** tileGrid;
	// tileTypeGrid= the grid dhowing the position of tiles (by default is NULL)
	int** tileTypeGrid;

	int width, height;
	int tileWidth, tileHeight;

	Vec2 pos;

};

#endif
