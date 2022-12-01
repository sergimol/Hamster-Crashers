// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "SDL.h"
#include <string>
#include <map>
#include <fstream>
#include <iostream>

#include "../utils/Singleton.h"
#include "RandomNumberGenerator.h"
#include "Font.h"
#include "Music.h"
#include "SoundEffect.h"
#include "Texture.h"
#include "VirtualTimer.h"
#include "Animation.h"

using namespace std;

const int RESOLUTIONSCOUNT = 7;

class SDLUtils: public Singleton<SDLUtils> {

	friend Singleton<SDLUtils> ; // needed to give access to private constructors

public:

	// we abstract away the actual data structure we use for
	// tables. All we assume is that is has the following
	// methods
	//
	//   emplace(key,value)
	//   at(key)
	//   clear()
	//
	template<typename T>
	using sdl_resource_table = std::map<std::string,T>;

	virtual ~SDLUtils();

	// cannot copy/move
	SDLUtils(SDLUtils&) = delete;
	SDLUtils(SDLUtils&&) = delete;
	SDLUtils& operator=(SDLUtils&) = delete;
	SDLUtils& operator=(SDLUtils&&) = delete;

	// access to the underlying SDL_Window -- in principle not needed
	inline SDL_Window* window() {
		return window_;
	}

	// access to the underlying SDL_Renderer -- needed when creating textures
	// other than those initialized in this class
	inline SDL_Renderer* renderer() {
		return renderer_;
	}

	// clear the renderer with a given SDL_Color
	inline void clearRenderer(SDL_Color bg = build_sdlcolor(0x0000000)) {
		SDL_SetRenderDrawColor(renderer_, COLOREXP(bg));
		SDL_RenderClear(renderer_);
	}

	// present the current content of the renderer
	inline void presentRenderer() {
		SDL_RenderPresent(renderer_);
	}

	// the window's width
	inline int width() {
		return width_;
	}

	// the window's height
	inline int height() {
		return height_;
	}
	
	inline int hamstersToChoose() {
		return hamstersToChoose_;
	}
	
	inline int hamstersChosen() {
		return hamstersChosen_;
	}

	inline Vector2D volumes() {
		return Vector2D(musicVol_, fxVol_);
	}

	inline void setResolution() {
		width_ = widths_[resolutionIndex_];
		height_ = heights_[resolutionIndex_];

		SDL_SetWindowSize(window_, width_, height_);
		SDL_RenderSetScale(renderer_, width_ / 1920.0f, height_ / 1080.f);
	}

	inline Vector2D getResolutionRelation() const& {
		return Vector2D(width_ / 1920.0f, height_ / 1080.0f);
	}

	inline void lowerResolution() {
		if (resolutionIndex_ > 0)
			resolutionIndex_--;
		else
			resolutionIndex_ = RESOLUTIONSCOUNT - 1;

		setResolution();
	}

	inline void setResolutionIndex(int i) {
		resolutionIndex_ = i;

		setResolution();
	}

	inline void higherResolution() {
		if (resolutionIndex_ < RESOLUTIONSCOUNT - 1)
			resolutionIndex_++;
		else
			resolutionIndex_ = 0;

		setResolution();
	}

	inline string resolutionString(int i) {
		return to_string((int)widths_[i]) + "x" + to_string((int)heights_[i]);
	}

	inline int resolutionIndex() {
		return resolutionIndex_;
	}

	inline void setWidth(int widthAux) {
		width_ = widthAux;
	}

	inline void setHeight(int heightAux) {
		height_ = heightAux;
	}

	inline void setHamstersToChoose(int hamsters) {
		hamstersToChoose_ = hamsters;
	}
	
	inline void setHamstersChosen(int hamsters) {
		hamstersChosen_ = hamsters;
	}

	inline void setMusicVol(float v) {
		musicVol_ = v;
	}

	inline void setFxVol(float v) {
		fxVol_ = v;
	}

	inline bool angelUnlocked() {
		return angelUnlocked_;
	}
	
	inline bool tutorialDone() {
		return tutorialDone_;
	}

	inline void setTutorialDone() {
		tutorialDone_ = true;
	}

	inline void setTutorialUndone() {
		tutorialDone_ = false;
	}

	inline void unlockAngel() {
		angelUnlocked_ = true;
	}

	// toggle to full-screen/window mode
	inline void toggleFullScreen() {
		auto flags = SDL_GetWindowFlags(window_);
		if (flags & SDL_WINDOW_FULLSCREEN) {
			SDL_SetWindowFullscreen(window_, 0);
		} else {
			SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN);
		}
	}

	// show the cursor when mouse is over the window
	inline void showCursor() {
		SDL_ShowCursor(1);
	}

	// hide the cursor when mouse is over the window
	inline void hideCursor() {
		SDL_ShowCursor(0);
	}

	// All resource maps can be modified from outside, this way you can store
	// your own dynamically. Be careful when modifying them!

	// fonts map
	inline sdl_resource_table<Font>& fonts() {
		return fonts_;
	}

	// images map
	inline sdl_resource_table<Texture>& images() {
		return images_;
	}

	// messages map
	inline sdl_resource_table<Texture>& msgs() {
		return msgs_;
	}

	// sound effects map
	inline sdl_resource_table<SoundEffect>& soundEffects() {
		return sounds_;
	}

	// musics maps
	inline sdl_resource_table<Music>& musics() {
		return musics_;
	}

	// animations maps
	inline sdl_resource_table<Animation>& anims() {
		return anims_;
	}


	// Access to the random number generator. It is important to always
	// use this generator, this way you can regenerate the same sequence
	// if you start from the same seed
	inline RandomNumberGenerator& rand() {
		return random_;
	}

	// Access to the virtual timer, it is useful when you allow to 'pause'
	// your game, also for synchronising clocks of players (when using sdlnet)
	inline VirtualTimer& virtualTimer() {
		return timer_;
	}

	// Access to real time
	inline Uint32 currRealTime() const {
		return SDL_GetTicks();
	}

	inline float lerp(float a, float b, float f) const{
		return (a + f * (b - a));
	}

	void loadData();
	void saveData();

private:
	SDLUtils();
	SDLUtils(std::string windowTitle, int width, int height);
	SDLUtils(std::string windowTitle, int width, int height,
			std::string filename);

	void initWindow();
	void closeWindow();
	void initSDLExtensions(); // initialize resources (fonts, textures, audio, etc.)
	void closeSDLExtensions(); // free resources the
	void loadReasources(std::string filename); // load resources from the json file

	std::string windowTitle_; // window title
	int width_; // window width
	int height_; // window height
	int hamstersToChoose_; // número de hamsters a elegir en el menú de selección
	int hamstersChosen_; // número de hamstes ya elegidos

	SDL_Window *window_; // the window
	SDL_Renderer *renderer_; // the renderer

	sdl_resource_table<Font> fonts_; // fonts map (string -> font)
	sdl_resource_table<Texture> images_; // textures map (string -> texture)
	sdl_resource_table<Texture> msgs_; // textures map (string -> texture)
	sdl_resource_table<SoundEffect> sounds_; // sounds map (string -> sound)
	sdl_resource_table<Music> musics_; // musics map (string -> music)
	sdl_resource_table<Animation> anims_; //animations map (string -> animation)

	RandomNumberGenerator random_; // (pseudo) random numbers generator
	VirtualTimer timer_; // virtual timer

	// Arrays con ancho y alto de todas las resoluciones
	float widths_[RESOLUTIONSCOUNT] = { 800, 854, 1024, 1280, 1280, 1280, 1920 };
	float heights_[RESOLUTIONSCOUNT] = { 600, 480, 768, 720, 960, 1024, 1080 };
	// Indice de la resolución actual dentro de los arrays
	int resolutionIndex_;
	bool angelUnlocked_;
	bool tutorialDone_;
	float fxVol_;
	float musicVol_;
};


// This macro defines a compact way for using the singleton SDLUtils, instead of
// writing SDLUtils::instance()->method() we write sdlutils().method()
//
inline SDLUtils& sdlutils() {
	return *SDLUtils::instance();
}
