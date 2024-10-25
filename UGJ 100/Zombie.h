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
	bool MoveToWaypoint = false;
	bool HitWall = false;
	bool GoingAfterPlayer = false;
	bool HitPlayer = false;

	float Speed = 0.0f;

	Vector3 DestinationWaypoint = {0.0f,0.0f,0.0f};

	Entity LookAhead = {};

	std::vector<Entity*> Walls = {};

	void MoveForward(float deltaTime);
	void CalculateDestinationWaypoint(float deltaTime);
	void CheckHit();
	void CheckPlayerHit();
};
