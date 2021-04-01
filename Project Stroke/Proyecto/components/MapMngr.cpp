#include "MapMngr.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/Game.h"

void MapMngr::init() {
	loadNewMap("resources/images/tiled/Mapa.tmx");
}

void MapMngr::render() {
	int index;
	const auto& layers = map_.getLayers();
	const auto& tilesets = map_.getTilesets();
	for (const auto& layer : layers)
	{
		//SI ES UNA CAPA DE OBJETOS, TODAVÍA NO
		//if (layer->getType() == tmx::Layer::Type::Object)
		//{
		//	const auto& objectLayer = layer->getLayerAs<tmx::ObjectGroup>();
		//	const auto& objects = objectLayer.getObjects();
		//	for (const auto& object : objects)
		//	{
		//		//do stuff with object properties
		//	}
		//} else

		//SI ES UNA CAPA DE TILES
		index = 0;	//Recorrerá los tilesets para saber a cual corresponde cada tile
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

					int scale = 6;

					SDL_Rect dest;
					dest.x = x * scale; dest.y = y * scale;
					dest.w = dest.h = tilesDimensions_.x * scale;

					Vector2D renderPos = Vector2D(dest.x - Game::camera_.x, dest.y - Game::camera_.y);
					dest.x = renderPos.getX();
					dest.y = renderPos.getY();

					if (globalIndexTile != 0)
						tilesetsArr[index]->render(src, dest);
				}
			}
		}
	}
}

void MapMngr::loadNewMap(string map) {
	if (map_.load(map)) {

		mapDimensions_ = map_.getTileCount();
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

	}
}
