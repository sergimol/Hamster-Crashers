// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"

#include "HamsterStateMachine.h"
#include "Ability.h"
#include "StrokeStrategy.h"
//#include "Transform.h"

class Stroke: public Component {
public:
	Stroke(StrokeStrategy* ss) :
			hms_(nullptr), ab_(nullptr), ss_(ss), tr_(nullptr), state_(nullptr) {
	}
	virtual ~Stroke() {
		if (ss_ != nullptr) delete ss_; ss_ = nullptr;
	}
	void init() override;

	void update() override;

	void onEnable() override;

	void onResume() override;

	void increaseChance(int n, bool fromAbility);

	void decreaseChance();

	void infarctHamster();

	void setStrategy(StrokeStrategy* ss);

	//DEBUG ------ INFARTA AL HAMSTER
	void INFARCT() { chance_ = 1000; };

	void restartChance() { chance_ = 0; chanceFromAb_ = 0; };

private:
	void checkChance();

	bool allInfarted = false;
	int infartTime;
	int waitAfterInfart = 5000;

	StrokeStrategy* ss_;
	HamsterStateMachine* hms_;
	Ability* ab_;
	Transform* tr_;
	GameStates* state_;

	const int UPDATETIME = 3000, // Tiempo entre comprobaciones de infarto
		TIMETODECREASE = 3500, // Tiempo que debe pasar para empezar a reducir el infarto
		TIMEBETWEENDECREASES = 250, // Tiempo entre reducciones de la probabilidad
		NORMALDECREASE = 75, //Decremento de forma natural
		MINVALUE = 5, //Mínimo porcentaje de infarto
		DECREASEPERCENTAGE = 35, // Porcentaje que se reduce por acierto en el minijuego
		CHANGECOLORVALUE = 800; //Porcentaje para cambiar el color del hamster a aviso
	// Probabilidad de que haya un infarto
	int chance_ = 1,
		chanceFromAb_ = 0,
		// Tiempo de la última comprobación
		timeLastUpdate_ = 0,
		// Tiempo del último aumento
		timeLastIncrease_ = 0,
		// Tiempo de la última reducción
		timeLastDecrease_ = 0;

};

