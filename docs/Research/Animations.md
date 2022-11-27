# Animations

## Requirements
- Initialize with animation
- set animation to play once and then loop another (Transitions)
	- Possibly a state system

https://stackoverflow.com/questions/28012390/animation-manager-design-pattern

### Implementation
- make `animations` map static in AnimationManager... here is factory as well... 
- each Entity.SpriteComponent will keep track of which animation (by std::string key) and their current frame... 
	- update frame for each tick (take in # of ticks per frame and mod by total frames in anim)