#include "../ecs/Entity.h"


#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
using namespace std;
class ObstacleMoveable: public Component {
public:
	ObstacleMoveable(Texture* wTx, float x, float y, float z, int floor) : lastTime_(0), spawnTime_(5000), lifeTime_(3000), time_(0),
		warningTime_(2000), warningTimeFlickering_(100),
		spawns_(0), warningTx(wTx),
		obstacle(nullptr), vel(-10), x_(x), y_(y), z_(z), floor_(floor),
		gamestate(nullptr)
	{}
	virtual ~ObstacleMoveable();
	virtual void init() override;
	void update() override;
	void render() override;
private:
	Entity* obstacle; //el coche en cuestion que va a cohcar con el jugador

	float vel; //la velocidad del coche (tmb la distancia y todo lo que necesite)
	float x_, y_, z_; //coordenadas en la que debera de spawnear el coche
	int floor_; //el nivel al que va a spawnear si esto llegase a ser necesario

	Texture* warningTx; //la textura que se usara como (aviso) de queva a pasar un coche por esa zona
	
	float
		time_,
		lastTime_,

		spawnTime_,
		lifeTime_,

		warningTime_, //a cuanto tiempo antes avisa de que sale un coche
		warningTimeFlickering_; //el intervalo de parpadear, cuanto dura un parpadeo
		//warningTimeLife_; //el timepo maximo que va a estar haciendolo, creo que no me hace falta realmente

	int spawns_; //auxiliar para calcular cuantos coches ha spawneado y asi cuadrar el spawTime y que saque mas coches/avisos;


	GameStates* gamestate;
};