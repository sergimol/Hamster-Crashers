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

const int MAXPLAYERS = 4,
		  JOYSTICKDEADZONE = 10000,
		  TRIGGERDEADZONE = 10000;

class InputHandler: public Singleton<InputHandler> {

	friend Singleton<InputHandler> ;

public:
	enum MOUSEBUTTON : uint8_t {
		LEFT = 0, MIDDLE = 1, RIGHT = 2
	};

	virtual ~InputHandler() {
		/*for (int i = 0; i < MAXPLAYERS; ++i) {
			if (controllers_[i] != nullptr) {
				SDL_GameControllerClose((SDL_GameController*)i);
				controllers_[i] = nullptr;

				delete leftJoysticks_[i];
				leftJoysticks_[i] = nullptr;

				delete rightJoysticks_[i];
				rightJoysticks_[i] = nullptr;				
			}
		}*/
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
			//cout << "motion" << endl;
			break;
		case SDL_JOYBUTTONDOWN:
			onButtonDown(event);
			//cout << "down" << endl;
			break;
		case SDL_JOYBUTTONUP:
			onButtonUp(event);
			//cout << "up" << endl;
			break;
		case SDL_CONTROLLERDEVICEADDED:
			onControllerAdded(event);
			break;
		case SDL_CONTROLLERDEVICEREMOVED:
			onControllerRemoved(event);
			break;
		case SDL_QUIT:
			isQuitEvent_ = true;
		default:
			break;
		}
	}

	inline bool onQuit() {
		return isQuitEvent_;
	}

	inline void startQuitEvent() {
		isQuitEvent_ = true;
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

	// mando
	inline bool isButtonDown(int controller, SDL_GameControllerButton button) {
		if (controllers_[controller] == nullptr)
			return false;
		return (isButtonDownEvent_ && buttonStates_[controller][button]);
	}

	inline bool isAnyBButtonDown() {
		for (int i = 0; i < MAXPLAYERS; ++i) {
			if (controllers_[i] != nullptr) {
				if (buttonStates_[i][SDL_CONTROLLER_BUTTON_B])
					return true;
			}
			else
				break;
		}

		return false;
	}

	inline bool isButtonUp(int controller, SDL_GameControllerButton button) {
		if (controllers_[controller] == nullptr)
			return false;
		return (isButtonUpEvent_ && !buttonStates_[controller][button]);
	}

	inline bool isButtonDownEvent() {
		return isButtonDownEvent_;
	}

	inline bool isButtonUpEvent() {
		return isButtonUpEvent_;
	}

	inline bool isAxisMotionEvent() {
		return isAxisMotionEvent_;
	}

	inline float getAxisValue(int controller, SDL_GameControllerAxis axis) {
		if (controllers_[controller] == nullptr)
			return 0.0f;
		switch (axis)
		{
		case SDL_CONTROLLER_AXIS_LEFTX:
			return leftJoysticks_[controller].getX();
			break;
		case SDL_CONTROLLER_AXIS_LEFTY:
			return leftJoysticks_[controller].getY();
			break;
		case SDL_CONTROLLER_AXIS_RIGHTX:
			return rightJoysticks_[controller].getX();
			break;
		case SDL_CONTROLLER_AXIS_RIGHTY:
			return rightJoysticks_[controller].getY();
			break;
		case SDL_CONTROLLER_AXIS_TRIGGERLEFT:
			return leftTriggers_[controller];
			break;
		case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
			return rightTriggers_[controller];
			break;
		default:
			break;
		}
	}

	inline bool playerHasController(int player) {
		return controllers_[player] != nullptr;
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

	inline void rumbleEvent(int id) {
		if(haptics_[id] != NULL)
			SDL_HapticRunEffect(haptics_[id], 0, 1);
	}

private:
	InputHandler() {
		kbState_ = SDL_GetKeyboardState(0);
		clearState();
		actualControllers_ = 0;
		totalControllers_ = 0;
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
		auto it = sysToGameId.find(event.jaxis.which);
		int controllerID = (*it).second;

		Uint8 i = 0;
		bool found = false;
		int axis;

		// Encontramos el eje que se ha movido
		while (!found && i < SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_MAX) {
			SDL_GameControllerButtonBind b = SDL_GameControllerGetBindForAxis(controllers_[controllerID], (SDL_GameControllerAxis)i);
			if (b.value.axis == event.jaxis.axis) {
				axis = i;
				found = true;
			}
			++i;
		}

		float value;
		// Si es joystick
		if (axis < 4) {
			if (event.jaxis.value > JOYSTICKDEADZONE || event.jaxis.value < -JOYSTICKDEADZONE)
				value = event.jaxis.value / 32768.0;
			else
				value = 0;

			switch (axis) {
			case 0:
				leftJoysticks_[controllerID].setX(value);
				break;
			case 1:
				leftJoysticks_[controllerID].setY(value);
				break;
			case 2:
				rightJoysticks_[controllerID].setX(value);
				break;
			case 3:
				rightJoysticks_[controllerID].setY(value);
				break;
			}
		}
		// Si es gatillo
		else {
			if (event.jaxis.value > TRIGGERDEADZONE)
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

	inline void onButtonDown(const SDL_Event& event) {
		isButtonDownEvent_ = true;

		Uint8 i = 0;
		bool found = false;
		int id = sysToGameId.find(event.cdevice.which)->second;

		// Encontramos el bot�n
		while (!found && i < SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_MAX) {
			SDL_GameControllerButtonBind b = SDL_GameControllerGetBindForButton(controllers_[id], (SDL_GameControllerButton)i);
			if (b.value.button == event.cbutton.button)
				found = true;
			else
				i++;
		}

		if(found)
			buttonStates_[id][i] = true;
	}

	inline void onButtonUp(const SDL_Event& event) {
		isButtonUpEvent_ = true;

		Uint8 i = 0;
		bool found = false;
		int id = sysToGameId.find(event.jaxis.which)->second;

		// Encontramos el bot�n
		while (!found && i < SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_MAX) {
			SDL_GameControllerButtonBind b = SDL_GameControllerGetBindForButton(controllers_[id], (SDL_GameControllerButton)i);
			if (b.value.button == event.cbutton.button)
				found = true;
			else
				i++;
		}

		if (found)
			buttonStates_[id][i] = false;
	}

	// Añade un mando al juego
	inline void onControllerAdded(const SDL_Event& event) {
		if (actualControllers_ < MAXPLAYERS) {
			int id = totalControllers_; // id fisica que recibe SDL
			int gId; // id dentro del juego
			// Comprueba si el mando que se acaba de conectar es nuevo o reconectado
			if (disconectedControllers_.empty()) 
				gId = actualControllers_;
			else {
				gId = disconectedControllers_.front();
				disconectedControllers_.pop();
			}
			initController(event.cdevice.which, gId);
			actualControllers_++;
			totalControllers_++;
			sysToGameId.emplace(id, gId);
			gameToSysId[gId] = id;
		}
	}

	// Elimina un mando del juego
	inline void onControllerRemoved(const SDL_Event& event) {
		actualControllers_--;
		auto it = sysToGameId.find(event.cdevice.which);
		if (it != sysToGameId.end()) {
			int id = (*it).second;
			disconectedControllers_.push(id);
			sysToGameId.erase(it);

			if (haptics_[id] != NULL)
				SDL_HapticClose(haptics_[id]);

			SDL_GameControllerClose(controllers_[id]);
			controllers_[id] = nullptr;

			leftJoysticks_[id] = Vector2D(0, 0);
			rightJoysticks_[id] = Vector2D(0, 0);

			leftTriggers_[id] = 0.0f;
			rightTriggers_[id] = 0.0f;
		}
	}

	inline void initController(int id, int gId) {
		SDL_GameController* c = SDL_GameControllerOpen(id);
		if (c) {
			cout << SDL_GameControllerName(c) << endl;

			controllers_[gId] = c;
			leftJoysticks_[gId] = Vector2D(0, 0);
			rightJoysticks_[gId] = Vector2D(0, 0);
			leftTriggers_[gId] = 0.0f;
			rightTriggers_[gId] = 0.0f;
			
			// para la vibracion
			SDL_Joystick* j = SDL_GameControllerGetJoystick(c);
			haptics_[gId] = SDL_HapticOpenFromJoystick(j);

			if (haptics_[gId] != NULL) {
				// Creacion del efecto
				SDL_HapticEffect e;
				SDL_memset(&e, 0, sizeof(SDL_HapticEffect));
				e.type = SDL_HAPTIC_LEFTRIGHT;
				e.leftright.large_magnitude = 2000;
				e.leftright.small_magnitude = 2000;
				e.leftright.length = 100;
				SDL_HapticNewEffect(haptics_[gId], &e);
			}

			vector<int> aux;
			for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; ++i)
				aux.push_back(0);

			buttonStates_[gId] = aux;
		}
		SDL_JoystickEventState(SDL_ENABLE);
	}

	// Teclado
	bool isKeyUpEvent_;
	bool isKeyDownEvent_;
	bool isMouseMotionEvent_;
	bool isMouseButtonEvent_;
	bool isQuitEvent_ = false;
	pair<Sint32, Sint32> mousePos_;
	array<bool, 3> mbState_;
	const Uint8 *kbState_;

	// Mando
	bool isButtonDownEvent_;
	bool isButtonUpEvent_;
	bool isAxisMotionEvent_;
	array<vector<int>, MAXPLAYERS> buttonStates_;
	array<int, MAXPLAYERS> gameToSysId{ -1, -1, -1, -1 };
	map<int, int> sysToGameId;

	int actualControllers_; // Numero de mandos conectados en el momento
	int totalControllers_; // Numero de mandos conectados en total
	
	array<SDL_GameController*, MAXPLAYERS> controllers_;
	queue<int> disconectedControllers_;
	array<Vector2D, MAXPLAYERS> leftJoysticks_;
	array<Vector2D, MAXPLAYERS> rightJoysticks_;
	array<float, MAXPLAYERS> leftTriggers_;
	array<float, MAXPLAYERS> rightTriggers_;

	array<SDL_Haptic*, MAXPLAYERS> haptics_;
};

// This macro defines a compact way for using the singleton InputHandler, instead of
// writing InputHandler::instance()->method() we write ih().method()
//
inline InputHandler& ih() {
	return *InputHandler::instance();
}
