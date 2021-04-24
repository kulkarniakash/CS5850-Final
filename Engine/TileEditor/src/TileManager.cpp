#include<TileManager.hpp>

unordered_map<TileType, SDL_Texture*> TileManager::tileTextures;

TileManager::TileManager() {

}

// tile textures is a map specifying what tile type is associated with what texture, tileTypeGrid represent the 2d grid of the editor and speicifies the types of tiles
// present at a specific location.
TileManager::TileManager(Vec2 pos, int width, int height, int tileWidth, int tileHeight) : pos(pos), width(width),
height(height), tileWidth(tileWidth), tileHeight(tileHeight){
	tileGrid = new Tile * [height];

	// if tileTypeGrid is null, everything is the empty tile
		this->tileTypeGrid = new TileType * [height];
		for (int i = 0; i < height; i++) {
			this->tileTypeGrid[i] = new TileType[width];
			for (int j = 0; j < width; j++) {
				this->tileTypeGrid[i][j] = TileType::Empty;
			}
		}

	// populates the tile grid with the specfiied tiles in tileTypeGrid
	for (int i = 0; i < height; i++) {
		tileGrid[i] = new Tile[width];
		for (int j = 0; j < width; j++) {
			tileGrid[i][j] = Tile(pos + Vec2(j * tileWidth, i * tileHeight), tileWidth, tileHeight, TileManager::tileTextures.at(this->tileTypeGrid[i][j]), this->tileTypeGrid[i][j]);
		}
	}
}

int TileManager::getWidth() {
	return width;
}

int TileManager::getHeight() {
	return height;
}

int TileManager::getTileWidth() {
	return tileWidth;
}

int TileManager::getTileHeight() {
	return tileHeight;
}

Vec2 TileManager::getPos() {
	return pos;
}

void TileManager::render(SDL_Renderer* ren, Camera* camera) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			tileGrid[i][j].render(ren, camera);
		}
	}
}

