#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 12

//class ModuleCollision;
class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleAudio;
class ModuleParticles;
class ModuleRender;
class ModuleIntroScene;
class ModuleCastleScene;

class ModuleScoreScene;
class ModulePlayer;
class ModuleFadeToBlack;
class ModuleEnemies;
class Module;

class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleAudio* audio;
	ModuleParticles* particles;
	ModuleIntroScene* scene_intro;
	ModuleCastleScene* scene_castle;

	ModuleScoreScene* scene_score;
	ModulePlayer* player;
	ModuleFadeToBlack* fade;
	//ModuleCollision* collision;
	ModuleEnemies* enemies;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__