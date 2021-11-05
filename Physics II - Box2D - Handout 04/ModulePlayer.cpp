#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"

#ifdef _DEBUG
#pragma comment( lib, "Box2D/libx86/Debug/Box2D.lib" )
#else
#pragma comment( lib, "Box2D/libx86/Release/Box2D.lib" )
#endif
ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	b2BodyDef bodyR;
	bodyR.type = b2_dynamicBody;
	bodyR.position.Set(PIXEL_TO_METERS(283), PIXEL_TO_METERS(600));

	
	b2PolygonShape boxP;
	boxP.SetAsBox(PIXEL_TO_METERS(20) * 0.5f, PIXEL_TO_METERS(10) * 0.5f);

	b2FixtureDef fixtureR;
	fixtureR.shape = &boxP;
	fixtureR.density = 1.0f;

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	return UPDATE_CONTINUE;
}



