#pragma once
#include "TheManagers.h"
#include "Model3D.h"

class ParticleCube : public Model3D
{
public:
	ParticleCube();
	virtual ~ParticleCube();

	void SetManagers(TheManagers* managers);

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void Update(float deltaTime);
	void FixedUpdate(float deltaTime);
	void Draw3D();

	void Spawn(Vector3 position, Vector3 velocity, float radius, float speed, float time);

private:
	size_t LifeTimerID = 0;

	TheManagers* Managers = nullptr;
};
