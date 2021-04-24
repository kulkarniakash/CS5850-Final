#include<TileEditor.hpp>
#include<fstream>

std::unordered_map<TileType, std::string> TileEditor::tilePaths = std::unordered_map<TileType, std::string>{};

TileEditor::TileEditor(Vec2 pos, int width, int height, int tileWidth, int tileHeight) : TileManager(pos, 
	width, height, tileWidth, tileHeight) {

	// hard coded for now, change later!!
	int tileMenuColumns = 2;
	int tileMenuRows = 8;

	tileMenu = TileMenu(Vec2(0, 0), 2, tileMenuRows, (SCREEN_HEIGHT / tileMenuRows), SCREEN_HEIGHT / tileMenuRows, TileManager::tileTextures);
}

void TileEditor::handleClick(Vec2 clickPos, Camera* camera, Click click) {
	// first checks to see if the click is handled by tileMenu (i.e. the user has clicked on the menu). If not, handle click again
	if (!tileMenu.handleClick(clickPos)) {
		Vec2 actualPos = camera->getObjectPos(pos);
		// if the user has clicked anywhere in the tile editor grid region, handle the click
		if (clickPos.x > actualPos.x && clickPos.x < actualPos.x + width * tileWidth && clickPos.y > actualPos.y&& clickPos.y < actualPos.y + height * tileHeight) {
			
			int rowClicked = int((clickPos.y - actualPos.y) / tileHeight);
			int colClicked = int((clickPos.x - actualPos.x) / tileWidth);
			
			

			TileType newTileType = tileMenu.getSelectedTileType();
			

			if (click == Click::Right) {
				newTileType = TileType::Empty;
			}

			SDL_Texture* newTexture = TileManager::tileTextures.at(newTileType);
			Tile currentTile = tileGrid[rowClicked][colClicked];
			tileGrid[rowClicked][colClicked] = Tile(currentTile.getPos(), currentTile.getWidth(), currentTile.getHeight(), newTexture, newTileType);
		}
	}
}

void TileEditor::render(SDL_Renderer* ren, Camera* camera) {
	TileManager::render(ren, camera);

	// in additon to calling the render function of its parent, tiel editor draws white squares around each tile
	// , thus forming a grid
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			SDL_SetRenderDrawColor(ren, 255, 255, 255, 150);
			SDL_Rect dest = SDL_Rect();
			Vec2 correctedPos = camera->getObjectPos(tileGrid[i][j].getPos());
			dest.x = correctedPos.x;
			dest.y = correctedPos.y;
			dest.w = tileWidth;
			dest.h = tileHeight;
			SDL_RenderDrawRect(ren, &dest);
		}
	}

	tileMenu.render(ren, camera);
}

void TileEditor::loadLevelMap(std::string path) {
	SDL_RWops* file = SDL_RWFromFile(path.c_str(), "r");
	if (file == nullptr) {
		SDL_Log("Cannot read tile map file.");
		//exit(1);
	}


	char gData[400000] = { 0 };

	SDL_RWread(file, gData, 400000, 1);
	SDL_RWclose(file);

	// parse the file to get the tile map
	int i = 0;
	std::string cur = "";
	while (gData[i] != '\r') {
		if (gData[i] == ' ') {
			height = stoi(cur);
			cur = "";
		}
		else {
			cur.push_back(gData[i]);
		}
		i++;
	}
	i++;
	width = stoi(cur);
	cur = "";

	tileGrid = new Tile * [height];
	for (int i = 0; i < height; i++) {
		this->tileGrid[i] = new Tile[width];
	}
	

	int r = 0, c = 0;
	int count = 0;
	while (gData[i] != 0) {
		if (gData[i] == ' ' || gData[i] == '\r') {
			count++;
			TileType type = static_cast<TileType>(stoi(cur));
			cur = "";
			Vec2 pos(c * tileWidth, r * tileHeight);
			tileGrid[r][c] = Tile(pos, tileWidth, tileHeight, TileManager::tileTextures.at(type), type);
			if (r == 10) {
				printf("bad type: %d", tileGrid[r][c].getTileType());
			}
			if (gData[i] == '\r') {
				c = 0;
				r++;
				// i++;
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
	printf("count: %d\n", count);

}

void TileEditor::saveLevelToFile(string path) {
		std::ofstream tileMapFile (path, std::ofstream::out);
		// tileMapFile.open(path);
		std::string line = "";
		std::string typeCode;
		// write row and col
		tileMapFile << std::to_string(height) + " " + std::to_string(width) + "\n";
		// write the entire tile map
		for (int r = 0; r < height; ++r) {
			line = "";
			for (int c = 0; c < width; ++c) {
				typeCode = std::to_string(static_cast<int>(tileGrid[r][c].getTileType()));
				line += typeCode + " ";
			}
			line.pop_back();
			line += "\n";
			tileMapFile << line;
		}
		line += "\n\n";
		tileMapFile.close();
}