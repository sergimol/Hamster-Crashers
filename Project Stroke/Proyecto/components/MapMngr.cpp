#include "MapMngr.h"
#include "../sdlutils/SDLUtils.h"

#include "../components/Transform.h"
#include "../components/HamsterStateMachine.h"
#include "../components/Image.h"
#include "../components/Movement.h"
#include "../components/LightAttack.h"
#include "../components/StrongAttack.h"
#include "../components/Stroke.h"
#include "../components/UI.h"
#include "../components/Animator.h"
#include "../components/Roll.h"
#include "../components/Poison.h"
#include "../components/Pray.h"
#include "../components/Combos.h"
#include "../components/Turret.h"
#include "../components/MovementSimple.h"
#include "../components/EnemyAttack.h"
#include "../components/EnemyStateMachine.h"
#include "../components/MapMngr.h"
#include "../components/ControlHandler.h"
#include "../components/Item.h"
#include "../components/GetItem.h"
#include "../components/EnemyStun.h"
#include "../components/Stun.h"
#include "../components/Gravity.h"
#include "../components/Knockback.h"
#include "../components/HeartUI.h"
#include "../components/PossesionGame.h"
#include "../components/GhostCtrl.h"
#include "../components/ContactDamage.h"
#include "../components/HeightObject.h"
#include "../components//AnimHamsterStateMachine.h"
#include "../components/Swallow.h"
#include "../ecs/Camera.h"
#include "../components/EnemyBehaviour.h"
#include "../components/IddleEnemy.h"
#include "../components/FollowPlayer.h"
#include "../components/AmbushPlayer.h"
#include "../components/FleeFromPlayer.h"
#include "../components/FirstBossBehaviour.h"
#include "../components/FirstBossAttack.h"
#include "../components/EnemyStrongAttack.h"
#include "../components/StrongFollowPlayer.h"
#include "../components/BackGround.h"
#include "../components/FairStrokeStrategy.h"
#include "../components/RandomStrokeStrategy.h"
#include "../components/Parallax.h"
#include "../components/CollisionDetec.h"
#include "../components/Shadow.h"
#include "../components/EnemyMother.h"
#include "../components/TriggerScene.h"





MapMngr::~MapMngr() {
	for (int i = 0; i < mapDimensions_.x; i++)
	{
		delete[] collider[i];
	}
	delete[] collider;
}

void MapMngr::update() {
	auto* camera = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>();
	//	Comprobamos la colision con los triggers salas
	auto& players = entity_->getMngr()->getPlayers();
	for (tmx::Object trigger : TriggerftCamera) {//Recorrer triggers
		auto& getProp = trigger.getProperties();
		for (Entity* player : players) {
			auto* pTr = player->getComponent<Transform>();
			if (player->getComponent<HamsterStateMachine>()->getState() != HamStates::INFARCTED && Collisions::collides(pTr->getPos(), pTr->getW(), pTr->getH(), Vector2D(trigger.getPosition().x, trigger.getPosition().y) * scale, trigger.getAABB().width * scale, trigger.getAABB().height * scale)) {
				LoadEnemyRoom();
				if (getProp[0].getIntValue() != -1 || getProp[1].getIntValue() != -1) {
					camera->setGoToTracker(true);
					camera->changeCamFollowPos(Vector2D(getProp[0].getIntValue(), getProp[1].getIntValue()) * scale);
					camera->changeCamState(State::GoingTo);
				}
				//Borrar el punto de la camara del vector
				TriggerftCamera.pop_back();
			}
		}
	}
	//Si el estado de la camara es "Static" aka luchando con enemigos, y la cantidad de enemigos en la habitación es 0, volvemos a "Player1s"
	if (camera->getCamState() == State::Static && numberEnemyRoom == 0) {
		camera->changeCamFollowPos(Vector2D(-1, -1));	//Se pasa el punto medio de los jugadores
		camera->setGoToTracker(false);					//Se fija la transicion al punto medio de los jugadores al terminar GoTo
		camera->changeCamState(State::GoingTo);			//Se cambia el estado de la camara a GoTo
	}
}

void MapMngr::loadNewMap(string map) {
	cam = entity_->getMngr()->getHandler<Camera__>()->getComponent<Camera>()->getCam();

	if (map_.load(map)) {

		mapDimensions_ = map_.getTileCount();
		const auto& layers = map_.getLayers();

		//Establecemos el tamaño de la matriz
		collider = new bool* [mapDimensions_.x];
		for (int i = 0; i < mapDimensions_.x; i++)
		{
			collider[i] = new bool[mapDimensions_.y]{ false };
		}

		//Dimensiones de los tiles
		tilesDimensions_ = map_.getTileSize();

		int i = 0;
		//Cargamos los tilesets y guardamos las texturas
		const auto& tilesets = map_.getTilesets();

		//Estblecemos el tamaño en funcion de los tilesets que tenga
		tilesetsArr[tilesets.size()];

		for (const auto& tileset : tilesets)
		{
			//Guardamos las texturas de los tilesets
			tilesetsArr[i] = &sdlutils().images().at(tileset.getName());	//El nombre del tileset en Tiled y la textura png DEBEN llamarse igual
			i++;
		}

		//Fondos
		auto* o = entity_->getMngr()->addBackGround();
		o->addComponent<Transform>(Vector2D(0, 0), Vector2D(0, 0), 1920, 1459, 0.0, 1, 1);
		//Para meter un fondo meter esto									velocidad		tamaño       posicion
		o->addComponent<Parallax>(&sdlutils().images().at("level1background1"), 30, Vector2D(1920, 1459), Vector2D(0, -205));

		auto* p = entity_->getMngr()->addBackGround();
		p->addComponent<Transform>(Vector2D(0, 0), Vector2D(0, 0), 1920, 1459, 0.0, 1, 1);
		//Para meter un fondo meter esto                              velocidad  tamaño            posicion
		p->addComponent<Parallax>(&sdlutils().images().at("level1background2"), 20, Vector2D(1920, 1459), Vector2D(0, -205));

		auto* q = entity_->getMngr()->addBackGround();
		q->addComponent<Transform>(Vector2D(0, 0), Vector2D(0, 0), 1920, 1459, 0.0, 1, 1);
		//Para meter un fondo meter esto                              velocidad  tamaño            posicion
		q->addComponent<Parallax>(&sdlutils().images().at("level1background3"), 10, Vector2D(1920, 1459), Vector2D(0, -205));

		for (const auto& layer : layers)
		{
			if (layer->getType() == tmx::Layer::Type::Object)
			{
				const auto& objLayer = &layer->getLayerAs<tmx::ObjectGroup>();
				const auto& objects = objLayer->getObjects();
				if (layer->getName() == "Alturas") {
					for (const auto& object : objects)
					{
						auto* o = entity_->getMngr()->addMapHeight();
						o->addComponent<Transform>(Vector2D(object.getPosition().x * scale, object.getPosition().y * scale),
							Vector2D(), object.getAABB().width * scale, object.getAABB().height * scale, 0.0f, 1, 1);
						o->addComponent<HeightObject>()->setZ(stoi(object.getName()));
					}
				}
				else if (layer->getName() == "Salas") {
					//Guardamos todos los triggers de cambio de sala
					for (auto object : objects)
					{
						TriggerftCamera.push_back(object);
					}
				}
				//else if (layer->getName() == "PuntosCamara") {
				//	//Guardamos todos los triggers de cambio de sala
				//	for (tmx::Object object : objects)
				//	{
				//		/*auto* o = entity_->getMngr()->addEntity();
				//		o->addComponent<Transform>(Vector2D(object.getPosition().x * scale, object.getPosition().y * scale),
				//			Vector2D(), object.getAABB().width * scale, object.getAABB().height * scale, 0.0f);
				//		o->addComponent<HeightObject>();
				//		o->getComponent<HeightObject>()->setZ(stoi(object.getName()));*/
				//	}
				//}
				else if (layer->getName() == "entities") {
					//Guardamos la capa de objetos
					std::cout << layer->getName();

					objectLayer = &layer->getLayerAs<tmx::ObjectGroup>();

					for (const auto& object : objects) {
						if (object.getName() == "sardinilla" || object.getName() == "canelon" || object.getName() == "keta" || object.getName() == "monchi")
							addHamster(object);
						else if (object.getName() == "newScene") {

							newSceneTrigger(object.getProperties()[0].getStringValue(), object);
						}
					}
				}
			}

			//SI ES UNA CAPA DE TILES
			int index = 0;	//Recorrer� los tilesets para saber a cual corresponde cada tile
			if (layer->getType() == tmx::Layer::Type::Tile)
			{
				const auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();
				//read out tile layer properties etc...
				for (int j = 0; j < mapDimensions_.y; j++) {
					for (int i = 0; i < mapDimensions_.x; i++) {


						//Guardamos el indice global del tile (nos servir� para saber en qu� tileset se encuentra)
						auto tileList = tileLayer.getTiles();
						auto globalIndexTile = tileList[i + j * mapDimensions_.x].ID;	//mapDimensions_.y+columna*elementos_enuna_fila

					//Necesitamos saber a cual de los tilesets pertenece esa posicion
						while (globalIndexTile > tilesets[index].getLastGID()) {
							index++;	//Marca la posicion del tileset al que pertenece el tile
						}

						//Calculamos la posicion del tile en la pantalla -> DestRect
						auto x = i * tilesDimensions_.x;
						auto y = j * tilesDimensions_.y;

						//Calculamos la posici�n del tile en el tileset -> SrcRect
						int tilesetSize = tilesets[index].getColumnCount();
						//Calculamos las coordenadas locales del tile
						//Hay que restar el valor del primer tile del tileset a la posicion global
						auto localIndexTile = globalIndexTile - tilesets[index].getFirstGID();

						auto Srcx = (localIndexTile % tilesets[index].getColumnCount()) * tilesDimensions_.x;
						auto Srcy = (localIndexTile / tilesets[index].getColumnCount()) * tilesDimensions_.y;

						//Sacamos el SDL_SrcRect y SDL_DestRect con el que imprimimos los tiles
						SDL_Rect src;
						src.x = Srcx; src.y = Srcy;
						src.w = src.h = tilesDimensions_.x;	//Las tiles son cuadradas


						SDL_Rect dest;
						dest.x = x * scale; dest.y = y * scale;
						dest.w = dest.h = tilesDimensions_.x * scale;


						/*Vector2D renderPos = Vector2D(dest.x - cam.x, dest.y - cam.y);
						dest.x = renderPos.getX();
						dest.y = renderPos.getY();*/

						if (globalIndexTile != 0 && index < tilesets.size()) {
							//ESTO ES EL NOMBRE DE LA LAYER QUE SE CREE SOLO DE LAS COLISIONES
							if (tileLayer.getName() == "Collision") {
								//Si el leemos la capa de colisiones ponemos la matriz a true
								collider[i][j] = true;
								Tile(entity_->getMngr(), src, dest, tilesetsArr[index], true);
							}
							else {
								//Si no es una capa de colisiones se renderiza sin más
								Tile(entity_->getMngr(), src, dest, tilesetsArr[index], false);
							}
						}
					}
				}
			}
		}
		//ENEMIGO
		//Una vez terminamos de cargar todas las entidades y tiles de las CAPAS, cargamos los enemigos de la sala 0
		LoadEnemyRoom();
	}
}

//Devuelve true si se está chocando con alguna colision
bool MapMngr::intersectWall(SDL_Rect hamster) {

	//Cogemos arriba izquierda y abajo derecha
	Vector2D topLeftCoords = SDLPointToMapCoords(Vector2D((hamster.x) / scale, (hamster.y) / scale));
	Vector2D bottomRightCoords = SDLPointToMapCoords(Vector2D((hamster.x + hamster.w - 1) / scale, (hamster.y + hamster.h - 1) / scale));

	for (int x = topLeftCoords.getX(); x <= bottomRightCoords.getX(); x++) {
		for (int y = topLeftCoords.getY(); y <= bottomRightCoords.getY(); y++) {
			if (x < mapDimensions_.x && y < mapDimensions_.y && x >= 0 && y >= 0) {
				//Si hay una colision cercana...
				if (collider[x][y])
					//Se choca
					return true;
			}
		}
	}
	//Si no se choca con nada devuelve false
	return false;
}

//Devuelve la posicion en pantalla
Vector2D MapMngr::mapCoorsToSDLPoint(Vector2D coords) {
	return Vector2D(coords.getX() * TAM_CELDA, coords.getY() * TAM_CELDA);
}

//Devuelve la posicion del vector en coordenadas
Vector2D MapMngr::SDLPointToMapCoords(Vector2D p) {
	return Vector2D(p.getX() / TAM_CELDA, p.getY() / TAM_CELDA);
}


void MapMngr::LoadEnemyRoom() {

	auto& enemies = entity_->getMngr()->getEnemies();

	const auto& objects = objectLayer->getObjects();
	numberEnemyRoom = 0;	//Guarda el numero de enemigos por sala
	for (const auto& object : objects)
	{
		auto& name = object.getName();
		auto mngr_ = entity_->getMngr();
		auto& prop = object.getProperties();

		if (name == "enemigo" && prop[0].getIntValue() == Room) { //PROP[0] ES LA PROPIEDAD 0, EDITAR SI SE AÑADEN MAS
				
			for (int i = 0; i < 8; i++) {
				auto* enemy = mngr_->addEntity();
				enemy->addComponent<Transform>(
					Vector2D(object.getPosition().x * scale, object.getPosition().y * scale),
					Vector2D(), 240.0f, 370.0f, 0.0f, 1,1)->getFlip() = true;

				enemy->addComponent<EnemyStateMachine>();
				enemy->setGroup<Enemy>(true);

				enemy->addComponent<EntityAttribs>(200, 0.0, "enemy", Vector2D(4.5, 2), 0, 0, 5);

				enemy->addComponent<Image>(&sdlutils().images().at("canelon"));
				enemy->addComponent<UI>("canelon", 4);

				enemy->addComponent<EnemyAttack>();
				enemy->addComponent<Knockback>();
				enemy->addComponent<Gravity>();
				enemy->addComponent<CollisionDetec>();
				enemy->addComponent<MovementSimple>();

				enemy->addComponent<EnemyBehaviour>(new IddleEnemy());

				enemies.push_back(enemy);
				//anyadir a los cuidados de la madre
				mngr_->getHandler<Mother>()->getComponent<EnemyMother>()->addEnemy(enemy);
				//enemy->addComponent<EnemyStun>();
				numberEnemyRoom++;
			}
				
		}
		else if (name == "enemigoFuerte" && prop[0].getIntValue() == Room) { //PROP[0] ES LA PROPIEDAD 0, EDITAR SI SE AÑADEN MAS

			for (int i = 0; i < 8; i++) {
				auto* enemy = mngr_->addEntity();
				enemy->addComponent<Transform>(
					Vector2D(object.getPosition().x * scale, object.getPosition().y * scale),
					Vector2D(), 240.0f, 370.0f, 0.0f, 1, 1)->getFlip() = true;

				enemy->addComponent<EnemyStateMachine>();
				enemy->setGroup<Enemy>(true);

				enemy->addComponent<EntityAttribs>(200, 0.0, "enemy", Vector2D(4.5, 2), 0, 0, 5);

				enemy->addComponent<Image>(&sdlutils().images().at("enemigoFuerte"));
				enemy->addComponent<UI>("canelon", 4);

				//enemy->addComponent<EnemyStrongAttack>();
				enemy->addComponent<EnemyAttack>();
				enemy->addComponent<Knockback>();
				enemy->addComponent<MovementSimple>();

				enemy->addComponent<EnemyBehaviour>(new IddleEnemy());

				enemies.push_back(enemy);

				//anyadir a los cuidados de la madre
				mngr_->getHandler<Mother>()->getComponent<EnemyMother>()->addEnemy(enemy);
				
				enemy->addComponent<EnemyStun>();
				numberEnemyRoom++;
			}
		}
		else if (name == "firstBoss" && prop[0].getIntValue() == Room) { //PROP[0] ES LA PROPIEDAD 0, EDITAR SI SE AÑADEN MAS
			//auto* enemy = mngr_->addEntity();
			//enemy->addComponent<Transform>(
			//	Vector2D(object.getPosition().x * scale, object.getPosition().y * scale),
			//	Vector2D(), 240.0f, 370.0f, 0.0f, 1,1)->getFlip() = true;

			//enemy->addComponent<EnemyStateMachine>();
			//enemy->setGroup<Enemy>(true);

			//enemy->addComponent<EntityAttribs>(200, 0.0, "enemy", Vector2D(4.5, 2), 0, 0, 5);

			//enemy->addComponent<Image>(&sdlutils().images().at("enemigoFuerte"));
			//enemy->addComponent<UI>("canelon", 4);

			//enemy->addComponent<EnemyStrongAttack>();
			//enemy->addComponent<EnemyAttack>();
			//enemy->addComponent<Knockback>();
			//enemy->addComponent<CollisionDetec>();
			//enemy->addComponent<MovementSimple>();

			//enemy->addComponent<EnemyBehaviour>(new StrongFollowPlayer());

			//enemies.push_back(enemy);
			//enemy->addComponent<EnemyStun>();
			//numberEnemyRoom++;
		}
		else if (name == "firstBoss" && prop[0].getIntValue() == Room) { //PROP[0] ES LA PROPIEDAD 0, EDITAR SI SE AÑADEN MAS
			auto* enemy = mngr_->addEntity();
			enemy->addComponent<Transform>(
				Vector2D(object.getPosition().x * scale, object.getPosition().y * scale),
				Vector2D(),/* 5*23.27f*/256.0f, 5 * 256.0f, 0.0f, 0.8f, 0.8f)->getFlip() = true;

			enemy->addComponent<EnemyStateMachine>();
			enemy->setGroup<Enemy>(true);

			enemy->addComponent<EntityAttribs>(700, 0.0, "enemy", Vector2D(4.5, 2), 0, 0, 20, true, true);

			enemy->addComponent<Image>(&sdlutils().images().at("firstBoss"));
			enemy->addComponent<UI>("canelon", 4);

			enemy->addComponent<FirstBossAttack>();
			enemy->addComponent<MovementSimple>();

			enemy->addComponent<EnemyBehaviour>(new FirstBossBehaviour());

			enemies.push_back(enemy);

			numberEnemyRoom++;
		}
	}
	Room++;	//Una vez cargamos a los enemigos de la habitacion incrementamos el contador para poder cargar los enemigos de la siguiente
}

void MapMngr::addHamster(const tmx::Object& obj) {
	//do stuff with object properties
	auto& name = obj.getName();
	auto mngr_ = entity_->getMngr();
	auto& players = mngr_->getPlayers();

	auto* hamster1 = mngr_->addEntity();


	//Habilidad
	if (name == "sardinilla")
		hamster1->addComponent<Transform>(Vector2D(obj.getPosition().x * scale, obj.getPosition().y * scale), 
			Vector2D(), 86 * scale, 86 * scale, 0.0f,0.5,0.5);
	else if (name == "canelon")
		hamster1->addComponent<Transform>(Vector2D(obj.getPosition().x * scale, obj.getPosition().y * scale), 
			Vector2D(), 86 * scale, 86 * scale, 0.0f, 1, 1);
	else if (name == "keta")
		hamster1->addComponent<Transform>(Vector2D(obj.getPosition().x * scale, obj.getPosition().y * scale), 
			Vector2D(), 86 * scale, 86 * scale, 0.0f, 1, 1);
	else
		hamster1->addComponent<Transform>(Vector2D(obj.getPosition().x * scale, obj.getPosition().y * scale), 
			Vector2D(), 86 * scale, 86 * scale, 0.0f, 1, 1);

	Transform* tr = hamster1->getComponent<Transform>();
	hamster1->addComponent<HamsterStateMachine>();

	hamster1->addComponent<EntityAttribs>(100, 0.0, name, Vector2D(7, 4.5), 0, 15, 20);
	hamster1->addComponent<Animator>(
		&sdlutils().images().at(name + "Sheet"),
		86,
		86,
		3,
		3,
		220,
		Vector2D(0, 0),
		3
		);
	hamster1->addComponent<AnimHamsterStateMachine>();
	hamster1->addComponent<Gravity>();
	hamster1->addComponent<CollisionDetec>();
	hamster1->addComponent<Movement>();
	
	Gravity* g = hamster1->getComponent<Gravity>();
	tr->setGravity(g);

	//Ataques Basicos
	hamster1->addComponent<LightAttack>();
	hamster1->addComponent<StrongAttack>();
	hamster1->addComponent<Combos>();

	//Habilidad
	if (name == "sardinilla") hamster1->addComponent<Roll>();
	else if (name == "canelon") hamster1->addComponent<Pray>(100, 100);
	else if (name == "keta") hamster1->addComponent<Poison>(10000);
	else hamster1->addComponent<Turret>();


	//Interfaz
	hamster1->addComponent<UI>(name, 0);
	hamster1->addComponent<HeartUI>(name, 0);

	//Gestion de infartos
	hamster1->addComponent<PossesionGame>();
	hamster1->addComponent<GhostCtrl>();
	//ES NECESARIO PASAR LA ESTRATEGIA QUE DEBE USAR EL STROKE O SE VA A LA PUTA (RandomStrokeStrategy o FairStrokeStrategy)
	FairStrokeStrategy* rndStr = new FairStrokeStrategy();
	hamster1->addComponent<Stroke>(rndStr);

	hamster1->addComponent<Knockback>();
	hamster1->addComponent<GetItem>();

	//Handlr
	hamster1->addComponent<ControlHandler>(hamster1->getComponent<EntityAttribs>()->getNumber());
	hamster1->addComponent<Stun>();

	hamster1->setGroup<Ally>(true);

	//Lo a�adimos al vector de entidades
	players.push_back(hamster1);

	//añadirlo tmb a la lista de control de enemyMother
	mngr_->getHandler<Mother>()->getComponent<EnemyMother>()->addObjetive(hamster1);

	//Para acceder facilmente le metemos en Hamster1 de Handelers
	if (name == "sardinilla") mngr_->setHandler<Hamster1>(hamster1);
	else if (name == "canelon") mngr_->setHandler<Hamster2>(hamster1);
	else if (name == "keta") mngr_->setHandler<Hamster3>(hamster1);
	else mngr_->setHandler<Hamster4>(hamster1);

}

//void MapMngr::Refresh() {
//	roomTrigger.erase( //
//		std::remove_if( //
//			roomTrigger.begin(), //
//			roomTrigger.end(), //
//			[](const Entity* e) { //
//				return !e->isActive();
//			}), //
//		roomTrigger.end());
//}
void MapMngr::newSceneTrigger(string newScene, const tmx::Object& object) {

	//Creamos una entidad
	auto trigger = entity_->getMngr()->addEntity();
	trigger->addComponent<Transform>(Vector2D(object.getPosition().x * scale, object.getPosition().y * scale),
		Vector2D(), object.getAABB().width * scale, object.getAABB().height * scale, 0.0f, 1, 1);
	trigger->addComponent<TriggerScene>(newScene);
}