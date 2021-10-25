#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

#ifdef _DEBUG
#pragma comment( lib, "Box2D/libx86/Debug/Box2D.lib" )
#else
#pragma comment( lib, "Box2D/libx86/Release/Box2D.lib" )
#endif

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	circle = box = rick = NULL;
	ray_on = false;
	sensed = false;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;
	
	circle = App->textures->Load("pinball/wheel.png");

	box = App->textures->Load("pinball/Maqueta2.png");
	rick = App->textures->Load("pinball/Start.png");
	rick2 = App->textures->Load("pinball/lose.png");
	circulos_fx = App->audio->LoadFx("pinball/minicercles.wav");
	sables_fx = App->audio->LoadFx("pinball/sable.wav");

	//sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 50);

	circles.add(App->physics->CreateCircle(890, ballY, 7));
	circles.getLast()->data->listener = this;
	circles.getLast()->data->body->SetBullet(true);

	boxes.add(App->physics->CreateRectangle(50, 25, 100, 50));
	//App->renderer->Blit(box, 50, 25, (310, 660));

	sensor1 = App->physics->CreateRectangleSensor(140, 640, 85, 20, 0);
	sensor2 = App->physics->CreateRectangleSensor(290, 573, 20, 40, 0);

	sensor3 = App->physics->CreateRectangleSensor(45, 130, 30, 30, 0);
	sensor4_1 = App->physics->CreateRectangleSensor(252, 300, 30, 60, 0);
	sensor4_2 = App->physics->CreateRectangleSensor(260, 350, 30, 45, 0);
	sensor4_3 = App->physics->CreateRectangleSensor(240, 400, 30, 50, 0);

	//fets
	sensor5 = App->physics->CreateRectangleSensor(27, 404, 50, 10, 20.09);
	sensor8 = App->physics->CreateRectangleSensor(78, 524, 80, 10, -1.9);

	//fuym
	sensor7 = App->physics->CreateRectangleSensor(190, 522, 80, 10, 1.9);
	sensor6 = App->physics->CreateRectangleSensor(255, 228, 70, 10, 1.71);
	sensor9 = App->physics->CreateRectangleSensor(210, 370, 50, 10, 2.1);



	bigCircles[0] = App->physics->CreateCircle2(123, 145, 22);
	bigCircles[1] = App->physics->CreateCircle2(220, 173, 22);
	bigCircles[2] = App->physics->CreateCircle2(146, 249, 22);

	bigCirclesSensor[0] = App->physics->CreateCircleSensor(123, 145, 24);
	bigCirclesSensor[1] = App->physics->CreateCircleSensor(220, 173, 24);
	bigCirclesSensor[2] = App->physics->CreateCircleSensor(145, 249, 24);

	smallCircles[0] = App->physics->CreateCircle2(155, 292, 4);
	smallCircles[1] = App->physics->CreateCircle2(113, 305, 4);
	smallCircles[2] = App->physics->CreateCircle2(195, 303, 4);
	smallCircles[3] = App->physics->CreateCircle2(165, 334, 4);
	smallCircles[4] = App->physics->CreateCircle2(123, 363, 4);
	smallCircles[5] = App->physics->CreateCircle2(183, 377, 4);
	smallCircles[6] = App->physics->CreateCircle2(144, 390, 4);
	smallCircles[7] = App->physics->CreateCircle2(100, 396, 4);
	smallCircles[8] = App->physics->CreateCircle2(112, 429, 4);
	smallCircles[9] = App->physics->CreateCircle2(161, 431, 4);
	

	//Press R to start
	int rick_head[6] = {
	14, 36,
	42, 40,
	40, 0,
	};
	ricks.add(App->physics->CreateChain2(0, 0, rick_head, 6));

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{

	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		ray_on = !ray_on;
		ray.x = App->input->GetMouseX();
		ray.y = App->input->GetMouseY();
	}

	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.getLast()->data->body->GetWorld()->DestroyBody(circles.getLast()->data->body);
		circles.clear();
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 7));
		circles.getLast()->data->listener = this;
		circles.getLast()->data->body->SetBullet(true);
	}

	//move palanca esquerra
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
	{
		App->physics->palanca->body->ApplyForce(b2Vec2(0, -10), b2Vec2(10, 0), true);
	}
	else if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP) {
		App->physics->palanca->body->ApplyForce(b2Vec2(0, 10), b2Vec2(10, 0), true);
	}
	else if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
		App->physics->palanca->body->ApplyForce(b2Vec2(0, -1), b2Vec2(10, 0), true);
	}

	//move palanca dreta
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		App->physics->palanca2->body->ApplyForce(b2Vec2(0, -10), b2Vec2(-10, 0), true);
	}
	else if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP) {
		App->physics->palanca2->body->ApplyForce(b2Vec2(0, 10), b2Vec2(-10, 0), true);
	}
	else if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
		App->physics->palanca2->body->ApplyForce(b2Vec2(0, -1), b2Vec2(-10, 0), true);
	}	

	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN && ball_count == 0) {
		//BORRAR BODY, netejar llista, crear bola
		circles.getLast()->data->body->GetWorld()->DestroyBody(circles.getLast()->data->body);
		circles.clear();
		circles.add(App->physics->CreateCircle(290, ballY, 7));
		circles.getLast()->data->listener = this;
		circles.getLast()->data->body->SetBullet(true);
		//Borra el PRESS R TO START
		ricks.getLast()->data->body->GetWorld()->DestroyBody(ricks.getLast()->data->body);
		ricks.clear();
		ball_count = 3;
	}

	if (App->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN && ball_count == 0)
	{
		boxes.getFirst()->data->body->GetWorld()->DestroyBody(boxes.getFirst()->data->body);
		boxes.clear();
		int rick_head[6] = {
			14, 36,
			42, 40,
			40, 0,
		};
		ricks.add(App->physics->CreateChain2(0, 0, rick_head, 6));
	}

	if(App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		boxes.add(App->physics->CreateRectangle(App->input->GetMouseX(), App->input->GetMouseY(), 100, 50));
	}

	if(App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		// Pivot 0, 0
		int rick_head[64] = {
			14, 36,
			42, 40,
			40, 0,
			75, 30,
			88, 4,
			94, 39,
			111, 36,
			104, 58,
			107, 62,
			117, 67,
			109, 73,
			110, 85,
			106, 91,
			109, 99,
			103, 104,
			100, 115,
			106, 121,
			103, 125,
			98, 126,
			95, 137,
			83, 147,
			67, 147,
			53, 140,
			46, 132,
			34, 136,
			38, 126,
			23, 123,
			30, 114,
			10, 102,
			29, 90,
			0, 75,
			30, 62
		};

		ricks.add(App->physics->CreateChain(App->input->GetMouseX(), App->input->GetMouseY(), rick_head, 64));
	}

	
	circles.getLast()->data->GetPosition(ball.x, ball.y);

	if (max_score >= score)
		max_score = score;

	//reiniciar la bola sensor
	LOG("Ball cont: %d",ball_count)
	if (sensor1->Contains(ball.x,ball.y) && ball_count >= 1) {//Limitador de bolas a 3
		//LOG("uwu");
		ball_count--;
		score = 0;
		circles.getLast()->data->body->GetWorld()->DestroyBody(circles.getLast()->data->body);
		circles.clear();
		circles.add(App->physics->CreateCircle(290, ballY, 7));
		circles.getLast()->data->listener = this;
		circles.getLast()->data->body->SetBullet(true);
	}

	//Cuando llega a esta a 0 el numero de pelotas restantes hace que no aparezcan mas pelotas en el mapa
	if (sensor1->Contains(ball.x, ball.y) && ball_count <= 0) {
		circles.getLast()->data->body->GetWorld()->DestroyBody(circles.getLast()->data->body);
		circles.clear();
		circles.add(App->physics->CreateCircle(890, ballY, 7));
		circles.getLast()->data->listener = this;
		circles.getLast()->data->body->SetBullet(true);
		
		//imprime por pantalla como reiniciar
		int rick_head[6] = {
		14, 36,
		42, 40,
		40, 0,
		};
		ricks2.add(App->physics->CreateChain2(0, 0, rick_head, 6));
	}

	//sensor inicial bola
	if (sensor2->Contains(ball.x, ball.y)) {
		//LOG("uwu");
		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		{
			ballPushForce += 2;
		}
		else if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
		{
			circles.getLast()->data->body->ApplyForceToCenter(b2Vec2(0, -ballPushForce), true);
			ballPushForce = 0;
		}
	}

	//sensor dalt-esquerra

	if (sensorResetCont < 200) {
		sensorResetCont++;
	}
	LOG("Numero sensor tempo %d", sensorResetCont);
	if (sensor3->Contains(ball.x, ball.y)) {
		
		//Codigo que para la pelota y la lanza despues de 1 segundo
		
		if (sensorResetCont >= 200) {
			stopBall = true;
			sensorResetCont = 0;
		}
		if (stopBall) {
			circles.getLast()->data->body->SetLinearVelocity(stopVelocityBall);
			stopBallCont++;
		}
		if (stopBallCont == 60) {
			circles.getLast()->data->body->ApplyForceToCenter(b2Vec2(0, 50), true);
			stopBallCont = 0;
			stopBall = false;
			score += 5;
			LOG("Score: %d", score);
		}
		//circles.getLast()->data->body->ApplyForceToCenter(-2*circles.getLast()->data->body->GetLinearVelocity(), true); //CANVIAT
	}

	if (sensor5->Contains(ball.x, ball.y)) {
		LOG("%d", score)
		score += 3;
		//circles.getLast()->data->body->ApplyForceToCenter(-2*circles.getLast()->data->body->GetLinearVelocity(), true); //CANVIAR
		circles.getLast()->data->body->ApplyForceToCenter(b2Vec2(40, -40), true);
	}
	if (sensor8->Contains(ball.x, ball.y)) {
		LOG("%d", score);
		score += 2;
		//circles.getLast()->data->body->ApplyForceToCenter(-2*circles.getLast()->data->body->GetLinearVelocity(), true); //CANVIAR
		circles.getLast()->data->body->ApplyForceToCenter(b2Vec2(30, -50), true);
	}	
	if (sensor7->Contains(ball.x, ball.y)) {
		LOG("%d", score);
		score += 2;
		//circles.getLast()->data->body->ApplyForceToCenter(-2*circles.getLast()->data->body->GetLinearVelocity(), true); //CANVIAR
		circles.getLast()->data->body->ApplyForceToCenter(b2Vec2(-30, -50), true);
	}	

	if (sensor6->Contains(ball.x, ball.y)) {
		LOG("%d", score);
		score += 3;
		//circles.getLast()->data->body->ApplyForceToCenter(-2*circles.getLast()->data->body->GetLinearVelocity(), true); //CANVIAR
		circles.getLast()->data->body->ApplyForceToCenter(b2Vec2(-40, -50), true);
	}	
	if (sensor9->Contains(ball.x, ball.y)) {
		LOG("%d", score);
		score += 3;
		//circles.getLast()->data->body->ApplyForceToCenter(-2*circles.getLast()->data->body->GetLinearVelocity(), true); //CANVIAR
		circles.getLast()->data->body->ApplyForceToCenter(b2Vec2(-50, -30), true);
	}

	//sensor accelerador dreta
	if ((sensor4_1->Contains(ball.x, ball.y)) || (sensor4_2->Contains(ball.x, ball.y)) || (sensor4_3->Contains(ball.x, ball.y))) {
		if (circles.getLast()->data->body->GetLinearVelocity().y > 0) {
			circles.getLast()->data->body->ApplyForceToCenter(b2Vec2(0, -15), true);
		}
		else {
			circles.getLast()->data->body->ApplyForceToCenter(circles.getLast()->data->body->GetLinearVelocity(), true);
		}
	}
	
	
	//Big circles sensor
	/*
		if (bigCirclesSensor[0]->Contains(ball.x, ball.y)) {
			//circles.getLast()->data->body->ApplyForceToCenter(b2Vec2(0, -30), true);
			circles.getLast()->data->body->ApplyForceToCenter(-30 * circles.getLast()->data->body->GetLinearVelocity(), true); //CANVIAR

		}
		if (bigCirclesSensor[1]->Contains(ball.x, ball.y)) {
			circles.getLast()->data->body->ApplyForceToCenter(-30 * circles.getLast()->data->body->GetLinearVelocity(), true); //CANVIAR
			//circles.getLast()->data->body->ApplyForceToCenter(b2Vec2(0, -30), true);
		}
		if (bigCirclesSensor[2]->Contains(ball.x, ball.y)) {
			circles.getLast()->data->body->ApplyForceToCenter(-30 * circles.getLast()->data->body->GetLinearVelocity(), true); //CANVIAR
			//circles.getLast()->data->body->ApplyForceToCenter(b2Vec2(0, -30), true);
		}
	*/

	//Big Circles
	for (int i = 0; i < BIGCIRCLENUMBER; i++) {
		if (bigCircles[i]->body->GetContactList() != NULL) {
			//circles.getLast()->data->body->ApplyForceToCenter(b2Vec2(0, -10), true);
		}
	}
	//Small Circles
	for (int i = 0; i < SMALLCIRCLENUMBER; i++) {
		if (smallCircles[i]->body->GetContactList() != NULL) {
			//circles.getLast()->data->body->ApplyForceToCenter(b2Vec2(0, -10), true);
		}
	}



	// Prepare for raycast ------------------------------------------------------
	
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();
	int ray_hit = ray.DistanceTo(mouse);

	fVector normal(0.0f, 0.0f);

	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* c = boxes.getFirst();

	while (c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(box, x, y, NULL, 1.0f, c->data->GetRotation());
		/*if(ray_on)
		{
			int hit = c->data->RayCast(ray.x, ray.y, mouse.x, mouse.y, normal.x, normal.y);
			if(hit >= 0)
				ray_hit = hit;
		}*/
		c = c->next;
	}

	c = circles.getFirst();


	while (c != NULL)
	{
		int x, y;

		/*if (ray_on) {
			int hit = c->data->RayCast(ray.x, ray.y, mouse.x, mouse.y, normal.x, normal.y);
			if (hit >= 0)
			{
				ray_hit = hit;
				if (ray_hit) {
					circles.getLast()->data->body->ApplyForceToCenter(b2Vec2(0, -10), true);
				}
			}
		}*/

		c->data->GetPosition(x, y);
		App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = ricks.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(rick, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = ricks2.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(rick2, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	// ray -----------------
	if(ray_on == true)
	{
		fVector destination(mouse.x-ray.x, mouse.y-ray.y);
		destination.Normalize();
		destination *= ray_hit;

		App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

		if(normal.x != 0.0f)
			App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
	}



	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	//Colisió boles grans
	if (bodyA == circles.getLast()->data && (bodyB == bigCirclesSensor[0] || bodyB == bigCirclesSensor[1] || bodyB == bigCirclesSensor[2])) {
		App->audio->PlayFx(circulos_fx);
		int x, y, xs = 0, ys = 0;
		for (int i = 0; i < 3; i++) {
			if (bodyB == bigCirclesSensor[i]) {
				bigCirclesSensor[i]->GetPosition(xs, ys);
				break;
			}
		}
		circles.getLast()->data->GetPosition(x, y);
		circles.getLast()->data->body->ApplyForceToCenter(b2Vec2(x - xs, y - ys), true);
	}

	if(bodyA == circles.getLast()->data && (bodyB == sensor5 || bodyB == sensor6 || bodyB == sensor7 || bodyB == sensor8 || bodyB == sensor9))
		App->audio->PlayFx(sables_fx);
}
