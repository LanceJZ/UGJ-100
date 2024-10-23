#pragma once
#include "Enemy.h"

class Zombie : public Enemy
{
public:
	Zombie();
	virtual ~Zombie();

	void SetWalls(std::vector<Entity*> walls);
	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void Update(float deltaTime);
	void Draw3D();

	void Spawn();
	void Spawn(Vector3 position);
	void Destroy();

private:
	std::vector<Entity*> Walls = {};


	void MoveForward(float deltaTime);
};
