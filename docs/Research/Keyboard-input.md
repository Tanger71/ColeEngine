# Keyboard Input

### notes
- `SDL_GetKeyState`
- 

### Old implementation
will be good when implementing scrolling lists with keyboard... because SDL pumps out multiple key events when holding down keys... but we dont want this for player controls.

```C++
	/**
     * @brief update the component: handle key input.
     */
	void update() override {
		if (Game::event.type == SDL_KEYDOWN) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_w:
				transform->velocity.y = -1;
				sprite->Play("Walk");
				break;
			case SDLK_a:
				transform->velocity.x = -1;
				sprite->Play("Walk");
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_s:
				transform->velocity.y = 1;
				sprite->Play("Walk");
				break;
			case SDLK_d:
				transform->velocity.x = 1;
				sprite->Play("Walk");
				break;
			case SDLK_ESCAPE:
				Game::isRunning = false;
			default:
				break;
			}
		}
	}
```

### good links
https://stackoverflow.com/questions/11699183/what-is-the-best-way-to-read-input-from-keyboard-using-sdl
https://www.libsdl.org/release/SDL-1.2.15/docs/html/guideinputkeyboard.html