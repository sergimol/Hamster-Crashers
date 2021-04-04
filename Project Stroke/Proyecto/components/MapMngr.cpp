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
				for (const auto& object : objects)
				{
					//do stuff with object properties
					auto& name = object.getName();
					auto mngr_ = entity_->getMngr();

					auto& players = mngr_->getPlayers();
					auto& enemies = mngr_->getEnemies();
					auto& obstacles = mngr_->getObstacles();

					if (name == "sardinilla") {
						//Sardinilla
						auto* hamster1 = mngr_->addEntity();
						hamster1->addComponent<Transform>(
							Vector2D(object.getPosition().x * scale, object.getPosition().y * scale),
							Vector2D(), 256.0f, 256.0f, 0.0f);
						hamster1->addComponent<EntityAttribs>(100, 0.0, "sardinilla", Vector2D(7, 4.5));
						//hamster1->addComponent<Image>(&sdlutils().images().at("sardinilla"));
						hamster1->addComponent<Animator>(
							&sdlutils().images().at("sardinillaSheet"),
							64,
							64,
							3,
							3,
							220,
							Vector2D(0, 0),
							3
							);
						hamster1->addComponent<HamsterStateMachine>();
						hamster1->addComponent<Movement>();
						hamster1->addComponent<LightAttack>();
						hamster1->addComponent<StrongAttack>();
						hamster1->addComponent<UI>("sardinilla", 0);


						hamster1->addComponent<HeartUI>("sardinilla", 0);
						//hamster1->addComponent<Pray>(30, 50);
						//hamster1->addComponent<Roll>();
						//hamster1->addComponent<Turret>();

						hamster1->addComponent<Poison>(5);
						hamster1->addComponent<Stroke>();
						hamster1->addComponent<Combos>();
						hamster1->setGroup<Ally>(true);
						hamster1->addComponent<ControlHandler>(1);
						hamster1->addComponent<Stun>();
						hamster1->addComponent<Knockback>();
						hamster1->addComponent<GetItem>();

						players.push_back(hamster1);

						//Igual luego no lo usammos pero por si aca
						mngr_->setHandler<Hamster1>(hamster1);
					}
					else if (name == "enemigo") {
						//Enemigo de prueba con la imagen de canelón
						auto* enemy = mngr_->addEntity();
						enemy->addComponent<EntityAttribs>(200, 0.0, "enemy", Vector2D(4.5, 2));
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

			//SI ES UNA CAPA DE TILES
			int index = 0;	//Recorrerá los tilesets para saber a cual corresponde cada tile
			if (layer->getType() == tmx::Layer::Type::Tile)
			{
				const auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();
				//read out tile layer properties etc...
				for (int j = 0; j < mapDimensions_.y; j++) {
					for (int i = 0; i < mapDimensions_.x; i++) {


						//Guardamos el indice global del tile (nos servirá para saber en qué tileset se encuentra)
						auto tileList = tileLayer.getTiles();
						auto globalIndexTile = tileList[i + j * mapDimensions_.x].ID;	//filas+columna*elementos_enuna_fila

					//Necesitamos saber a cual de los tilesets pertenece esa posicion
						while (globalIndexTile > tilesets[index].getLastGID()) {
							index++;	//Marca la posicion del tileset al que pertenece el tile
						}

						//Calculamos la posicion del tile en la pantalla -> DestRect
						auto x = i * tilesDimensions_.x;
						auto y = j * tilesDimensions_.y;

						//Calculamos la posición del tile en el tileset -> SrcRect
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
							Tile(entity_->getMngr(), src, dest, tilesetsArr[index],true);
					}
				}
			}
		}
	}
}
