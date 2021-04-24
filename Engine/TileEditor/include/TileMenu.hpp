#ifndef TILEMENU
#define TILEMENU
#include<TileManager.hpp>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

/**
*Serves as a menu of tiles from which a selection can be made
*/
class TileMenu : public TileManager {
public:
	TileMenu();
	TileMenu(Vec2 pos, int width, int height, int tileWidth, int tileHeight, unordered_map<TileType, SDL_Texture*> tileTextures);
	bool handleClick(Vec2 clickPos);

	// after a selection is made, the selected tile type is returned
	TileType getSelectedTileType();
	void render(SDL_Renderer* ren, Camera* camera);

private:
	// returns the index (row, col) of the tile that has been selected
	int selectedTileTypeIndex[2];
	
	//2d  grid of the menu where each entry represents a tile
	Tile** tileSelection;
};
#endif
