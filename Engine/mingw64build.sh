# Run with sh mingw64build.sh


COMPILE="g++ -D MINGW -std=c++14 -shared -fPIC -static-libgcc -static-libstdc++ -I./include/ -I./pybind11/include/ -I./../common/thirdparty/old/glm/ -L./lib/ `python3.6 -m pybind11 --includes` ./src/*.cpp -o Engine.pyd `python3.6-config --ldflags` -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer -mwindows -L libwinpthread-1.dll"


echo $COMPILE
echo "-------------------------------------------"
eval $COMPILE
