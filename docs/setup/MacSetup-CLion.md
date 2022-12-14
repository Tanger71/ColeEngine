# Mac Setup w/ CLion

Meethod found [here](https://medium.com/@navidsarhady/how-to-create-your-first-sdl2-project-using-clion-ide-in-macos-9155764d5765).

```ssh
brew install sdl2
brew install sdl2_image
brew install sdl2_mixer
brew install sdl2_ttf
```

Fork from [Boilerplate](https://github.com/JodyAndrews/SDL2_Basic_Setup.git).

`CMakeLists.txt`
```CMake
cmake_minimum_required(VERSION 3.13.1)  
  
Message("")  
Message( STATUS "CMAKE_BINARY_DIR: " ${CMAKE_BINARY_DIR} )  
Message( STATUS "CMAKE_SOURCE_DIR: " ${CMAKE_SOURCE_DIR} )  
Message( STATUS "CMAKE_COMMAND: " ${CMAKE_COMMAND} )  
Message( STATUS "CMAKE_VERSION: " ${CMAKE_VERSION} )  
Message( STATUS "CMAKE_C_COMPILER: " ${CMAKE_C_COMPILER} )  
Message( STATUS "CMAKE_PROJECT_NAME: " ${CMAKE_PROJECT_NAME} )  
Message( STATUS "CMAKE_FINDCMAKE: " ${CMAKE_SOURCE_DIR}/CMAKE )  
  
project(ColeEngine)  
  
# ------- Set Vars ------- #  
  
set(CMAKE_CXX_STANDARD 17)  
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)  
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMAKE")  
set(SOURCE_FILES    src/main.cpp src/Game.cpp src/Game.h src/TextureManager.cpp src/TextureManager.h src/GameObject.cpp src/GameObject.h src/Map.cpp src/Map.h src/ECS/ECS.h src/ECS/Components.h src/ECS/SpriteComponent.h src/ECS/TransformComponent.h src/Vector2D.h src/Vector2D.cpp)  
  
Message("")  
Message( STATUS "SOURCE entry point : " ${SOURCE_FILES} )  
Message("")  
  
# ------- End Set Vars --- #  
  
# ------- Executable ----- #  
  
ADD_EXECUTABLE(ColeEngine ${SOURCE_FILES})  
  
# ------- End Executable - #  
  
# ------- Finds ---------- #  
  
FIND_PACKAGE(SDL2 REQUIRED)  
Message("")  
Message( STATUS "FINDING SDL2" )  
IF (${SDL2_FOUND})  
    Message( STATUS "SDL2_FOUND: " ${SDL2_FOUND})  
    Message( STATUS "SDL2_INCLUDE_DIR:" ${SDL2_INCLUDE_DIR})  
    Message( STATUS "SDL2_LIBRARY: " ${SDL2_LIBRARY})  
ELSE()  
    Message( STATUS "SDL2_FOUND: " ${SDL2_FOUND})  
    Message( FATAL_ERROR "SDL2 NOT FOUND" )  
ENDIF()  
  
FIND_PACKAGE(SDL2_IMAGE)  
Message("")  
Message( STATUS "FINDING SDL2_IMAGE" )  
Message( STATUS "SDL2_IMAGE_FOUND: " ${SDL2_IMAGE_FOUND})  
IF (${SDL2_IMAGE_FOUND})  
    Message( STATUS "SDL2_IMAGE_INCLUDE_DIR: " ${SDL2_IMAGE_INCLUDE_DIR})  
    Message( STATUS "SDL2_IMAGE_LIBRARY: " ${SDL2_IMAGE_LIBRARY})  
ELSE()  
    Message( FATAL_ERROR "SDL2_IMAGE NOT FOUND" )  
ENDIF()  
  
FIND_PACKAGE(SDL2TTF)  
Message("")  
Message( STATUS "FINDING SDL2TTF" )  
Message( STATUS "SDL2TTF_FOUND: " ${SDL2TTF_FOUND} )  
IF (${SDL2TTF_FOUND})  
    Message( STATUS "SDL2TTF_INCLUDE_DIR: " ${SDL2TTF_INCLUDE_DIR})  
    Message( STATUS "SDL2TTF_LIBRARY: " ${SDL2TTF_LIBRARY})  
ELSE()  
    Message( FATAL_ERROR "SDL2TTF NOT FOUND" )  
ENDIF()  
Message("")  
  
FIND_PACKAGE(SDL2Mixer)  
  
Message( STATUS "FINDING SDL2Mixer" )  
Message( STATUS "SDL2Mixer_FOUND: " ${SDL2Mixer_FOUND} )  
  
Message("")  
  
file(COPY assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})  
  
# ------- End Finds ------ #  
  
# ------- Inc & Link ---- #  
  
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIR} ${SDL2TTF_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2Mixer_INCLUDE_DIR})  
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2TTF_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2Mixer_LIBRARY} )  
  
# ------- End ----------- #
```

