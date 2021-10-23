#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
#include "Box2D/Box2D/Box2D.h"

#define SMALLCIRCLENUMBER 10
#define BIGCIRCLENUMBER 3

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

public:
	p2List<PhysBody*> circles;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> ricks;
	p2List<PhysBody*> mapa;
	
	b2World* world;
	
	PhysBody* sensor;
	bool sensed;

	int ballPushForce = 0;

	SDL_Texture* circle;
	SDL_Texture* box;
	SDL_Texture* rick;
	uint bonus_fx;
	p2Point<int> ray;
	bool ray_on;

	PhysBody* sensor1;
	PhysBody* sensor2;
	PhysBody* sensor3;
	PhysBody* sensor4_1;
	PhysBody* sensor4_2;
	PhysBody* sensor4_3;

	//joint
	//b2RevoluteJointDef rjd1;
	PhysBody* bigCirclesSensor[BIGCIRCLENUMBER];



	PhysBody* bigCircles[BIGCIRCLENUMBER];
	PhysBody* smallCircles[SMALLCIRCLENUMBER];

	int score = 0;

	struct Ball {
		int x, y;
	};
	Ball ball;

	int ballY = 550;
};
