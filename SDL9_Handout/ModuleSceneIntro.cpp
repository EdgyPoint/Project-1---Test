#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneIntro.h"
#include "ModuleSceneCastle.h"
#include "ModuleSceneScore.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL.h"


ModuleSceneIntro::ModuleSceneIntro()
{
	background.h = 320;
	background.w = 224;
	background.x = 0;
	background.y = 0;

	startbutton.PushBack({ 0, 320, 68, 13 });
	startbutton.PushBack({ 0, 333, 68, 13 });
	startbutton.speed = 0.03f;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro intro");
	
	//--Loading Background texture--
	graphics = App->textures->Load("assets/images/Intro Screen.png");
	//--Loading Audio--
	App->audio->audio = App->audio->Load("assets/bgm/castle.ogg");
	Mix_PlayMusic(App->audio->audio, -1);
	
	return true;
}

// UnLoad assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	//--Unloading loaded textures--
	App->textures->Unload(graphics);

	//--Disabling Modules--
	App->scene_intro->Disable();
	
	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	//--Draw Intro background--
	App->render->Blit(graphics, 0, 0, &background, 0.75f);
	App->render->Blit(graphics, 75, 224, &(startbutton.GetCurrentFrame()), 0.01f);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->audio->sfx = App->audio->LoadSFX("assets/SFX/ganbaado.wav");
		Mix_PlayChannel(-1, App->audio->sfx, 0);
		App->fade->FadeToBlack(this, App->scene_castle, 2.0f);
	}
	return UPDATE_CONTINUE;
}