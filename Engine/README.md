## Add any additional notes here

*Follow compilation instructions to build and run the game.*

*To play the game, use the WASD keys to control the spaceship. The objective of the goal is to avoid crashing into planets and comets for the given time. You are trying to survive by waiting for your spaceship's barrier to recharge. You will be dragged and pulled towards the planet due to their gravitational fields. Try to balance out your movement with the pull to avoid collisions!*

*Our "WoW" factor (special game feature) is our physics engine with its gravitational fields! We were able to create a realistic gravitational field with objects to simulate an orbit system, which we utilized to create our game.*

## Game/Engine Publicity

**Project Website**: *https://rumanstheddy.github.io/CS4850-FinalProject-website/* (See part 3)

## Compilation Instructions

The Readme that it included in the repository is compatible with Windows.

*For Windows:*
- Check TileEditor README and follow instructions
- sh mingw64build.sh
- python3 main.py -m ./Engine.pyd

*For Linux:*
- Check TileEditor README and follow instructions
- python3 linuxbuild.py
- python3 main.py

*For Mac:*
- Check TileEditor README and follow instructions
- python3 macbuild.py
- python3 main.py

## Project Hieararchy

In the future, other engineers may take on our project, so we have to keep it organized given the following requirements below. Forming some good organization habits now will help us later on when our project grows as well. These are the required files you should have 

### ./Engine Directory Organization

- Docs 
    - Source Code Documentation
- Assets
    - Art assets (With the Sub directories music, sound, images, and anything else)
- src
    - source code(.cpp files) The make file or any build scripts that automate the building of your project should reside here.
- include
    - header files(.h and .hpp files)
- lib
    - libraries (.so, .dll, .a, .dylib files). Note this is a good place to put SDL
- bin
    - This is the directory where your built executable(.exe for windows, .app for Mac, or a.out for Linux) and any additional generated files are put after each build.
- EngineBuild (Optional)
    - You may optionally put a .zip to you final deliverable. One should be able to copy and paste this directory, and only this directory onto another machine and be able to run the game. This is optional because for this course we will be building your projects from source. However, in the game industry it is useful to always have a build of a game ready for testers, thus a game project hieararchy would likely have this directory in a repo or other storage medium.
- ThirdParty
    - Code that you have not written if any.

**Note: For the final project you may add additional directories if you like, for example for your game which demonstrates your engine works.** 

**Additional Notes:** 

1. src and include should only contain ".cpp" or ".hpp" files. Why? It makes it very fast to do a backup of your game project as one example. Secondly, binary files that are generated often clutter up directories. I should not see any binaries in your repository, you may use a '.gitignore' file to help prevent this automatically. 
