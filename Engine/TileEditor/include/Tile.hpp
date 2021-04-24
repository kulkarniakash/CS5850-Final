#ifndef TILE
#define TILE
#include <Vec2.h>
#include <Camera.h>

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else // This works for Mac
#include <SDL.h>
#endif

/**
*Enum for specifying what tile type we wish to
*use. If you want to add a new tile type, add it here first
*/
enum TileType {
	Empty = 0,
	Dry,
	Coal,
	Lava,
	Ice, 
	Grass,
	Wood,
	Metal,
	TileNum
};

/**
*Represents one tile in the tile grid. Note that the position of the tile is the initial
*position without accounting for the camera. The render function will take the camera into
*account.
*/
class Tile {
public:
	Tile();

	// Takes in position of the top-left corner of the tile, the tile width and height in pixels
	// the texture to be shown when the tile renders, and the source of the part of the texture to 
	// be rendered (by default, the entire texture will be rendered (hence setting the sdl rect to 0)
	Tile(Vec2 pos, int width, int height, SDL_Texture* texture, TileType type, SDL_Rect src = SDL_Rect{ 0, 0, 0, 0 });

	// Position of Top-left corner of tile
	Vec2 getPos();

	int getWidth();
	int getHeight();
	TileType getTileType();
	SDL_Texture* getTexture();

	// Takes in the renderer and a camera object in order to render the tile in the appropriate position.
	// the camera figures out the absolute final coordinates of the tile
	void render(SDL_Renderer* ren, Camera* camera=NULL);

private:
	// Position of top-left corner of tile
	Vec2 pos;
	int width, height;
	SDL_Texture* texture;

	// part of the texture to be rendered.
	SDL_Rect src;

	TileType type;
};
#endif
