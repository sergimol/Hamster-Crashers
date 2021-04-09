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
#include "../components/FollowPlayer.h"
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
#include "../components/Possesion.h"
#include "../components/GhostCtrl.h"
#include "../components/ContactDamage.h"
#include "../components/HeightObject.h"
#include "../components//AnimHamsterStateMachine.h"
#include "../components/Swallow.h"


void MapMngr::init() {
	loadNewMap("resources/images/tiled/Mapa.tmx");
}

void MapMngr::loadNewMap(string map) {

	if (map_.load(map)) {

		mapDimensions_ = map_.getTileCount();
		const auto& layers = map_.getLayers();

		//Dimensiones de los tiles
		tilesDimensions_ = map_.getTileSize();

		int i = 0;
		//Cargamos los tilesets y guardamos las texturas
		const auto& tilesets = map_.getTilesets();
		for (const auto& tileset : tilesets)
		{
			//Guardamos las texturas de los tilesets
			tilesetsArr[i] = &sdlutils().images().at(tileset.getName());	//El nombre del tileset en Tiled y la textura png DEBEN llamarse igual
			i++;
		}

		for (const auto& layer : layers)
		{
			if (layer->getType() == tmx::Layer::Type::Object)
			{
				const auto& objectLayer = layer->getLayerAs<tmx::ObjectGroup>();
				const auto& objects = objectLayer.getObjects();
				if (layer->getName() == "Alturas") {
					for (const auto& object : objects)
					{
						auto* o = entity_->getMngr()->addMapHeight();
						o->addComponent<Transform>(Vector2D(object.getPosition().x * scale, object.getPosition().y * scale),
							Vector2D(), object.getAABB().width * scale, object.getAABB().height * scale, 0.0f);
						o->addComponent<HeightObject>();
						o->getComponent<HeightObject>()->setZ(stoi(object.getName()));
						/*entity_->getMngr()->getMapH().push_back(o);*/
					}
				}
				else {
					for (const auto& object : objects)
					{
						//do stuff with object properties
						auto& name = object.getName();
						auto mngr_ = entity_->getMngr();

						auto& players = mngr_->getPlayers();
						auto& enemies = mngr_->getEnemies();
						auto& obstacles = mngr_->getObstacles();

						//SARDINILLA
						if (name == "sardinilla") {
							auto* hamster1 = mngr_->addEntity();

							hamster1->addComponent<Transform>(
								Vector2D(object.getPosition().x * scale, object.getPosition().y * scale),
								Vector2D(), 256.0f, 256.0f, 0.0f);

							hamster1->addComponent<EntityAttribs>(100, 0.0, "sardinilla", Vector2D(7, 4.5), 0, 15);

							hamster1->addComponent<Animator>(
								&sdlutils().images().at("sardinillaSheet"),
								86,
								86,
								3,
								3,
								220,
								Vector2D(0, 0),
								3
								);

							hamster1->addComponent<AnimHamsterStateMachine>();
							hamster1->addComponent<HamsterStateMachine>();
							hamster1->addComponent<Movement>();
							hamster1->addComponent<Gravity>();

							//Ataques Basicos
							hamster1->addComponent<LightAttack>();
							hamster1->addComponent<StrongAttack>();
							hamster1->addComponent<Combos>();

							//Habilidad
							hamster1->addComponent<Roll>();

							//Handlr
							hamster1->addComponent<ControlHandler>(hamster1->getComponent<EntityAttribs>()->getNumber());

							//Interfaz
							hamster1->addComponent<UI>("sardinilla", 0);
							hamster1->addComponent<HeartUI>("sardinilla", 0);

							//Gestion de infartos
							hamster1->addComponent<Possesion>();
							hamster1->addComponent<GhostCtrl>();
							hamster1->addComponent<Stroke>();

							hamster1->addComponent<Stun>();
							hamster1->addComponent<Knockback>();
							hamster1->addComponent<GetItem>();

							hamster1->setGroup<Ally>(true);

							//Lo a�adimos al vector de entidades
							players.push_back(hamster1);

							//Para acceder facilmente le metemos en Hamster1 de Handelers
							mngr_->setHandler<Hamster1>(hamster1);

							auto* cosodecosas = mngr_->addEntity();
							cosodecosas->addComponent<Transform>(
								Vector2D(object.getPosition().x * scale + 300, object.getPosition().y * scale),
								Vector2D(), 256.0f, 256.0f, 0.0f);
							cosodecosas->addComponent<ContactDamage>(10);


						}
						//CANELON
						else if (name == "canelon") {
							//Sardinilla
							auto* hamster2 = mngr_->addEntity();

							hamster2->addComponent<Transform>(
								Vector2D(object.getPosition().x * scale, object.getPosition().y * scale),
								Vector2D(), 256.0f, 256.0f, 0.0f);

							hamster2->addComponent<EntityAttribs>(100, 0.0, "canelon", Vector2D(7, 4.5), 1, 0);

							hamster2->addComponent<Animator>(
								&sdlutils().images().at("canelonSheet"),
								64,
								64,
								3,
								3,
								220,
								Vector2D(0, 0),
								3
								);

							hamster2->addComponent<AnimHamsterStateMachine>();
							hamster2->addComponent<HamsterStateMachine>();
							hamster2->addComponent<Movement>();

							//Ataques basicos
							hamster2->addComponent<LightAttack>();
							hamster2->addComponent<StrongAttack>();
							hamster2->addComponent<Combos>();

							//Habilidad
							hamster2->addComponent<Pray>(30, 50);

							//Handlr
							hamster2->addComponent<ControlHandler>(hamster2->getComponent<EntityAttribs>()->getNumber());

							//Interfaz
							hamster2->addComponent<UI>("canelon", 0);
							hamster2->addComponent<HeartUI>("canelon", 0);

							//Gestion de infarto
							hamster2->addComponent<Stroke>();

							hamster2->addComponent<Stun>();
							hamster2->addComponent<Knockback>();
							hamster2->addComponent<GetItem>();

							hamster2->setGroup<Ally>(true);

							players.push_back(hamster2);

							//Para acceder facilmente le metemos en Hamster2 de Handelers
							mngr_->setHandler<Hamster2>(hamster2);
						}
						//KETA
						else if (name == "keta") {
							//Sardinilla
							auto* hamster3 = mngr_->addEntity();
							hamster3->addComponent<Transform>(
								Vector2D(object.getPosition().x * scale, object.getPosition().y * scale),
								Vector2D(), 256.0f, 256.0f, 0.0f);
							hamster3->addComponent<EntityAttribs>(100, 0.0, "keta", Vector2D(7, 4.5), 2, 10);
							//hamster1->addComponent<Image>(&sdlutils().images().at("sardinilla"));
							hamster3->addComponent<Animator>(
								&sdlutils().images().at("ketaSheet"),
								64,
								64,
								3,
								3,
								220,
								Vector2D(0, 0),
								3
								);

							hamster3->addComponent<HamsterStateMachine>();
							hamster3->addComponent<Movement>();
							hamster3->addComponent<Gravity>();

							//Ataques basicos
							hamster3->addComponent<LightAttack>();
							hamster3->addComponent<StrongAttack>();
							hamster3->addComponent<Combos>();

							//Habilidad
							hamster3->addComponent<Poison>(5);

							//Handler
							hamster3->addComponent<ControlHandler>(hamster3->getComponent<EntityAttribs>()->getNumber());

							//Interfaz
							hamster3->addComponent<UI>("keta", 0);
							hamster3->addComponent<HeartUI>("keta", 0);

							//Gestion de infarto
							hamster3->addComponent<Stroke>();

							hamster3->addComponent<Stun>();
							hamster3->addComponent<Knockback>();
							hamster3->addComponent<GetItem>();

							hamster3->setGroup<Ally>(true);

							players.push_back(hamster3);

							//Para acceder facilmente le metemos en Hamster3 de Handelers
							mngr_->setHandler<Hamster3>(hamster3);
						}
						//MONCHI
						else if (name == "monchi") {
							//Sardinilla
							auto* hamster4 = mngr_->addEntity();
							hamster4->addComponent<Transform>(
								Vector2D(object.getPosition().x * scale, object.getPosition().y * scale),
								Vector2D(), 256.0f, 256.0f, 0.0f);
							hamster4->addComponent<EntityAttribs>(100, 0.0, "monchi", Vector2D(7, 4.5), 3, 0);
							//hamster1->addComponent<Image>(&sdlutils().images().at("sardinilla"));
							hamster4->addComponent<Animator>(
								&sdlutils().images().at("monchiSheet"),
								64,
								64,
								3,
								3,
								220,
								Vector2D(0, 0),
								3
								);

							hamster4->addComponent<HamsterStateMachine>();
							hamster4->addComponent<Movement>();
							hamster4->addComponent<Gravity>();

							//Ataques basicos
							hamster4->addComponent<LightAttack>();
							hamster4->addComponent<StrongAttack>();
							hamster4->addComponent<Combos>();

							//Habilidad
							hamster4->addComponent<Turret>();
							//Pasiva
							hamster4->addComponent<Swallow>(40);

							//Handler
							hamster4->addComponent<ControlHandler>(hamster4->getComponent<EntityAttribs>()->getNumber());

							//Interfaz
							hamster4->addComponent<UI>("monchi", 0);
							hamster4->addComponent<HeartUI>("monchi", 0);

							//Gestion de infarto
							hamster4->addComponent<Stroke>();

							hamster4->addComponent<Stun>();
							hamster4->addComponent<Knockback>();
							hamster4->addComponent<GetItem>();

							hamster4->setGroup<Ally>(true);

							players.push_back(hamster4);

							//Para acceder facilmente le metemos en Hamster4 de Handelers
							mngr_->setHandler<Hamster4>(hamster4);
						}
						//ENEMIGO
						//Faltan ifs especificando enemigos etc

						//TO DO
						else if (name == "enemigo") {
							//Enemigo de prueba con la imagen de canel�n
							auto* enemy = mngr_->addEntity();
							enemy->addComponent<EntityAttribs>(200, 0.0, "enemy", Vector2D(4.5, 2), 0, 0);
							enemy->addComponent<Transform>(
								Vector2D(sdlutils().width() / 2.0f + 400, sdlutils().height() / 2.0f - 100),
								Vector2D(), 240.0f, 370.0f, 0.0f)->getFlip() = true;
							enemy->addComponent<Image>(&sdlutils().images().at("canelon"));
							enemy->setGroup<Enemy>(true);
							enemy->addComponent<UI>("canelon", 4);

							enemy->addComponent<EnemyStateMachine>();
							enemy->addComponent<EnemyAttack>();
							enemy->addComponent<Knockback>();
							enemy->addComponent<MovementSimple>();
							enemy->addComponent<FollowPlayer>();
							enemy->addComponent<EnemyStun>();
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
						auto globalIndexTile = tileList[i + j * mapDimensions_.x].ID;	//filas+columna*elementos_enuna_fila

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

						Vector2D renderPos = Vector2D(dest.x - Game::camera_.x, dest.y - Game::camera_.y);
						dest.x = renderPos.getX();
						dest.y = renderPos.getY();

						//COMPROBAR DE ALGUNA MANERA SI ES COLLIDER O KHE
						if (globalIndexTile != 0 && index < 2)

							//ESTO ES EL NOMBRE DE LA LAYER QUE SE CREE SOLO DE LAS COLISIONES
							/*if (tileLayer.getName() == "Collision")
								Tile(entity_->getMngr(), src, dest, tilesetsArr[index], true);
							else
								Tile(entity_->getMngr(), src, dest, tilesetsArr[index], false);*/

								//Esto esta porque falta depurar lo de arriba, hay que eliminarlo
							Tile(entity_->getMngr(), src, dest, tilesetsArr[index], false);
					}
				}
			}
		}
	}
}


//bool GameMap::intersectsWall(SDL_Rect rect) {
//	Point2D topLeftCoords = static_cast<PlayState*>(juego)->SDLPointToMapCoords(Point2D(rect.x, rect.y));
//	Point2D bottomRightCoords = static_cast<PlayState*>(juego)->SDLPointToMapCoords(Point2D(rect.x + rect.w - 1, rect.y + rect.h - 1));
//
//	for (int x = topLeftCoords.getX(); x <= bottomRightCoords.getX(); x++) {
//		for (int y = topLeftCoords.getY(); y <= bottomRightCoords.getY(); y++)
//			if (cells[x][y] == Wall) return true;
//	}
//	return false;
//}
