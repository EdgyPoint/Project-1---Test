#ifndef __MODULESCENECASTLE_H__
#define __MODULESCENECASTLE_H__

#include "Module.h"

struct SDL_Texture;

class ModuleSceneCastle : public Module
{
public:
	ModuleSceneCastle();
	~ModuleSceneCastle();
	
	bool Start();
	update_status Update();
	bool CleanUp();
	

public:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphics2 = nullptr;
	SDL_Rect background;
	SDL_Rect npi;

	float yflag;
};
#endif
