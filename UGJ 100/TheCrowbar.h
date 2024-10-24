#pragma once
#include "Globals.h"
#include "Model3D.h"

class TheCrowbar : public Model3D
{
public:
	TheCrowbar();
	virtual ~TheCrowbar();

	int Damage = 5;
	bool Swinging = false;

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void Update(float deltaTime);
	void Draw3D();

	void Spawn(Vector3 position);
	void Destroy();

	void Swing();
	void Hit();

private:

	void DoTheSwing();
};
