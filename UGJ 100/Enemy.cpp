#include "Enemy.h"

Enemy::Enemy()
{
	ShotTimerID = Managers.EM.AddTimer();
}

Enemy::~Enemy()
{
}

void Enemy::SetPlayer(ThePlayer* player)
{
	Player = player;
}

void Enemy::SetShotModel(Model model)
{
	ShotModel = model;
}

void Enemy::SetFireSound(Sound fireSound)
{
	FireSound = fireSound;
}

void Enemy::SetExplodeSound(Sound explodeSound)
{
	ExplodeSound = explodeSound;
}

void Enemy::SetParticleManager(ParticleManager* particleManager)
{
	Particles = particleManager;
}

bool Enemy::Initialize(Utilities* utilities)
{
	Model3D::Initialize(utilities);

	return false;
}

bool Enemy::BeginRun()
{
	Model3D::BeginRun();


	return false;
}

void Enemy::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

	if (!Player->GameOver && !IsSoundPlaying(OnSound)) PlaySound(OnSound);
}

void Enemy::Draw3D()
{
	Model3D::Draw3D();
}

void Enemy::CheckShotsHitPlayer()
{
	for (const auto shot : Shots)
	{
		if (!shot->Enabled) continue;

		if (shot->CirclesIntersect(*Player))
		{
			Player->Hit(shot->Position, shot->Velocity);
			shot->Destroy();
			break;
		}
	}
}

void Enemy::Spawn()
{
	if (!Player->GameOver) PlaySound(SpawnSound);

	Vector3 position = { 0.0f, 0.0f, 0.0f };


	Spawn(position);
}

void Enemy::Spawn(Vector3 position)
{
	Entity::Spawn(position);

	Managers.EM.ResetTimer(ShotTimerID, GetRandomFloat(0.75f, 1.5f));
}

void Enemy::Hit()
{
	Entity::Hit();

	if (!Player->GameOver) PlaySound(ExplodeSound);

	if (Particles != nullptr) Particles->SpawnLineParticles(Position,
		Vector3Multiply(Velocity, {0.25f}),
		20, 100, 20, 2.0f, WHITE);

	Destroy();
}

void Enemy::Reset()
{
	for (auto& shot : Shots)
	{
		shot->Destroy();
	}

	Velocity = { 0.0f, 0.0f, 0.0f };
	RotationVelocityZ = 0.0f;

	Destroy();
}

void Enemy::Destroy()
{
	Entity::Destroy();

}

void Enemy::Shoot()
{
	PlaySound(FireSound);

	Managers.EM.ResetTimer(ShotTimerID);

	bool spawnNew = true;
	size_t spawnNumber = Shots.size();

	for (size_t check = 0; check < spawnNumber; check++)
	{
		if (!Shots[check]->Enabled)
		{
			spawnNew = false;
			spawnNumber = check;
			break;
		}
	}

	if (spawnNew)
	{
		Shots.push_back(DBG_NEW Shot());
		Managers.EM.AddModel3D(Shots[spawnNumber], ShotModel);
		Shots[spawnNumber]->BeginRun();
	}

	Shots[spawnNumber]->Spawn(Position);
}

void Enemy::Shoot(Vector3 velocity)
{
	Managers.EM.ResetTimer(ShotTimerID);

	bool spawnNew = true;
	size_t spawnNumber = Shots.size();

	for (size_t check = 0; check < spawnNumber; check++)
	{
		if (!Shots[check]->Enabled)
		{
			spawnNew = false;
			spawnNumber = check;
			break;
		}
	}

	if (spawnNew)
	{
		Shots.push_back(DBG_NEW Shot());
		Managers.EM.AddModel3D(Shots[spawnNumber], ShotModel);
		Shots[spawnNumber]->BeginRun();
	}

	Shots[spawnNumber]->Spawn(Position, velocity, ShotLifeTime);
}

void Enemy::ChasePlayer()
{
	RotationVelocityZ = 0.0f;

	Vector3 target = Player->Position;

	SetRotationZFromVector(target);
}

bool Enemy::CheckCollisions()
{
	for (const auto& shot : Player->Shots)
	{
		if (shot->CirclesIntersect(*this))
		{
			shot->Destroy();
			Hit();

			if (Player->GameOver) return true;

			Player->ScoreUpdate(Points);

			return true;
		}
	}

	if (!Player->GetBeenHit())
	{
		if (CirclesIntersect(*Player))
		{

			Hit();
			Player->ScoreUpdate(Points);

			Player->Hit(Position, Velocity);

			return true;
		}
	}

	return false;
}