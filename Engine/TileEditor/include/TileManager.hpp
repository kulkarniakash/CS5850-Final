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



/*!
 * @brief class that manages storing the state of, loading and rendering
 * of tiles. It serves two functions- 1) to render all the tiles during
 * the actual game and 2) to render tiles for the tile editor
*/
class TileManager {
public:
    
    //! @brief Constructs our TileManager
	TileManager();

	static unordered_map<int, SDL_Texture*> tileTextures;
    
    /*!
     * @brief Constructs our TileManager
     * @param pos: Vec2 position of our whole grid
     * @param width: int representing the width of the entire tile grid
     * @param height: int representing the height of the entire tile grid
     * @param tileWidth: int representing the width of a tile
     * @param tileHeight: int representing the height of a tile
     */
	TileManager(Vec2 pos, int width, int height, int tileWidth, int tileHeight);

    //! @return the width of the tile grid
	int getWidth();
    
    //! @return the height of the tile grid
	int getHeight();
    
    //! @return the width of a tile
	int getTileWidth();
    
    //! @return the height of a tile
	int getTileHeight();
    
    //! @return the postioin of the tilegrid
	Vec2 getPos();

    
    /*!
     * @brief Calls the render functions of each individual tile
     * @param ren: SDL_Renderer we want to use to render our tiles
     * @param camera: Camera we want to render our tiles in the user's screen
     */
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
