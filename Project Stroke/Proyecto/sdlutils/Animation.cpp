// This file is part of the course TPV2@UCM - Samir Genaim

#include "Animation.h"


Animation::Animation(Vector2D st, int dur, int c, int r, int fu, int lo, std::string ch) {
	
	startFrame_ = st;
	duration_ = dur;
	cols_ = c;
	rows_ = r;
	frameUpdate_ = fu;
	if (lo == 1) loop_ = true;
	else loop_ = false;
	chain_ = ch;
}

