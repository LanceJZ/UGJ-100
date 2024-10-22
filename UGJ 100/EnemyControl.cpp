#include "EnemyControl.h"

EnemyControl::EnemyControl()
{
}

EnemyControl::~EnemyControl()
{
}

void EnemyControl::SetPlayer(ThePlayer* player)
{
	Player = player;

}


void EnemyControl::SetParticleManager(ParticleManager* particles)
{
	Particles = particles;
}

bool EnemyControl::Initialize(Utilities* utilities)
{
	Common::Initialize(TheUtilities);


	return false;
}

bool EnemyControl::BeginRun()
{
	Common::BeginRun();

	Reset();

	return false;
}

void EnemyControl::FixedUpdate()
{
	Common::FixedUpdate();

}

void EnemyControl::NewGame()
{
	Reset();

}


void EnemyControl::Reset()
{

}
