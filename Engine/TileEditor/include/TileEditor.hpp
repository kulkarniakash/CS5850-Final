#ifndef TILEEDITOR
#define TILEEDITOR
#include<unordered_map>
#include<string>
#include<Camera.h>
#include<TileManager.hpp>
#include<TileMenu.hpp>
#include <fstream>
#include <sstream>
#include <iostream>

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#else // This works for Mac
#include <SDL.h>
#include<SDL_image.h>
#endif

#if defined(MINGW)
#define endline '\r'
#else
#define endline '\n'
#endif

//! @brief enum class representing the possibilities of click events the user can input
enum class Click {
	None=0,
	Left, 
	Right
};

using namespace std;

/*! @brief
 * Class inherits from Tile Manager. While tile manager
 * can be used for the general purpose of rendering and keeping
 * track of the tile grid state, TileEditor is specifically meant for
 * creating new custom landscapes by placing tiles in whatever arrangement one desires.
 * this includes a tile selection menu rendered at the left part of the screen from
 * which one can select a certain tile type and then place it in a certain location.
 * The first tile type is always the "erase tile", which after selecting will erase any
 * selected tile by clicking on it.
*/
class TileEditor : public TileManager {
public:
	
    /*!
     * @brief Constructor for TileEditor
     * @param pos: Vec2 position of the top-left corner of the entire grid
     * @param width: int representing the width of the entire tile grid
     * @param height: int represetning the height of the entire tile grid
     * @param tileWidth: int representing the width of a tile
     * @param tileHeight: int representing the height of a tile
     */
	TileEditor(Vec2 pos, int width, int height, int tileWidth, int tileHeight);

	static unordered_map<int, std::string> tilePaths;

	/*!@brief to be called before constructing object!!
     @param path: filepath of a tile
     @param ren: SDL_Renderer we want to render our tile with
     */
	static void loadTileTypes(std::string path, SDL_Renderer* ren) {
		SDL_RWops* file = SDL_RWFromFile(path.c_str(), "r");
		if (file == nullptr) {
			SDL_Log("Cannot read tile type file.");
			exit(1);
		}

		char gData[4096] = { 0 };
		//printf("Reading file...!\n");

		SDL_RWread(file, gData, 4096, 1);
		SDL_RWclose(file);

		// parse the file to get the tile types

		int i = 0;
		std::string cur = "";
		int type = 0;
		while (gData[i] != 0) {
			if (gData[i] == ' ') {
				type = (std::stoi(cur));
				cur = "";
			}
			else if (gData[i] == endline) {
				tilePaths[type] = cur;
				cur = "";
				type = 0;
				// i++;
			}
			else {
				cur.push_back(gData[i]);
			}
			i++;
		}

		SDL_Texture* empty = NULL;
		tileTextures.insert(make_pair(0, empty));
		for (auto tilet : tilePaths) {
			// SDL_Surface* newType = SDL_LoadBMP(tilet.second.c_str());
			// SDL_Texture* newText = SDL_CreateTextureFromSurface(ren, newType);
			SDL_Surface* image;
			SDL_RWops* rwop;
			rwop = SDL_RWFromFile(tilet.second.c_str(), "rb");
			image = IMG_LoadJPG_RW(rwop);
			if (!image) {
				printf("IMG_LoadJPG_RW: %s\n", IMG_GetError());
			}

			SDL_Texture* newText = SDL_CreateTextureFromSurface(ren, image);
			TileManager::tileTextures.insert(make_pair(tilet.first, newText));
		}

		std::cout << "loaded tile types\n";
	}

	// takes in as input the coordinates of the click and the camera and decides what to do based on whether the tile menu region was
	// clicked or the rest of the tile editor region. If it was the tile menu, a tile selection is made. Otherwise if it's the rest of
	// the tile editor, the current tile selection is placed over there.
    
    /*!
     * @brief Handles event when user clicks on a screen
     * @param clickPos: Vec2 Position where the user clicked
     * @param camera: Camera that is locked on the user's screen
     * @param Click: click event the user inputted
     */
	void handleClick(Vec2 clickPos, Camera* camera, Click click);

    /*!
     * @brief Loads the tileMap of a file
     * @param path: String representing the path of the file
     */
	void loadLevelMap(std::string path);

    
    /*!
     * @brief renders our tiles and tileMap
     * @param ren: SDL_Renderer we want to use to render
     * @param camera: Camera to render what is shown on the user's screen
     */
	void render(SDL_Renderer* ren, Camera* camera);

    /*!
     * @brief saves the user's work to a new file
     * @param filepath: String representing the file path the user wants to save towards
     */
	void saveLevelToFile(string filePath);

private:
	// a tile menu representing all the avaialble tile selections to choose from
	TileMenu tileMenu;
};

#endif
