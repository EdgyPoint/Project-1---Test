#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleParticles.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneIntro.h"
#include "ModuleSceneCastle.h"
#include "ModuleSceneScore.h"
#include "ModuleAudio.h"
#include "ModuleEnemies.h"
#include "SDL/include/SDL.h"



ModuleSceneCastle::ModuleSceneCastle()
{
	background.h = 1677;
	background.w = 224;
	background.x = 0;
	background.y = 0;

	npi.h = 5;
	npi.w = 1000;
	npi.x = 0;
	npi.y = -10;
}


ModuleSceneCastle::~ModuleSceneCastle()
{
}

bool ModuleSceneCastle::Start()
{
	LOG("Loading castle scene");

	App->player->Enable();
	App->particles->Enable();
	App->enemies->Enable();
	
	yflag = -1357;

	App->collision->AddCollider(npi, COLLIDER_WALL);
	//--Enemies--


	//--Loading spritesheets--
	graphics = App->textures->Load("assets/images/Castle Background better.png");
	graphics2 = App->textures->Load("assets/images/Castle Upper Background better.png");

	//--Loading audio--
	App->audio->audio = App->audio->Load("assets/bgm/castle.ogg");
	Mix_PlayMusic(App->audio->audio, -1);

	return true;
}

bool ModuleSceneCastle::CleanUp()
{
	LOG("Unloading castle scene");

	//--Unloading loaded textures--
	App->textures->Unload(graphics);
	App->textures->Unload(graphics2);

	//
	App->enemies->Disable();
	App->particles->Disable();
	App->player->Disable();
	if (App->player2->IsEnabled() == true)
	{
		App->player2->Disable();
	}
	App->collision->Disable();

	return true;
}

update_status ModuleSceneCastle::Update()
{
	//--Screen--
	yflag += 0.55f;


	//--Draw bacground layer
	App->render->Blit(graphics, 0, yflag, &background, 10.0f);
	// -- Draw background top layer
	App->render->Blit(graphics2, 0, yflag, &background, 10.0f);

	return UPDATE_CONTINUE;
}