#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleIntroScene.h"
#include "ModuleCastleScene.h"
#include "ModuleFadeToBlack.h"
#include "ModuleScoreScene.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL.h"


// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleScoreScene::ModuleScoreScene()
{
	background.h = 320;
	background.w = 234;
	background.x = 0;
	background.y = 0;
}

ModuleScoreScene::~ModuleScoreScene()
{}

// Load assets
bool ModuleScoreScene::Start()
{
	LOG("Loading score scene");

	graphics = App->textures->Load("assets/images/Score Screen.png");
	App->audio->audio = App->audio->Load("assets/bgm/Gunbird OST Character Selection.ogg");
	Mix_PlayMusic(App->audio->audio, -1);
	return true;
}

// UnLoad assets
bool ModuleScoreScene::CleanUp()
{
	LOG("Unloading score scene");
	App->textures->Unload(graphics);
	App->player->Disable();

	return true;
}

// Update: draw background
update_status ModuleScoreScene::Update()
{

	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &background, 0.75f); // sea and sky

	if (App->input->keyboard[SDL_SCANCODE_SPACE] && fading == false)
	{
		App->fade->FadeToBlack(this, App->scene_intro, 2.0f);
	}
	// TODO 2: make so pressing SPACE the HONDA stage is loaded

	return UPDATE_CONTINUE;
}