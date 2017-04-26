#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneCastle.h"
#include "ModuleSceneScore.h"
#include "ModuleAudio.h"
#include "ModuleFonts.h"
#include "ModuleCollision.h"
#include "SDL/include/SDL.h"



ModuleSceneScore::ModuleSceneScore()
{
	background.h = 320;
	background.w = 234;
	background.x = 0;
	background.y = 0;
}


ModuleSceneScore::~ModuleSceneScore()
{
}

bool ModuleSceneScore::Start()
{
	LOG("Loading score scene");

	//--Loading textures--
	graphics = App->textures->Load("assets/images/Score Screen.png");

	//--Loading audio--
	App->audio->audio = App->audio->Load("assets/bgm/Gunbird OST Character Selection.ogg");
	Mix_PlayMusic(App->audio->audio, -1);

	return true;
}

bool ModuleSceneScore::CleanUp()
{
	LOG("Unloading score scene");

	//--Setting both player scores to initial value--
	App->player->score = 0;
	App->player2->score = 0;

	//--Unload loaded textures--
	App->textures->Unload(graphics);

	return true;
}

update_status ModuleSceneScore::Update()
{
	//--Draw background--
	App->render->Blit(graphics, 0, 0, &background, 0.75f);

}