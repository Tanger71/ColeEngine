NOTE: going to make this more robust later, this is just the temporary setup.

Method found [here](https://blog.ahmadz.ai/sdl2-for-clion-and-cmake/).

1. Download mingw.zip: 
- https://github.com/libsdl-org/SDL/releases
- https://github.com/libsdl-org/SDL_image/releases
- https://github.com/libsdl-org/SDL_mixer/releases
- https://github.com/libsdl-org/SDL_ttf/releases

2. Extract all somewhere and make their respoective enviroment vars.
- $SDL2
- $SDL2_IMAGE
- $SDL2_MIXER
- $SDL2TTFDIR

3. Run MakeCLists.txt

4. Extract respective `.ddl` files from `bin/` and add directory called `<projRoot>\sdl2bins\`

5. Run program!