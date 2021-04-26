
#include "ResourceManager.hpp"

#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

ResourceManager *ResourceManager::inst = nullptr;

// return the only instance, this is probably not thread-safe
// need to change if multiple threads are used in the game
ResourceManager& ResourceManager::getInstance() {
	if (!inst) {
		inst = new ResourceManager();
	}
	return (*inst);
}

// 'equivalent' to our constructor
void ResourceManager::startUp() {
	// leave here for potential future usage
}

// 'equivalent' to our destructor
void ResourceManager::shutDown() {
	// free other resources
	for (auto& pair : mapSoundEffect) 
		Mix_FreeChunk(pair.second);

	for (auto& pair : mapBackgroundMusic)
		Mix_FreeMusic(pair.second);

	for (auto& pair : mapFont)
		TTF_CloseFont(pair.second);
	Mix_CloseAudio();
	Mix_Quit();
	TTF_Quit();
}

// check if the designated resource is loaded
// this should be used before calling a getter method
bool ResourceManager::hasResource(std::string const& keyOrFilePath, ResourceType type) {
	bool flag;
	switch (type) {
		case ResourceType::SoundEffect:
			flag = mapSoundEffect.count(keyOrFilePath) ? true : false;
			break;
		case ResourceType::BackgroundMusic:
			flag = mapBackgroundMusic.count(keyOrFilePath) ? true : false;
			break;

		case ResourceType::Font:
			flag = mapFont.count(keyOrFilePath) ? true : false;
			break;

		case ResourceType::SDLWindow:
			flag = mapSDLWindow.count(keyOrFilePath) ? true : false;
			break;

		case ResourceType::SDLRenderer:
			flag = mapSDLRenderer.count(keyOrFilePath) ? true : false;
			break;
		
		case ResourceType::SDLTexture:
			flag = mapSDLTexture.count(keyOrFilePath) ? true : false;
			break;

		default:
			flag = false;
	}
	return flag;
}

bool ResourceManager::hasLanguage(ResourceType langType) {
    return mapLoadedLang.count(langType) ? true : false;
}

// add a resource, the type of the resource should be provided
// return 0 : resource adde successfully
// return 1 : resource exists already
// return 2 : failed loading resource(SDL api error)
// return 3 : passed in non-existent resource type
int ResourceManager::addResource(std::string const& filePath, ResourceType type, int fontSize) {
	int indicator = 0;
	switch (type) {
		case ResourceType::SoundEffect:
			if (hasResource(filePath, type)) indicator = 1;
			else {
				Mix_Chunk *sound = Mix_LoadWAV(filePath.c_str());
				if (!sound) indicator = 2;
				else mapSoundEffect[filePath] = sound;
			}
			break;

		case ResourceType::BackgroundMusic:
			if (hasResource(filePath, type)) indicator = 1;
			else {
				Mix_Music *bgm = Mix_LoadMUS(filePath.c_str());
				if (!bgm) indicator = 2;
				else mapBackgroundMusic[filePath] = bgm;
			}
			break;

		case ResourceType::Font:
			if (hasResource(filePath, type)) indicator = 1;
			else {
				TTF_Font *font = TTF_OpenFont(filePath.c_str(), fontSize);
				if (!font) {
					indicator = 2;
				}
				else {
					mapFont[filePath] = font;
				}
			}
			break;

		case ResourceType::SDLTexture:
			if (hasResource(filePath, type)) indicator = 1;
			else {

			}

		default:
			indicator = 3;
	}
	return indicator;
}

void ResourceManager::parseAndLoad(std::ifstream& fileObj, ResourceType langType) {
	std::string line;
    std::string token;
	std::string specifier, word;
	mapLoadedLang[langType] = std::unordered_map<std::string, std::string>();
	while (std::getline(fileObj, line)) {
		std::istringstream ss(line);
		
		// word before '=' is the specifier
		std::getline(ss, token, '=');
		specifier = token;
		
		// word afterr '=' is the actual string
		std::getline(ss, token, '=');
		word = token;
		mapLoadedLang[langType][specifier] = word;
	}
}

// load a window into resource manager
// return 0 : window succefully loaded
// return 1 : failed at creating window (sdl api error)
int ResourceManager::addWindow(std::string windowSpecifier, std::string windowTitle, int x, int y, int width, int height, Uint32 flag) {
	int indicator = 0;
	SDL_Window *window = SDL_CreateWindow(windowTitle.c_str(), x, y, width, height, flag);
	if (!window) indicator = 1;
	else mapSDLWindow[windowSpecifier] = window;

	return indicator;
}

// return 0 : renderer successfully loaded
// return 1 : window specified does not exist yet, consider add window first
// return 2 : failed at creating renderer
int ResourceManager::addRenderer(std::string rendererSpecifier, std::string windowSpecifier, int index, Uint32 flag) {
	int indicator = 0;
	if (!mapSDLWindow.count(windowSpecifier)) indicator = 1;
	else {
		SDL_Renderer *renderer = SDL_CreateRenderer(mapSDLWindow[windowSpecifier], index, flag);
		if (!renderer) indicator = 2;
		else mapSDLRenderer[rendererSpecifier] = renderer;
	}
	return indicator;
}

int ResourceManager::addRenderer(std::string rendererSpecifier, SDL_Renderer* renderer) {
	if (mapSDLRenderer.count(rendererSpecifier)) return 1;
	mapSDLRenderer[rendererSpecifier] = renderer;
	return 0;
}

// since there are multiple ways to create a surface, resource manager takes in surface
// as a parameter, and create the texture then store it
// return 0 : texture successfully created and stored
// return 1 : renderer doesn't exist yet
// return 2 : failed at creating texture
int ResourceManager::addTexture(std::string textureSpecifier, std::string rendererSpecifier, SDL_Surface *surface) {
	int indicator = 0;
	if (!mapSDLRenderer[rendererSpecifier]) indicator = 1;
	else {
		SDL_Renderer *r = mapSDLRenderer[rendererSpecifier];
		SDL_Texture *texture = SDL_CreateTextureFromSurface(r, surface);
		if (!texture) indicator = 2;
		else mapSDLTexture[textureSpecifier] = texture;
	}
	return indicator;
}


int ResourceManager::addTexture(std::string textureSpecifier, std::string rendererSpecifier) {
	int indicator = 0;
	if (!mapSDLRenderer[rendererSpecifier]) indicator = 1;
	else {
		SDL_Renderer* r = mapSDLRenderer[rendererSpecifier];
		SDL_Surface* surface = IMG_Load(textureSpecifier.c_str());
		SDL_Texture* texture = SDL_CreateTextureFromSurface(r, surface);
		if (!texture) indicator = 2;
		else mapSDLTexture[textureSpecifier] = texture;
	}
	return indicator;
}

// return 0 : texture successfully created and stored
// return 1 : renderer doesn't exist yet
// return 2 : failed at creating texture
// return 3 : failed at loading JPG image
int ResourceManager::addJPG(std::string filePath, std::string rendererSpecifier) {
	SDL_Surface* image;
	SDL_RWops* rwop;
	int indicator = 0;
	if (!mapSDLRenderer[rendererSpecifier]) indicator = 1;
	SDL_Renderer* r = mapSDLRenderer[rendererSpecifier];
	rwop = SDL_RWFromFile(filePath.c_str(), "rb");
	image = IMG_LoadJPG_RW(rwop);
	if (!image) {
		printf("IMG_LoadJPG_RW: %s\n", IMG_GetError());
		indicator = 3;
		// handle error
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(r, image);
	if (!texture) indicator = 2;
	else mapSDLTexture[filePath] = texture;

	return indicator;
}

// load different language text for the game
// return 0 : language loaded successfully
// return 1 : failed to open specified file
// return 2 : no matched language type
// set needReload to true if language source file is changed
int ResourceManager::addLanguage(std::string const& filePath, ResourceType langType, bool needReload) {
    int indicator = 0;
    std::ifstream langFile(filePath);
    if (!langFile) indicator = 1;
	switch (langType) {
		case ResourceType::EnglishLang:
			// don't reload
			if (mapLoadedLang.count(langType) && !needReload) return indicator;
			parseAndLoad(langFile, langType);
			break;
	
		case ResourceType::SpanishLang:
			if (mapLoadedLang.count(langType) && !needReload) return indicator;
			parseAndLoad(langFile, langType);
			break;

		default:
			indicator = 2;
            std::cout << "loadLanguage: no matched case found.\n";
	}
    return indicator;
}


// getter methods, use hasResource before use a getter method
Mix_Chunk *ResourceManager::getResourceSoundEffect(std::string const& filePath) {
	return mapSoundEffect[filePath];
}

Mix_Music *ResourceManager::getResourceBackgroundMusic(std::string const& filePath) {
	return mapBackgroundMusic[filePath];
}

TTF_Font *ResourceManager::getResourceFont(std::string const& filePath) {
	return mapFont[filePath];
}


SDL_Window *ResourceManager::getResourceSDLWindow(std::string const& specifier) {
	return mapSDLWindow[specifier];
}


SDL_Renderer *ResourceManager::getResourceSDLRenderer(std::string const& specifier) {
	return mapSDLRenderer[specifier];
}

SDL_Texture *ResourceManager::getResourceSDLTexture(std::string const& specifier) {
	return mapSDLTexture[specifier];
}

// call hasLanguage before calling this method, also make sure the specifier is correct
// and exists
std::string ResourceManager::getResourceLangStr(ResourceType langType, std::string const& specifier) {
	return mapLoadedLang[langType][specifier];
}


