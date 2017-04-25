#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
//#include "ModuleCollision.h"
#include "ModuleParticles.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("assets/images/Marion.png");

	marionbeam[0].anim.PushBack({ 166,67, 7, 29});
	marionbeam[0].anim.loop = false;
	marionbeam[0].anim.speed = 0.3f;
	marionbeam[0].speed.y = -4;
	marionbeam[0].life = 4000;

	marionbeam[1].anim.PushBack({ 166, 97, 7, 29 });
	marionbeam[1].anim.loop = false;
	marionbeam[1].anim.speed = 0.3f;
	marionbeam[1].speed.y = -4;
	marionbeam[1].life = 4000;

	marionbeam[2].anim.PushBack({ 166, 127, 7, 29 });
	marionbeam[2].anim.loop = false;
	marionbeam[2].anim.speed = 0.3f;
	marionbeam[2].speed.y = -4;
	marionbeam[2].life = 4000;


	balloonshoot.anim.PushBack({ 31, 425, 6, 6 });
	balloonshoot.anim.PushBack({ 47, 425, 6, 6 });
	balloonshoot.anim.PushBack({ 79, 425, 6, 6 });
	balloonshoot.anim.PushBack({ 111, 425, 6, 6 });
	balloonshoot.anim.PushBack({ 143, 425, 6, 6 });
	balloonshoot.anim.PushBack({ 191, 425, 6, 6 });
	balloonshoot.anim.PushBack({ 15, 441, 6, 6 });
	balloonshoot.anim.PushBack({ 47, 441, 6, 6 });
	balloonshoot.anim.loop = true;
	balloonshoot.anim.speed = 0.3f;
	balloonshoot.speed.y = 3;
	balloonshoot.life = 4000;


	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= p->born)
		{
			
			/*collider->type == COLLIDER_PLAYER_SHOT && p->apperance == 0)
			{
				p->position.x = App->player->position.x + 11; p->apperance++;
			}*/
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			if (p->fx_played == false)
			{
				p->fx_played = true;
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			
			p->position.x = x;
			p->position.y = y;
			/*if (collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);*/
			active[i] = p;
			break;
		}
	}
}

// TODO 5: Make so every time a particle hits a wall it triggers an explosion particle
/*void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			delete active[i];
			active[i] = nullptr;
			break;
		}
	}
}*/
// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) :
	anim(p.anim), position(p.position), speed(p.speed),
	fx(p.fx), born(p.born), life(p.life)
{}

Particle::~Particle()
{
	/*if (collider != nullptr)
		App->collision->EraseCollider(collider);*/
}

bool Particle::Update()
{
	bool ret = true;
	int aux = (SDL_GetTicks() - born);

	if (life > 0)
	{
		if (aux > (int)life)
			ret = false;
	}
	else
		if (anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;

	/*if (collider != nullptr && SDL_GetTicks() >= born)
		collider->SetPos(position.x, position.y);
	if (collider != nullptr && SDL_GetTicks() < born)
		collider->SetPos(-50, 500);*/
	return ret;
}

