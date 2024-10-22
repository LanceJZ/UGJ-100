#pragma once
#include "Globals.h"
#include "Model3D.h"

class TheGround : public Model3D
{
public:
	enum SqureType
	{
		Empty = 0,
		Wall = 1
	};

	SqureType Squre[10][10];

	TheGround();
	virtual ~TheGround();

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void Update(float deltaTime);
	void Draw3D();

	void Spawn(Vector3 position);
	void Destroy();

private:


};
