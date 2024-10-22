#include "ParticleCube.h"
ParticleCube::ParticleCube()
{
	LifeTimerID = Managers->EM.AddTimer();
}

ParticleCube::~ParticleCube()
{
}

void ParticleCube::SetManagers(TheManagers* managers)
{
	Managers = managers;
}

bool ParticleCube::Initialize(Utilities* utilities)
{
	Model3D::Initialize(utilities);

	return false;
}

bool ParticleCube::BeginRun()
{
	Model3D::BeginRun();

	return false;
}

void ParticleCube::Update(float deltaTime)
{
	Model3D::Update(deltaTime);
}

void ParticleCube::FixedUpdate(float deltaTime)
{
	Model3D::FixedUpdate(deltaTime);

	if (Managers->EM.TimerElapsed(LifeTimerID))
	{
		Enabled = false;
	}
}

void ParticleCube::Draw3D()
{
	Model3D::Draw3D();

}

void ParticleCube::Spawn(Vector3 position, Vector3 velocity, float radius,
	float speed, float time)
{
	Enabled = true;

	Vector3 spawnPos = position;
	spawnPos.x += GetRandomFloat(-radius, radius);
	spawnPos.y += GetRandomFloat(-radius, radius);
	Position = spawnPos;

	Managers->EM.ResetTimer(LifeTimerID, time);

	Vector3 AddedVel = GetRandomVelocity(GetRandomFloat(speed * 0.25f, speed));
	Velocity = Vector3Add(velocity, AddedVel);
}