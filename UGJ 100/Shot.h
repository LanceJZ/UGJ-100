#pragma once
#include "Model3D.h"
#include "Globals.h"

class Shot : public Model3D
{
public:
	Shot();
	virtual ~Shot();

	int HitPoints = 0;

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void Update(float deltaTime);
	void Draw3D();

	void Spawn(Vector3 position);
	void Spawn(Vector3 position, Vector3 velocity);
	void Spawn(Vector3 position, Vector3 velocity, float lifetime);
	void Destroy();

private:
	size_t LifeTimerID = 0;
};
