#include "Shot.h"

Shot::Shot()
{
	LifeTimerID = Managers.EM.AddTimer();
}

Shot::~Shot()
{
}

bool Shot::Initialize(Utilities* utilities)
{
	Model3D::Initialize(TheUtilities);

	return false;
}

bool Shot::BeginRun()
{
	Enabled = false;

	return false;
}

void Shot::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

	if (Managers.EM.TimerElapsed(LifeTimerID)) Destroy();

	CheckScreenEdge();
}

void Shot::Draw3D()
{
	Model3D::Draw3D();
}

void Shot::Spawn(Vector3 position)
{
	Entity::Spawn(position);
}

void Shot::Spawn(Vector3 position, Vector3 velocity)
{
	Spawn(position);
	Velocity = velocity;
}

void Shot::Spawn(Vector3 position, Vector3 velocity, float lifetime)
{
	Managers.EM.ResetTimer(LifeTimerID, lifetime);
	Spawn(position, velocity);
}

void Shot::Destroy()
{
	Entity::Destroy();
}