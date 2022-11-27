#pragma once

/**
 * @brief Struct to handle the Animations
 *
 * @author sawyercoletang
 *
 */
struct Animation {
	int index;
	int frames;
	int speed;

	Animation() = default;

    /**
     *
     * @param i index of animation on tile-sheet
     * @param f frames in animation
     * @param s speed of animation (time in milliseconds delay between frames)
     */
	Animation(int i, int f, int s) {
		index = i;
		frames = f;
		speed = s;
	}
};