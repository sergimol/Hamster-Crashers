// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <cassert>
#include <iostream>

#include "Font.h"

class Animation {
public:

	Animation();


	Animation(Vector2D st, int dur, int c, int r, int fu, int lo, std::string ch);


	virtual ~Animation() {

	}

	inline Vector2D startFrame() const {
		return startFrame_;
	}

	inline int duration() const {
		return duration_;
	}

	inline int cols() const {
		return cols_;
	}

	inline int rows() const {
		return rows_;
	}

	inline int frameUpdate() const {
		return frameUpdate_;
	}

	inline bool loop() const {
		return loop_;
	}

	inline std::string chain() const {
		return chain_;
	}


private:

	Vector2D startFrame_;
	int duration_;
	int cols_;
	int rows_;
	int frameUpdate_;
	bool loop_;
	std::string chain_;
};
