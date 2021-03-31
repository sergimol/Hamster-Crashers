// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <iostream>
#include <SDL.h>
#include <array>
#include <queue>
#include <map>
#include "../utils/Vector2D.h"

#include "../utils/Singleton.h"

using namespace std;

// Instead of a Singleton class, we could make it part of
// SDLUtils as well.

class InputHandler: public Singleton<InputHandler> {

	friend Singleton<InputHandler> ;

public:
	enum MOUSEBUTTON : uint8_t {
		LEFT = 0, MIDDLE = 1, RIGHT = 2
	};

	enum GAMEPADSTICK : uint8_t {
		LEFTST = 0, RIGHTST = 1
	};

	enum GAMEPADTRIGGER : uint8_t {
		LT = 0, RT = 1
	};

	virtual ~InputHandler() {
		for (int i = 0; i < maxConnectedControllers_; ++i) {
			delete leftJoysticks_[i];
			leftJoysticks_[i] = nullptr;

			delete rightJoysticks_[i];
			rightJoysticks_[i] = nullptr;
		}
	}

	// clear the state
	inline void clearState() {
		isKeyDownEvent_ = false;
		isKeyUpEvent_ = false;
		isMouseButtonEvent_ = false;
		isMouseMotionEvent_ = false;
		isButtonDownEvent_ = false;
		isButtonUpEvent_ = false;
		isAxisMotionEvent_ = false;
		for (auto i = 0u; i < 3; i++) {
			mbState_[i] = false;
		}
	}

	// update the state with a new event
	inline void update(const SDL_Event &event) {
		switch (event.type) {
		case SDL_KEYDOWN:
			onKeyDown(event);
			break;
		case SDL_KEYUP:
			onKeyUp(event);
			break;
		case SDL_MOUSEMOTION:
			onMouseMotion(event);
			break;
		case SDL_MOUSEBUTTONDOWN:
			onMouseButtonChange(event, true);
			break;
		case SDL_MOUSEBUTTONUP:
			onMouseButtonChange(event, false);
			break;
		case SDL_JOYAXISMOTION:
			onAxisMotion(event);
			break;
		case SDL_JOYBUTTONDOWN:
			break;
		case SDL_CONTROLLERDEVICEADDED:
			onControllerAdded(event);
			break;
		case SDL_CONTROLLERDEVICEREMOVED:
			onControllerRemoved(event);
			break;
		default:
			break;
		}
	}

	// keyboard
	inline bool keyDownEvent() {
		return isKeyDownEvent_;
	}

	inline bool keyUpEvent() {
		return isKeyUpEvent_;
	}

	inline bool isKeyDown(SDL_Scancode key) {
		return keyDownEvent() && kbState_[key] == 1;
	}

	inline bool isKeyDown(SDL_Keycode key) {
		return isKeyDown(SDL_GetScancodeFromKey(key));
	}

	inline bool isKeyUp(SDL_Scancode key) {
		return keyUpEvent() && kbState_[key] == 0;
	}

	inline bool isKeyUp(SDL_Keycode key) {
		return isKeyUp(SDL_GetScancodeFromKey(key));
	}

	// mouse
	inline bool mouseMotionEvent() {
		return isMouseMotionEvent_;
	}

	inline bool mouseButtonEvent() {
		return isMouseButtonEvent_;
	}

	inline const pair<Sint32, Sint32>& getMousePos() {
		return mousePos_;
	}

	inline int getMouseButtonState(MOUSEBUTTON b) {
		return mbState_[b];
	}

private:
	InputHandler() {
		kbState_ = SDL_GetKeyboardState(0);
		clearState();
		actualControllers_ = 0;
		maxConnectedControllers_ = 0;
	}

	inline void onKeyDown(const SDL_Event&) {
		isKeyDownEvent_ = true;
	}

	inline void onKeyUp(const SDL_Event&) {
		isKeyUpEvent_ = true;
	}

	inline void onMouseMotion(const SDL_Event &event) {
		isMouseMotionEvent_ = true;
		mousePos_.first = event.motion.x;
		mousePos_.second = event.motion.y;
	}

	inline void onAxisMotion(const SDL_Event& event) {
		isAxisMotionEvent_ = true;
		int controllerID = event.jaxis.which;

		Uint8 i = 0;
		bool bindFound = false;
		int axis;

		// Encontramos el eje que se ha movido
		while (!bindFound && i < SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_MAX) {
			SDL_GameControllerButtonBind b = SDL_GameControllerGetBindForAxis(controllers_[controllerID], (SDL_GameControllerAxis)i);
			if (b.value.axis == event.jaxis.axis) {
				axis = i;
				bindFound = true;
			}
			++i;
		}

		float value;
		// Si es joystick
		if (axis < 4) {
			if (event.jaxis.value > joystickDeadzone || event.jaxis.value < -joystickDeadzone)
				value = event.jaxis.value * joystickNormalize;
			else
				value = 0;

			switch (axis) {
			case 0:
				leftJoysticks_[controllerID]->setX(value);
				break;
			case 1:
				leftJoysticks_[controllerID]->setY(value);
				break;
			case 2:
				rightJoysticks_[controllerID]->setX(value);
				break;
			case 3:
				rightJoysticks_[controllerID]->setY(value);
				break;
			}
		}
		
		else {
			if (event.jaxis.value > triggerDeadzone)
				value = abs(event.jaxis.value);
			else
				value = 0;
			switch (axis) {
			case 4:
				leftTriggers_[controllerID] = value;
				break;
			case 5:
				rightTriggers_[controllerID] = value;
				break;
			}
		}
	}

	inline void onMouseButtonChange(const SDL_Event &event, bool isDown) {
		isMouseButtonEvent_ = true;
		switch (event.button.button) {
		case SDL_BUTTON_LEFT:
			mbState_[LEFT] = isDown;
			break;
		case SDL_BUTTON_MIDDLE:
			mbState_[MIDDLE] = isDown;
			break;
		case SDL_BUTTON_RIGHT:
			mbState_[RIGHT] = isDown;
			break;
		default:
			break;
		}
	}

	inline void onControllerAdded(const SDL_Event& event) {
		if (actualControllers_ < 4) {
			int id = controllers_.size(); // id fisica
			int gId; // id del juego
			initController(event.cdevice.which);
			if (disconectedControllers_.empty()) {
				gId = id;
				maxConnectedControllers_++;
			}
			else {
				gId = disconectedControllers_.front();
				disconectedControllers_.pop();
			}
			actualControllers_++;
			sysToGameId.emplace(id, gId);
			gameToSysId[gId] = id;
		}
	}

	inline void onControllerRemoved(const SDL_Event& event) {
		actualControllers_--;
		auto it = sysToGameId.find(event.cdevice.which);
		if (it != sysToGameId.end()) {
			disconectedControllers_.push((*it).second);
			sysToGameId.erase(it);
		}
	}

	inline void initController(int id) {
		SDL_GameController* c = SDL_GameControllerOpen(id);
		if (c) {
			cout << SDL_GameControllerName(c) << endl;

			controllers_.push_back(c);
			leftJoysticks_.push_back(new Vector2D(0, 0));
			rightJoysticks_.push_back(new Vector2D(0, 0));
			leftTriggers_.push_back(0.0f);
			rightTriggers_.push_back(0.0f);
			
			vector<int> aux;
			for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; ++i)
				aux.push_back(0);

			buttonStates_.push_back(aux);
		}
		SDL_JoystickEventState(SDL_ENABLE);
	}


	// Teclado
	bool isKeyUpEvent_;
	bool isKeyDownEvent_;
	bool isMouseMotionEvent_;
	bool isMouseButtonEvent_;
	pair<Sint32, Sint32> mousePos_;
	array<bool, 3> mbState_;
	const Uint8 *kbState_;

	// Mando
	bool isButtonDownEvent_;
	bool isButtonUpEvent_;
	bool isAxisMotionEvent_;
	vector<vector<int>> buttonStates_;
	array<int, 4> gameToSysId{ -1, -1, -1, -1 };
	map<int, int> sysToGameId;

	int actualControllers_; // Numero de mandos conectados en el momento
	int maxConnectedControllers_; // Numero de mandos que se han conectado en total

	
	vector<SDL_GameController*> controllers_;
	queue<int> disconectedControllers_;
	vector<Vector2D*> leftJoysticks_;
	vector<Vector2D*> rightJoysticks_;
	vector<float> leftTriggers_;
	vector<float> rightTriggers_;



	const double joystickNormalize = 1.0 / 32768.0;
	const int joystickDeadzone = 3276;
	const int triggerDeadzone = 3276;
};

// This macro defines a compact way for using the singleton InputHandler, instead of
// writing InputHandler::instance()->method() we write ih().method()
//
inline InputHandler& ih() {
	return *InputHandler::instance();
}
