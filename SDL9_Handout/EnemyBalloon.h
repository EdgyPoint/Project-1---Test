#ifndef __ENEMYBALLOON_H__
#define __ENEMYBALLOON_H__

#include "Enemy.h"
#include "Path.h"

class EnemyBalloon : public Enemy
{

private:
	iPoint original_pos;
	fPoint distance;
	Animation fly, fly2, fly3;
	Path path;

public:
	EnemyBalloon(int x, int y, int option);
	void Move();
	void Shoot();
	int reload = 0;
	int initcounter = 0;
	float aux_float;
	fPoint speeds;

};
#endif

