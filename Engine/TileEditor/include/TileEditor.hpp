#ifndef TILEEDITOR
#define TILEEDITOR
#include<unordered_map>
#include<string>
#include<Camera.h>
#include<TileManager.hpp>
#include<TileMenu.hpp>

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else // This works for Mac
#include <SDL.h>
#endif

enum class Click {
	None=0,
	Left, 
	Right
};

using namespace std;


/**
*Class inherits from Tile Manager. While tile manager
*can be used for the general purpose of rendering and keeping
*track of the tile grid state, TileEditor is specifically meant for 
*creating new custom landscapes by placing tiles in whatever arrangement one desires.
*this includes a tile selection menu rendered at the left part of the screen from
*which one can select a certain tile type and then place it in a certain location.
*The first tile type is always the "erase tile", which after selecting will erase any 
*selected tile by clicking on it.
*/
class TileEditor : public TileManager {
public:
	// Takes in the position of the top-left corner of the entire grid, width and height of the entire tile grid( width= no. of horizontal tiles in a row, height= no. of vertical tiles in a column), 
	// tileTextures = hashmap of TileType: SDL_Texture*, tileTypeGrid= the grid dhowing the position of tiles (by default is NULL)
	TileEditor(Vec2 pos, int width, int height, int tileWidth, int tileHeight);

	static unordered_map<TileType, std::string> tilePaths;

	// to be called before constructing object!!
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
		TileType type = TileType::Empty;
		while (gData[i] != 0) {
			if (gData[i] == ' ') {
				type = static_cast<TileType>(std::stoi(cur));
				cur = "";
			}
			else if (gData[i] == '\r') {
				tilePaths[type] = cur;
				cur = "";
				type = TileType::Empty;
				i++;
			}
			else {
				cur.push_back(gData[i]);
			}
			i++;
		}

		SDL_Texture* empty = NULL;
		tileTextures.insert(make_pair(TileType::Empty, empty));
		for (auto tilet : tilePaths) {
			SDL_Surface* newType = SDL_LoadBMP(tilet.second.c_str());
			SDL_Texture* newText = SDL_CreateTextureFromSurface(ren, newType);
			TileManager::tileTextures.insert(make_pair(tilet.first, newText));
		}
	}

	// takes in as input the coordinates of the click and the camera and decides what to do based on whether the tile menu region was
	// clicked or the rest of the tile editor region. If it was the tile menu, a tile selection is made. Otherwise if it's the rest of
	// the tile editor, the current tile selection is placed over there.
	void handleClick(Vec2 clickPos, Camera* camera, Click click);

	void loadLevelMap(std::string path);

	void render(SDL_Renderer* ren, Camera* camera);

	void saveLevelToFile(string filePath);

private:
	// a tile menu representing all the avaialble tile selections to choose from
	TileMenu tileMenu;
};

#endif
