#ifndef TILEMENU
#define TILEMENU
#include<TileManager.hpp>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

//! @brief class that Serves as a menu of tiles from which a selection can be made
class TileMenu : public TileManager {
public:
    
    //! @brief Constructs our TileMenu
	TileMenu();
    
    /*!
     * @brief Constructs our TileMenu
     * @param pos: Vec2 position of our whole grid
     * @param width: int representing the width of the entire tile grid
     * @param height: int representing the height of the entire tile grid
     * @param tileWidth: int representing the width of a tile
     * @param tileHeight: int representing the height of a tile
     * @param tileTextures: an unordered map that contains an index and texture of a tile
     */
	TileMenu(Vec2 pos, int width, int height, int tileWidth, int tileHeight, unordered_map<int, SDL_Texture*> tileTextures);'
    
    
    /*!
     * @brief checks whether the mouse was clicked on the menu area
     * @param clickPos: Vec2 position where the mouse was clicked
     * @return boolean value determining if it was clicked on the menu
     */
	bool handleClick(Vec2 clickPos);

	//! @return int represnting the tileType
	int getSelectedTileType();
    
    /*!
     * @brief Calls the render functions of each individual tile
     * @param ren: SDL_Renderer we want to use to render our tiles
     * @param camera: Camera we want to render our tiles in the user's screen
     */
	void render(SDL_Renderer* ren, Camera* camera);

private:
	// returns the index (row, col) of the tile that has been selected
	int selectedTileTypeIndex[2];
	
	//2d  grid of the menu where each entry represents a tile
	Tile** tileSelection;
};
#endif
