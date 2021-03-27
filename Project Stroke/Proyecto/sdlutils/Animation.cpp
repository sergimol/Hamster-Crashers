// This file is part of the course TPV2@UCM - Samir Genaim

#include "Animation.h"


Animation::Animation(Vector2D st, int dur, int c, int r, int fu) {
	
	startFrame_ = st;
	duration_ = dur;
	cols_ = c;
	rows_ = r;
	frameUpdate_ = fu;
}

