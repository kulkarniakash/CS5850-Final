#ifndef TILEMANAGER_HPP
#define TILEMANAGER_HPP
#pragma once

// Include C++ standard libraries.
#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>

// Include our custom headers.
#include "ResourceManager.hpp"
#include "Vec2.hpp"
#include "GameObject.hpp"


extern std::unordered_map<int, std::string> tiletypes;


/**
 * @brief TileManage class manages storing, loading and rendering
 * of tiles. It serves two main features: 1. Render all the tiles during
 * the actual game. 2. Render tiles for the tile editor.
*/
class TileManager {
public:

	/**
	 * @brief Three arguments constructor of TileManager object.
	 * @param tileWidth An integer indicates the number of horizontal tiles in a row.
	 * @param tileHeight An integer indicates the number of vertical tiles in a column.
	 * @param pos A Vec2 object indicates the start pocess position of the entire grid.
	*/
	TileManager(int tileWidth, int tileHeight, Vec2 pos = Vec2(0, 0));

	/**
	 * @brief Default destructor of TileManager object.
	*/
	~TileManager();

	// A static unordered_map which bind each tile type to its relative path.
	static std::unordered_map<int, std::string> tilePaths;

	/**
	 * @brief Load tiles' config file and bind each tile type with its relative path.
	 * @param path A string object indicates the path of tiles' config file.
	*/
	static void loadTileTypes(std::string path) {
		SDL_RWops* file = SDL_RWFromFile(path.c_str(), "r");
		// Check if the loading process is successful or not.
		if (file == nullptr) {
			SDL_Log("Cannot read tile type file.");
			//exit(1);
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
				printf("%s\n", cur.c_str());
				type = std::stoi(cur);
				cur = "";
			}
			else if (gData[i] == '\r') {
				// tilePaths[type] = cur;
				tiletypes.insert(std::make_pair(type, cur));
				cur = "";
				type = 0;
				i++;
			}
			else {
				cur.push_back(gData[i]);
			}
			i++;
		}
	}

	// Get a specific tile type's relative path by the input tile type.
	static std::string getTilePath(int type) { return tiletypes[type]; }

	/**
	 * @brief Get the column number of the entire tile grid.
	 * @return An integer indicates the column number of the entire tile grid.
	*/
	int getColNum();

	/**
	 * @brief Get the row number of the entire tile grid.
	 * @return An integer indicates the row number of the entire tile grid.
	*/
	int getRowNum();

	/**
	 * @brief Get the width of each single tile.
	 * @return An integer indicates the width of each single tile.
	*/
	int getTileWidth();

	/**
	 * @brief Get the height of each single tile.
	 * @return An integer indicates the height of each single tile.
	*/
	int getTileHeight();

	/**
	 * @brief Get the TileManager's current process position.
	 * @return A Vec2 object indicates the TileManager's current process position.
	*/
	Vec2 getPos();

	/**
	 * @brief Load the level map according to the input file path.
	 * @param path A string indicates the path of the level map file.
	*/
	void loadLevelMap(std::string path);

	/**
	 * @brief Save the current level to the input file path.
	 * @param path A string indicates the path of the level map file to be saved.
	*/
	void saveLevelMap(std::string path);

	/**
	 * @brief Calls the render functions to render each individual tile.
	 * @param ren A pointer to a GraphicsEngineRenderer object indicates the render.
	 * @param camera A pointer to a Camera object indicates the camera.
	*/
	GameObject** convertToGameObjects();

	/**
	 * @brief Get the tile type at a specified position.
	 * @param row An integer indicates the row number of that specified position.
	 * @param col An integer indicates the column number of that specified position.
	 * @return An integer(enum) indicates the tile type of that specified position.
	*/
	int getTileTypeAt(int row, int col);

	int getTileCount();

protected:

	// A pointer to a pointer of Tile object indicates the array of tile objects.
	int** tilemap;

	// Two integers to store the column and row number which TileManager is working on.
	int col, row;

	// Two integers indicate each single tile's width and height.
	int tileWidth, tileHeight;

	// A Vec2 object indicates the current pocess position of the entire grid.
	Vec2 pos;

	int tilesCount;
};

#endif
