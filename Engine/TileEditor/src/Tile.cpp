#include<Tile.hpp>

Tile::Tile () {

}

Tile::Tile(Vec2 pos, int width, int height, SDL_Texture* texture, TileType type, SDL_Rect src): pos ( pos ), width(width), height(height), texture(texture), src(src), type(type) {

}

Vec2 Tile::getPos() {
	return pos;
}

int Tile::getWidth() {
	return width;
}

int Tile::getHeight() {
	return height;
}

TileType Tile::getTileType() {
	return type;
}

SDL_Texture* Tile::getTexture() {
	return texture;
}

void Tile::render(SDL_Renderer* ren, Camera* camera) {
	SDL_Rect dest;

	// corrects the object's position according to the camera's position
	Vec2 absolutePos;
	if (camera != NULL) {
		absolutePos = camera->getObjectPos(pos);
	}
	else {
		absolutePos = pos;
	}

	dest.x = absolutePos.x;
	dest.y = absolutePos.y;
	dest.w = width;
	dest.h = height;

	// if texture is null, just draw a rectangle. Else, render the texture
	if (texture != NULL) {
		if (src.w <= 0) {
			SDL_RenderCopy(ren, texture, NULL, &dest);
		}
		else {
			SDL_RenderCopy(ren, texture, &src, &dest);
		}
	}
	else {
		SDL_RenderDrawRect(ren, &dest);
	}
}