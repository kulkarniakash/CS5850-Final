// NOTE: Most of the following code was written by Zejun Li from Akash's previous team (wecook)
#ifndef RESOURCE_MANAGER
#define RESOURCE_MANAGER

#include <SDL_Headers.hpp>


#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <fstream>

/**
 * @brief Enum class indicating the type of the resources in the resource manager
 */
enum class ResourceType {
	SoundEffect,
	BackgroundMusic,
	Font,
	EnglishLang,
	SpanishLang,
	SDLWindow,
	SDLRenderer,
	SDLTexture,
};

/**
 @brief This is a singleton class used for managing the resources in the game.
*/
class ResourceManager{

private:
	/*! the single instance ever will be created and used */
	static ResourceManager *inst;
	/*! empty constructor only used to create the first instance */
	ResourceManager() {};         	          

	/*! copy is not allowed */
	ResourceManager(ResourceManager const&);

	/*! assigning this instance is not allowed, either*/
	void operator=(ResourceManager const&); 

	/*! maps filepath to Mix_Chunk pointers*/
	std::unordered_map<std::string, Mix_Chunk*> mapSoundEffect;
	/*! maps filepath to Mix_Music pointers*/
	std::unordered_map<std::string, Mix_Music*> mapBackgroundMusic;
	/*! maps filepath to TTF_Font pointers*/
	std::unordered_map<std::string, TTF_Font*> mapFont;
	/*! maps window id(string) to window pointer */
	std::unordered_map<std::string, SDL_Window*> mapSDLWindow;
	/*! maps renderer id(string) to renderer pointer */
	std::unordered_map<std::string, SDL_Renderer*> mapSDLRenderer;
	/*! maps texture id(string) to texture pointer */
	std::unordered_map<std::string, SDL_Texture*> mapSDLTexture;

	
	/*! maps anguage types to a map that maps string token to the specific language specified
		by the key
	 */
    std::unordered_map<ResourceType, std::unordered_map<std::string, std::string>> mapLoadedLang;

	/**
	 * @brief This is a helper function to help parse file reading line
	 * as well as loading parsed content into mapLoadedLang
	 * @param[in] fileObj ifstream object
	 * @param[in] langType the language type to be parsed, so it knows where to 
	 * store this language content
	 */
	void parseAndLoad(std::ifstream& fileObj, ResourceType langType);

public:
	/**
		@brief returns the only instance of this class, if it doesn't exist yet,
		it will create the instance first
	*/
	static ResourceManager &getInstance();

	/**
	* @brief initializes all containers preparing for later usage
	*/
	void startUp();

	/**
	* @brief free all resources loaded
	*/
	void shutDown();


	/**
	 * @brief check if the designated resource is loaded
	this should be used before calling a getter method 
	 * @param[in] 
	*/
	bool hasResource(std::string const& keyOrFilePath, ResourceType type);


    /**
     * @brief check to see if a certain language has been loaded
     * @param[in] langType the specified language type
     */
    bool hasLanguage(ResourceType langType);

	/** @brief add a resource, the type of the resource should be provided 
	@param[in] filePath the file path of the resource to be loaded
	@param[in] type the type of this resource, so the manager knows where to store it
	@param[in] fontSize this is the default font size for the font to be loaded
	*/
	int addResource(std::string const& filePath, ResourceType type, int fontSize = 25);

	/**
	 * @brief adds a sdl window to resource manager
	 * @param[in] windowSpecifier the id of the window being added
	 * @param[in] windowTitle the title of the sdl window
	 * @param[in] x the x value of the window on the computer screen
	 * @param[in] y the y axis value of the window on the computer screen
	 * @param[in] width the width of the window
	 * @param[in] height the height of the window
	 * @param[in] flag the flag set to window, refer to SDL official documentation 
	 * https://wiki.libsdl.org/SDL_CreateWindow#flags
	 */
	int addWindow(std::string windowSpecifier, std::string windowTitle, int x, int y, int width, int height, Uint32 flag);

	/**
	 * @brief adds a renderer to resource manager
	 * @param[in] rendererSpecifier the id of the renderer being added
	 * @param[in] index refer to https://wiki.libsdl.org/SDL_CreateRenderer
	 * @param[in] flag refer to https://wiki.libsdl.org/SDL_CreateRenderer
	 */
	int addRenderer(std::string rendererSpecifier, std::string windowSpecifier, int index, Uint32 flag);

	/**
	 * @brief adds a texture to resource manager
	 * @param[in] textureSpecifier the id of the texture to be added
	 * @param[in] rendererSpecifier to create a texture, the renderer is needed, this is the id of
	 * the renderer that'll be used to create the texture
	 * @param[in] surface sdl surface that will be used to create texture
	 */
	int addTexture(std::string textureSpecifier, std::string rendererSpecifier, SDL_Surface *surface);

	/**
	 * @brief overloading addTexture, supporting loading a texture into resource manager directly from 
	 * a file path
	 * @param[in] textureSpecifier the file path of the image file
	 * @param[in] rendererSpecifier the id of the renderer needed to create a file
	 */ 
	int addTexture(std::string textureSpecifier, std::string rendererSpecifier);

	/**
	 * @brief adds texture to resource manager via file path of a jpg file
	 * @param[in] filePath the path of the jpg file
	 * @param[in] rendererSpecifier the id of a renderer stored in resource manager 
	 */ 
	int addJPG(std::string filePath, std::string rendererSpecifier);

	/**
	 * @brief adds a renderer to resource manager
	 * @param[in] rendererSpecifier the id of a renderer stored in resource manager
	 * @param[in] renderer the renderer to be added
	 */ 
	int addRenderer(std::string rendererSpecifier, SDL_Renderer* renderer);

	/** @brief load different language text for the game 
	 * @param[in] filePath the path of the specific language content
	 * @param[in] langType the type of the language to be loaded
	 * @param[in] needReload set to true if reload of a language is needed
	*/
	int addLanguage(std::string const& filePath, ResourceType langType, bool needReload);



	/**
	* @brief get sound effect resource based on the filepath provided
	* @param[in] filePath the id of the sound effect to be retrieved
	*/
	Mix_Chunk *getResourceSoundEffect(std::string const& filePath);

	/**
	 * @brief get background music resource based on the filepath provided
	 * @param[in] filePath the id of the background music to be retrieved
	*/
	Mix_Music *getResourceBackgroundMusic(std::string const& filePath);

	/**
	* @brief get font resource based on the filepath provided
	* @param[in] filePath the id of the font to be retrieved
	*/
	TTF_Font *getResourceFont(std::string const& filePath);

	/**
	 * @brief retrieve sdl window pointer
	 * @param[in] speicifer the id of the sdl window to be retrieved
	 */ 
	SDL_Window *getResourceSDLWindow(std::string const& specifier);

	/**
	 * @brief retrieve sdl renderer pointer
	 * @param[in] specifier the id of the sdl renderer to be retrieved
	 */ 
	SDL_Renderer *getResourceSDLRenderer(std::string const& specifier);

	/**
	 * @brief retrieve sdl texture pointer
	 * @param[in] specifier the id of the sdl texture to be retrieved
	 */ 
	SDL_Texture *getResourceSDLTexture(std::string const& specifier);

	/**
	 * @brief retrieve a string of a specified language
	 * @param[in] langType the language type
	 * @param[in] specifier the id of a string to be retrieved
	 */ 
	std::string getResourceLangStr(ResourceType langType, std::string const& specifier);

	// in the future probably introduce more methods

};


#endif