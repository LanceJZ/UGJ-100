#pragma once
#include "Globals.h"
#include "ThePlayer.h"
#include "Shot.h"
#include "ParticleManager.h"

class Enemy : public Model3D
{
public:
	Enemy();
	virtual ~Enemy();

	bool Dead = false;
	int Health = 10;
	float ShotTimerAmount = 0.0f;

	std::vector<Shot*> Shots;

	void SetPlayer(ThePlayer* player);
	void SetParticleManager(ParticleManager* particleManager);

	void SetShotModel(Model model);

	void SetFireSound(Sound fireSound);
	void SetExplodeSound(Sound explodeSound);

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void Update(float deltaTime);
	void Draw3D();

	virtual void CheckShotsHitPlayer();

	virtual void Spawn();
	virtual void Spawn(Vector3 position);
	virtual void Destroy();
	virtual void Hit();
	virtual void Reset();

protected:
	size_t ShotTimerID = 0;

	int Points = 0;
	int Damage = 10;
	float Speed = 200.0f;
	float TurnSpeed = 1.45f;
	float RotateMagnitude = PI / 2;
	float ShotLifeTime = 0.0f;

	ThePlayer* Player = nullptr;
	ParticleManager* Particles = nullptr;
	Sound AttackSound = {};
	Sound HitSound = {};
	Sound OnSound = {};
	Sound SpawnSound = {};

	Model ShotModel = {};

	virtual void Shoot();
	virtual void Shoot(Vector3 velocity);
	virtual void ChasePlayer();
	virtual bool CheckCollisions();

private:
};