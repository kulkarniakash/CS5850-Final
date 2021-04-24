#include "TileManager.hpp"

// Initialize the tilePaths.
std::unordered_map<int, std::string> TileManager::tilePaths = std::unordered_map<int, std::string>{};

std::unordered_map<int, std::string> tiletypes;

// Three arguments constructor of TileManager object.
TileManager::TileManager(int tileWidth, int tileHeight, Vec2 pos) : tileWidth(tileWidth), tileHeight(tileHeight), pos(pos) {
	tilesCount = 0;
	tilemap = nullptr;
}

// Default destructor of TileManager object.
TileManager::~TileManager() {}

// Get the column number of the entire tile grid.
int TileManager::getColNum() {
	return col;
}

// Get the row number of the entire tile grid.
int TileManager::getRowNum() {
	return row;
}

int TileManager::getTileCount() {
	return tilesCount;
}

// Get the width of each single tile.
int TileManager::getTileWidth() {
	return tileWidth;
}

// Get the height of each single tile.
int TileManager::getTileHeight() {
	return tileHeight;
}

// Get the TileManager's current process position.
Vec2 TileManager::getPos() {
	return pos;
}

// Load the level map according to the input file path.
void TileManager::loadLevelMap(std::string path) {
	SDL_RWops* file = SDL_RWFromFile(path.c_str(), "r");
	if (file == nullptr) {
		SDL_Log("Cannot read tile map file.");
		//exit(1);
	}

	const int bsize = 40000;
	char gData[bsize] = { 0 };

	SDL_RWread(file, gData, bsize, 1);
	SDL_RWclose(file);

	// parse the file to get the tile map
	int i = 0;
	std::string cur = "";
	while (gData[i] != '\r') {
		if (gData[i] == ' ') {
			row = stoi(cur);
			cur = "";
		}
		else {
			cur.push_back(gData[i]);
		}
		i++;
	}
	i++;
	col = stoi(cur);
	cur = "";
	tilemap = new int * [row];
	for (int i = 0; i < row; i++) {
		tilemap[i] = new int[col];
	}
	
	int r = 0, c = 0;
	while (gData[i] != 0) {
		if (gData[i] == ' ' || gData[i] == '\r') {
			int type = (stoi(cur));
			cur = "";
			if (type != 0) {
				tilesCount += 1;
			}

			tilemap[r][c] = type;
			if (gData[i] == '\r') {
				c = 0;
				r++;
				i++;
			}
			else {
				c++;
			}
		}
		else {
			cur.push_back(gData[i]);
		}
		i++;
	}

	std::cout << "Tile map\n";
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			std::cout << tilemap[i][j] << " ";
		}

		std::cout << std::endl;
	}
}

// Save the current level to the input file path.
void TileManager::saveLevelMap(std::string path) {
	
}

// Calls the render functions to render each individual tile.
/*void TileManager::render(GraphicsEngineRenderer* ren, Camera* camera) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			tilemap[i][j].render(ren, camera, tilePaths[tilemap[i][j].getTileType()]);
		}
	}
}*/

GameObject** TileManager::convertToGameObjects() {
	GameObject** tiles = new GameObject* [(size_t)tilesCount];

	if (tilemap == nullptr) {
		std::cout << "Error: tilemap not initialized\n";
		return nullptr;
	}

	if (tiletypes.size() == 0) {
		std::cout << "Error: tiles not initialized\n";
		return nullptr;
	}

	int count = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			int type = tilemap[i][j];
			if (type != 0) {
				Vec2 position = pos + Vec2(tileWidth * j, tileHeight * i);
				SpriteComponent* sprite = new SpriteComponent(tiletypes[type], SDL_Rect{ -1, -1, -1, -1 });
				TransformComponent* tran = new TransformComponent(position, Vec2(0, 0));
				tiles[count] = new GameObject(tiletypes[type], tileWidth, tileHeight);
				tiles[count]->addTransformComponent(tran);
				tiles[count]->addSpriteComponent(sprite);
				count++;
			}
		}
	}


	return tiles;
}

// Get the tile type at a specified position.
int TileManager::getTileTypeAt(int row, int col) {
	return tilemap[row][col];
}