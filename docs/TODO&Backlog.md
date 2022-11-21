# TODO & Backlog

[Boilerplate](https://github.com/JodyAndrews/SDL2_Basic_Setup.git)

- [x] Get enviroment running on MacOS
- [x] Get enviroment running on Windows10
- [x] init Readme.md
- [x] comment code for readability (Doxygen)
- [ ] make env more robust
	- [x] add .ddl injection for SDL2 bins
- [ ] fix keyboard input and ripple effects:
	- [x] animation misfires
	- [x] movement direction misfires
	- [ ] fix when release one opposite side, it maintains key press
- [ ] fix collison
	- [ ] self-collision checks
	- [ ] stuck on wall
- [ ] UI containers... hold diff types of UI elements.
- [ ] dont render stuff outside screen
- [ ] Follow `TODO: learn`  points 
- [ ] Refactor Code
	- [ ] variable naming
	- [ ] method/function nameing
	- [ ] efficiency
- [ ] Up robustness
	- [ ] improve memory cleanup
- [ ] set up PISKEL for map making workflow [here](https://www.piskelapp.com)
	- [ ] or Tiled preferribly acc
	- [ ] [https://youtu.be/1Ojoz24IWt0](https://www.youtube.com/watch?v=1Ojoz24IWt0&t=0s)

### current features:
- ECS component manager
- AABB Collision (no rotation)

### Issues
- [x] Camera Bounds are wrong

### possible issues with current implementation:
1. I was doing a bit of fiddling around and it turns out that the stringstream used for the UI is eating up memory and removing it stops it from using up excess memory, so maybe in future you could find a way to display text onscreen without using excess memory! Nice videos as usual!
   
   Just using stringstream shouldn't cause memory leaks, there is clearly a bug in the code resulting in this behavior. For a little 2d game I prefer to make a 2dText class that is basically a tile sheet like he has already made for the games tiles and each square is a new letter on the texture. Lazy foo has a description and implementation of this on their website, http://lazyfoo.net/tutorials/SDL/ , if you were interested.
   
   hello, it's the ui label component expecting something and not receiving it.

2. I was looking at the vector class operator overloads. It seems the basic vector to vector operations were altering the first vector, not just returning the result. That might be good for something like v1.Add(v2); but if you do v3 = v1 + v2; then v1 is modified also.

### cool links
- https://opengameart.org/
- https://www.youtube.com/playlist?list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx
- https://jothepro.github.io/doxygen-awesome-css/
- 