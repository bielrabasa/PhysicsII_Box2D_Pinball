#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
#include "Box2D/Box2D/Box2D.h"

#define SMALLCIRCLENUMBER 10
#define BIGCIRCLENUMBER 3
#define SMALLGCIRCLENUMBER 10

class PhysBody;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);
	void FontDraw(int score, int n, int posX, int posY, int separacio, float scale);

public:
	p2List<PhysBody*> circles;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> ricks;
	p2List<PhysBody*> ricks2;
	p2List<PhysBody*> palasD;
	p2List<PhysBody*> palasE;
	p2List<PhysBody*> mapa;
	p2List<PhysBody*> startL;
	
	b2World* world;
	
	PhysBody* sensor;
	bool sensed;

	int ballPushForce = 0;
	int cargablack = 50;


	SDL_Texture* flechas;
	SDL_Texture* bigBall;
	SDL_Texture* smallBall;
	SDL_Texture* circulosPequeños;

	SDL_Texture* circle;
	SDL_Texture* fonsSprite;
	SDL_Texture* startSprite;
	SDL_Texture* finishSprite;
	SDL_Texture* palaD;
	SDL_Texture* palaE;
	SDL_Texture* nombres; 
	SDL_Texture* canoAnimacio;
	SDL_Texture* barra_carga;
	SDL_Rect canoAnimacioRect;
	enum {A1, A2, A3, AN}canoAnimacioEnum = AN;

	uint circulos_fx;
	uint blaster_fx;
	uint sables_fx;
	uint start_fx;
	uint bolafora_fx;
	uint xoc1_fx;
	uint palancas_fx;
	uint tunel_fx;
	uint carga_fx;
	p2Point<int> ray;
	bool ray_on;

	PhysBody* sensor1;
	PhysBody* sensor2;
	PhysBody* sensor3;
	PhysBody* sensor4_1;
	PhysBody* sensor4_2;
	PhysBody* sensor4_3;
	PhysBody* sensor5;
	PhysBody* sensor6;
	PhysBody* sensor7;
	PhysBody* sensor8;
	PhysBody* sensor9;

	PhysBody* bigCirclesSensor[BIGCIRCLENUMBER];
	PhysBody* SmallCirclesSensor[SMALLGCIRCLENUMBER];

	PhysBody* bigCircles[BIGCIRCLENUMBER];
	PhysBody* smallCircles[SMALLCIRCLENUMBER];

	bool stopBall = false;
	b2Vec2 stopVelocityBall = { 0,-0.12f };//-0.12 es la velocidad y que detiene la pelota 
	int stopBallCont = 0;

	int sensorResetCont = 300;

	int score = 0;
	int max_score = 0;
	int prev_score = 0;
	int posicioFont = 110;
	int posicioFontY = 20;

	int posicioVidesX = 260;
	int posicioVidesY = 30;

	int ball_count = 0;

	Uint8 timeFlecha = 21;
	Uint8 timeBigBall = 21;
	Uint8 timeSmallBall = 21;
	bool timeSwitchFlecha = false;
	bool timeSwitchBigBall = false;
	bool timeSwitchSmallBall = false;

	bool lose = false;
	bool start = true;

	bool dretaPala = false;
	bool esquerraPala = false;

	bool BC1 = false;
	bool BC2 = false;
	bool BC3 = false;

	struct Ball {
		int x, y;
	};
	Ball ball;

	int ballY = 550;
};
