#include<TileMenu.hpp>
#include<stdio.h>

TileMenu::TileMenu() {

}

TileMenu::TileMenu(Vec2 pos, int width, int height, int tileWidth, int tileHeight, unordered_map<TileType, SDL_Texture*> tileTextures) :
	TileManager(pos, width, height, tileWidth, tileHeight) {

	// tile selection represents the menu of tiles that can be placed on the grid.
	tileSelection = new Tile * [size_t(height)];
	for (int j = 0; j < height; j++) {
		tileSelection[j] = new Tile[width];
	}

	int i = 0, j = 0;
	for (auto itr = tileTextures.begin(); itr != tileTextures.end(); ++itr) {
		if (j >= width) {
			i += 1;
			j = 0;
		}
		tileSelection[i][j] = Tile(pos + Vec2(j * tileWidth, i * tileHeight), tileWidth, tileHeight, itr->second, itr->first);
		
		j = j + 1;
	}


	while (i < height) {
		while (j < width) {
			tileSelection[i][j] = Tile(pos + Vec2(j * tileWidth, i * tileHeight), tileWidth, tileHeight, NULL, TileType::Empty);
			++j;
		}
		j = 0;
		++i;
	}

	selectedTileTypeIndex[0] = 0;
	selectedTileTypeIndex[1] = 0;
}

bool TileMenu::handleClick(Vec2 clickPos) {
	// if the mouse has clicked on the tile menu
	if (clickPos.x > pos.x && clickPos.x < pos.x + width * tileWidth && clickPos.y > pos.y && clickPos.y < pos.y + height * tileHeight) {
		selectedTileTypeIndex[0] = int((clickPos.y - pos.y) / tileHeight);
		selectedTileTypeIndex[1] = int((clickPos.x - pos.x) / tileWidth);
		return true;
	}

	return false;
}

// get the current selection of tile
TileType TileMenu::getSelectedTileType() {
	return tileSelection[selectedTileTypeIndex[0]][selectedTileTypeIndex[1]].getTileType();
}

void TileMenu::render(SDL_Renderer* ren, Camera* camera) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			tileSelection[i][j].render(ren);
		}
	}

	// render the grid lines with the selected tile in a special border color
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			SDL_Rect dest;
			Vec2 tilePos = tileSelection[i][j].getPos();
			dest.x = tilePos.x;
			dest.y = tilePos.y;
			dest.w = tileWidth;
			dest.h = tileHeight;

			if (i == selectedTileTypeIndex[0] && j == selectedTileTypeIndex[1]) {
				SDL_SetRenderDrawColor(ren, 255, 0,  0, 150);
			}
			else {
				SDL_SetRenderDrawColor(ren, 255, 255, 255, 100);
			}

			SDL_RenderDrawRect(ren, &dest);
		}
	}
}