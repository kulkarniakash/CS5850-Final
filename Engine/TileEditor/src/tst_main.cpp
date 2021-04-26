// Support Code written by Michael D. Shah
// Last Updated: 2/19/21
// Please do not redistribute without asking permission.


#include "tst_Engine.hpp" // The main engine
#include "tst_GraphicsEngineRenderer.hpp" // The renderering engine
#include <string>

std::string LEVEL_INPUT_FILE = "./assets/level1";
std::string LEVEL_OUTPUT_FILE = "./assets/level1";

/*@mainpage Tile Editor
*<table>
*<tr><th>Project<td>Platformer
*<tr><th>Author<td>Wecook
*</table>
*@section Program Details
*A tile editor used to create the tile map for the platformer. The program load the new_level text file in Assets and saves the modified tilemap
*to the same file.
*@section Instructions
*Build the build_tile_editor.py in the Game directory. Then run the tile_editor executable in the Game/bin directory.
*@section How to use
*Move the camera using the arrow keys. The tile menu is on the top-left corner.
*Select a tile from the tile menu by left-clicking on it. Then left clik on a tile in the grid to place the selected tile over there. Right click
*on a tile to delete it.
=======
/**@mainpage  Tile Editor
* <table>
* <tr><th>Project  <td>Platformer
* <tr><th>Author   <td>Wecook
* </table>
* @section   Project details
* A tile editor used to create the tile map for the platformer. The program load the new_level text file in Assets and saves the modified tilemap to the same file.
*
* @section   Instructions
* -# Build the build_tile_editor.py in the Game directory. Then run the tile_editor executable in the Game/bin directory.
*
* @section            How to use
* -# Move the camera using the arrow keys. The tile menu is on the top-left corner.
* -# Select a tile from the tile menu by left-clicking on it. Then left click on a tile in the grid to place the selected tile over there.
* -# Right click on a tile to delete it.
*
**********************************************************************************
*/

int TILE_WIDTH = -1;
int TILE_HEIGHT = -1;


int main(int argc, char** argv) {

	TILE_WIDTH = std::atoi(argv[1]);
	TILE_HEIGHT = std::atoi(argv[2]);

	// Create an instance of an object for our engine
	Engine engine;
	// Initialize the Engine Subsystems
	engine.InitializeGraphicsSubSystem();
	// Once all subsystems have been initialized
	// Start the engine
	engine.Start();
	// Run our program forever
	engine.MainGameLoop();
	// Explicitly call Shutdown to terminate our engine
	engine.Shutdown();
	// When our program ends, it will exit scope,
	// the destructor will then be called
	// and clean up the program.
	return 0;
}

