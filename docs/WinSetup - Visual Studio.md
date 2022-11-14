NOTE: going to make this more robust later, this is just the temporary setup.

Download mingw.zip: 
- https://github.com/libsdl-org/SDL/releases
- https://github.com/libsdl-org/SDL_image/releases
- https://github.com/libsdl-org/SDL_mixer/releases
- https://github.com/libsdl-org/SDL_ttf/releases

Extract all and make their respoective enviroment vars.
- $SDL2
- $SDL2_IMAGE
- $SDL2_MIXER
- $SDL2TTFDIR

Run MakeCLists.txt

extract respective ddl files and add them to  `out\build\x64-Debug\bin`.

Run program!