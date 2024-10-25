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

void EnemyControl::SetShotModel(Model model)
{
	ShotModel = model;
}

void EnemyControl::SetZombieModel(Model zombieModel)
{
	ZombieModel = zombieModel;
}

void EnemyControl::SetWalls(std::vector<Entity*> walls)
{
	Walls = walls;
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

	SpawnZombies(10);
}


void EnemyControl::Reset()
{
	for (auto& zombie : Zombies)
	{
		zombie->Reset();
		zombie->SetWalls(Walls);
	}
}

void EnemyControl::SpawnZombies(int count)
{
	for (int i = 0; i < count; i++)
	{
		bool spawnNew = true;
		size_t spawnNumber = Zombies.size();

		for (size_t check = 0; check < spawnNumber; check++)
		{
			if (!Zombies.at(check)->Enabled)
			{
				spawnNew = false;
				spawnNumber = check;
				break;
			}
		}


		if (spawnNew)
		{
			Zombies.push_back(DBG_NEW Zombie());
			Managers.EM.AddModel3D(Zombies.at(spawnNumber), ZombieModel);
			Zombies.at(spawnNumber)->Initialize(TheUtilities);
			Zombies.at(spawnNumber)->SetPlayer(Player);
			Zombies.at(spawnNumber)->BeginRun();
		}

		Zombies.at(spawnNumber)->SetWalls(Walls);
		Zombies.at(spawnNumber)->Spawn();
	}
}