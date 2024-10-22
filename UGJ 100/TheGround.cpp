#include "TheGround.h"

TheGround::TheGround()
{
}

TheGround::~TheGround()
{
}

bool TheGround::Initialize(Utilities* utilities)
{
	Model3D::Initialize(TheUtilities);

	return false;
}

bool TheGround::BeginRun()
{
	Model3D::BeginRun();

	return false;
}

void TheGround::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

}

void TheGround::Draw3D()
{
	Model3D::Draw3D();
}

void TheGround::Spawn(Vector3 position)
{
	Entity::Spawn(position);

}

void TheGround::Destroy()
{
	Entity::Destroy();

}
