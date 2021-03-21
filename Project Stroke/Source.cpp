// This file is part of the course TPV2@UCM - Samir Genaim

#include <iostream>
#include <memory>
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_net.h"
#include "SDL_image.h"
#include "box2d.h"
#include "tmxlite/include/Config.hpp"

#include "Proyecto/game/Game.h"

void start() {
	Game g;

	g.init();
	g.start();
}


int main(int, char**) {

	try {
		start();
	}
	catch (const std::string& e) { // catch exceptions thrown as strings
		std::cerr << e << std::endl;
	}
	catch (const char* e) { // catch exceptions thrown as char*
		std::cerr << e << std::endl;
	}
	catch (const std::exception& e) { // catch exceptions thrown as a sub-type of std::exception
		std::cerr << e.what();
	}
	catch (...) {
		std::cerr << "Caught and exception of unknown type ...";
	}

	return 0;
}