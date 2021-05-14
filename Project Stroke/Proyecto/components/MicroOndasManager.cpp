﻿#include "MicroOndasManager.h"
#include "Stroke.h"
#include "iddleEnemy.h"
#include "controlHandler.h"
#include "Stun.h"
#include "AnimHamsterStateMachine.h"

MicroOndasManager::MicroOndasManager(int hamN, Texture* tx, Texture* tx2) :
	tr_(nullptr),
	hamsNum_(hamN), rightAttribs_(nullptr), leftAttribs_(nullptr),
	timer_(0), timeToEnd_(30000), lastTime_(sdlutils().currRealTime()),
	phaseComplete_(false), hamsterDead_(false), tx_(tx), txBat_(tx2),
	auxX(0), auxY(0), hits_(1), damageInPercent_(0.25f), gamestate(nullptr)
{
}

void MicroOndasManager::init() {
	tx_->setBlendMode(SDL_BLENDMODE_BLEND);
	tx_->setAlpha(0.0f);

	txBat_->setBlendMode(SDL_BLENDMODE_BLEND);
	txBat_->setAlpha(0.0f);

	blackRect.x = 0;
	blackRect.y = 0;
	blackRect.w = sdlutils().width();
	blackRect.h = sdlutils().height();

	bateriaRect.x = 0;
	bateriaRect.y = 0;
	bateriaRect.w = sdlutils().width();
	bateriaRect.h = sdlutils().height();


	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

		
	gamestate = entity_->getMngr()->getHandler<StateMachine>()->getComponent<GameStates>();
	assert(gamestate != nullptr);


	thisEnttityAttribs_ = entity_->getComponent<EntityAttribs>();
	assert(thisEnttityAttribs_ != nullptr);

	hamsters_ = entity_->getMngr()->getPlayers();


	right_ = entity_->getMngr()->addEntity();		//Referencia a los cables derechos
	rightTr_ = right_->addComponent<Transform>(
		tr_->getPos() + Vector2D(250,0), Vector2D(), 256.0f, 256.0f, 0.0f, 0.8f, 0.8f);
	rightTr_->getFlip() = true;

	right_->setGroup<Enemy>(true);
	
	right_->addComponent<EnemyStateMachine>();
	rightAttribs_ = right_->addComponent<EntityAttribs>(100 + (hamsNum_ * 50), 0.0, "soldier1", Vector2D(4.5, 2), 0, 0, 20, true, false);
	
	right_->addComponent<EnemyAttack>();
	right_->addComponent<MovementSimple>();
	right_->addComponent<EnemyBehaviour>(new IddleEnemy());


	right_->addComponent<Image>(&sdlutils().images().at("cables"));

	entity_->getMngr()->getEnemies().push_back(right_);


	left_ = entity_->getMngr()->addEntity();		//Referencia al cable iz
	leftTr_ = left_->addComponent<Transform>(
		tr_->getPos() + Vector2D(-250, 0), Vector2D(), 256.0f, 256.0f, 0.0f, 0.8f, 0.8f);
	leftTr_->getFlip() = true;
	left_->setGroup<Enemy>(true);
	

	left_->addComponent<EnemyStateMachine>();
	leftAttribs_ = left_->addComponent<EntityAttribs>(100 + (hamsNum_ * 50), 0.0, "soldier1", Vector2D(4.5, 2), 0, 0, 20, true, false);
	
	left_->addComponent<EnemyAttack>();
	left_->addComponent<MovementSimple>();
	left_->addComponent<EnemyBehaviour>(new IddleEnemy());


	left_->addComponent<Image>(&sdlutils().images().at("cables"));


	entity_->getMngr()->getEnemies().push_back(left_);

	//bateria principal

	bateria_ = entity_->getMngr()->addEntity();		//Referencia al cable iz
	bateriaTr_ = bateria_->addComponent<Transform>(
		tr_->getPos() + Vector2D(0, -250), Vector2D(), 256.0f, 256.0f, 0.0f, 0.8f, 0.8f);
	bateriaTr_->getFlip() = true;
	bateria_->setGroup<Enemy>(true);
	

	bateria_->addComponent<EnemyStateMachine>();
	bateriaAttribs_ = bateria_->addComponent<EntityAttribs>(100 + (hamsNum_ * 50), 0.0, "soldier1", Vector2D(4.5, 2), 0, 0, 20, true, true);
	
	bateria_->addComponent<EnemyAttack>();
	bateria_->addComponent<MovementSimple>();
	bateria_->addComponent<EnemyBehaviour>(new IddleEnemy());



	bateria_->addComponent<Image>(&sdlutils().images().at("bateria"))->setActive(false);


	entity_->getMngr()->getEnemies().push_back(bateria_);

	//añadir la interafz de la vida
	

	entity_->addComponent<UI>("canelon", 4);

	handTurn_ = sdlutils().rand().nextInt(0, 2) == 0;
}



void MicroOndasManager::update() {

	int vida = 0;
	
	//como los enemigos se elimnan al final de todo esto me hace el apaño

	if (right_ != nullptr && !right_->isActive())
		right_ = nullptr;
	else if (right_ != nullptr) {
		vida += rightAttribs_->getLife();
	}

	if (left_ != nullptr && !left_->isActive())
		left_ = nullptr;
	else if (left_ != nullptr) {
		vida += leftAttribs_->getLife();
	}



	if (bateria_ != nullptr && !bateria_->isActive())
		bateria_ = nullptr;
	else if (bateria_ != nullptr) {
		vida += bateriaAttribs_->getLife();
	}

	thisEnttityAttribs_->setLife(vida);

	//cuando los dos cables han petado
	if (bateria_ != nullptr && right_ == nullptr && left_ == nullptr && bateriaAttribs_->checkInvulnerability()) {
		bateriaAttribs_->setInvincibility(false);
		bateria_->getComponent<Image>()->setActive(true);
		//hacer la animacion en al que cae la bateria
	}

	


	if (bateria_ == nullptr && right_ == nullptr && left_ == nullptr)
		phaseComplete_ = true;

	//Contrareloj del nivel microondas 
	//cuando llegue a 0 mataria a todos los jugadores
	//dependiendo del tiempo que le quede se aplicaro un difunicado a la pantalla de color rojo/naranja

	//la suma del tiempo
	if (!phaseComplete_) {

		//si el estado del jeugo no esta en pausa
		//TODO 
		//seria esta parte la unica que no se actualiza el resto daria igual, el last time si que es necesario 
		//que se actualice para que al volver al estado funcione de forma correcta
		if (gamestate->getState() == GameStates::RUNNING)
		timer_ += sdlutils().currRealTime() - lastTime_;

		lastTime_ = sdlutils().currRealTime();


		if (!hamsterDead_) {

			if (timer_ >= timeToEnd_) {
				//se acaba los hamster mueren
				auto ents = entity_->getMngr()->getPlayers();
				for (Entity* e : ents) {
					e->getComponent<EntityAttribs>()->setLife(0);
					e->getComponent<EntityAttribs>()->die();
				}
				hamsterDead_= true;
			}
			auto ents = entity_->getMngr()->getPlayers();
			for (Entity* e : ents) {
				e->getComponent<EntityAttribs>()->setLife(e->getComponent<EntityAttribs>()->getMaxLife()  - e->getComponent<EntityAttribs>()->getMaxLife() * timer_ / timeToEnd_);
				//e->getComponent<EntityAttribs>()->die();
				//cada cuarto de tiempo le hace daño
				if ((timer_ / timeToEnd_) >= ((float)hits_ * damageInPercent_)) {
					//como le doy una tollina a un bicho?
					e->getComponent<EntityAttribs>()->recieveDmg(0);
					//sonido de la ostia

					entity_->getMngr()->getHandler<SoundManager>()->getComponent<SoundManager>()->play("lighthit");

					auto& hamStateM = e->getComponent<HamsterStateMachine>()->getState();

					if (hamStateM != HamStates::DEAD && hamStateM != HamStates::INFARCTED) {
						//Si tiene stun, se aplica
						Stun* stun = e->getComponent<Stun>();
						if (stun != nullptr && stun->isActive()) {

							//Si no estaba aturdido ya
							if (hamStateM != HamStates::STUNNED) {
								//Aturdimos al hamster
								hamStateM = HamStates::STUNNED;

								//Animaci�n de stun
								e->getComponent<AnimHamsterStateMachine>()->setAnimBool(HamStatesAnim::HITTED, true);

								//Desactivamos control de movimiento 
								ControlHandler* ctrl = e->getComponent<ControlHandler>();
								if (ctrl != nullptr)
									ctrl->setActive(false);

								//Desactivamos componentes de ataque
								StrongAttack* strAtt = e->getComponent<StrongAttack>();
								if (strAtt != nullptr)
									strAtt->setActive(false);

								LightAttack* lghtAtt = e->getComponent<LightAttack>();
								if (lghtAtt != nullptr)
									lghtAtt->setActive(false);

							}
							//Reiniciamos tiempo de stun
							stun->restartStunTime();
						}
					}
				}
			}
			if ((timer_ / timeToEnd_) >= ((float)hits_ * damageInPercent_))
				hits_++;
			tx_->setAlpha(10.0f + (205.0f * timer_/ timeToEnd_));
		}
	}
	else
		tx_->setAlpha(0.0f);

}

void MicroOndasManager::render() {
	//cargar las dos texturas que quiero
	tx_->render(blackRect);

	//para el renderizado del efecto de la bateria
	SDL_Rect cam = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam();
	if (bateria_ != nullptr && bateria_->isActive()) {
		auxX = bateriaTr_->getPos().getX() + (bateriaTr_->getW() / 2);
		auxY = bateriaTr_->getPos().getY() + (bateriaTr_->getH() / 2);
		txBat_->setAlpha(255.0f - 255.0f * bateriaAttribs_->getLife() / bateriaAttribs_->getMaxLife());
	}
	else
		txBat_->setAlpha(255.0f);

	bateriaRect.x = auxX - cam.x - (cam.w / 2) ;
	bateriaRect.y = auxY - cam.y - (cam.h / 2);

	txBat_->render(bateriaRect);
}