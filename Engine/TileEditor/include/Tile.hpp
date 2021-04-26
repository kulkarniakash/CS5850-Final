#ifndef TILE
#define TILE
#include <Vec2.h>
#include <Camera.h>

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else // This works for Mac
#include <SDL.h>
#endif


/*!
 * @brief Represents one tile in the tile grid. Note that the position of the tile is the initial
 * position without accounting for the camera. The render function will take the camera into account.
 */
class Tile {
public:
    
    //! Constructor of our Tile
	Tile();

	/*!
     @brief Constructour of our Tile
     @param pos: Vec2 position of the top-left corner of the tile
     @param width: int that represents tile width
     @param height: int that represents tile height
     @param texture: SDL_Texture pointer to show the texture when tile renders
     @param type: int to determine the type of tile
     @param src: SDL_Rect to represent the rectangle we want to render
     */
	Tile(Vec2 pos, int width, int height, SDL_Texture* texture, int type, SDL_Rect src = SDL_Rect{ 0, 0, 0, 0 });

	//! @return Vec2 Position of Top-left corner of tile
	Vec2 getPos();

    //! @return int representing our width
	int getWidth();
    
    //! @return int representing our height
	int getHeight();
    
    //! @return int representing our tileType
	int getTileType();
    
    //! @return SDL_Texture pointer representing our texture
	SDL_Texture* getTexture();

	/*!
     @brief Renders the Tile
     @param ren: SDL_Renderer we choose to render with
     @param camera: Camera object which figures out the absolute final coordinates of the tile
     */
	void render(SDL_Renderer* ren, Camera* camera=NULL);

private:
	// Position of top-left corner of tile
	Vec2 pos;
	int width, height;
	SDL_Texture* texture;

	// part of the texture to be rendered.
	SDL_Rect src;

	int type;
};
#endif
