#pragma once
#include "Globals.h"
#include "ThePlayer.h"
#include "ParticleManager.h"
#include "Zombie.h"

class EnemyControl : public Common
{
public:
	EnemyControl();
	virtual ~EnemyControl();

	std::vector<Zombie*> Zombies;

	void SetPlayer(ThePlayer* player);
	void SetParticleManager(ParticleManager* particles);
	void SetZombieModel(Model zombieModel);
	void SetWalls(std::vector<Entity*> walls);

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void FixedUpdate();

	void Reset();
	void NewGame();

private:
	Model ZombieModel = {};

	std::vector<Entity*> Walls;

	ThePlayer *Player = nullptr;
	ParticleManager *Particles = nullptr;

	void SpawnZombies(int count);
};