#include "GameLogic.h"

GameLogic::GameLogic()
{

}

GameLogic::~GameLogic()
{
}

void GameLogic::SetPlayer(ThePlayer* player)
{
	Player = player;
}

void GameLogic::SetEnemies(EnemyControl* enemies)
{
	Enemies = enemies;
}

void GameLogic::SetParticles(ParticleManager* particles)
{
	Particles = particles;
}

void GameLogic::SetBackground(TheBackground* background)
{
	Background = background;
}

bool GameLogic::Initialize(Utilities* utilities)
{
	Common::Initialize(utilities);

	return false;
}

bool GameLogic::BeginRun()
{

	return false;
}

bool GameLogic::Load()
{

	return false;
}

void GameLogic::FixedUpdate()
{
	Common::FixedUpdate();

	MoveCamera();
}

void GameLogic::MoveCamera()
{
	float cameraMoveX = GetScreenWidth() / 3.0f;
	float cameraMoveY = GetScreenHeight() / 3.5f;

	if (Player->X() > cameraMoveX)
	{
		TheCamera.position.x = cameraMoveX;
		TheCamera.target.x = cameraMoveX;
	}
	else if (Player->X() < -cameraMoveX)
	{
		TheCamera.position.x = -cameraMoveX;
		TheCamera.target.x = -cameraMoveX;
	}
	else
	{
		TheCamera.position.x = 0.0f;
		TheCamera.target.x = 0.0f;
	}

	if (Player->Y() > cameraMoveY)
	{
		TheCamera.position.y = cameraMoveY;
		TheCamera.target.y = cameraMoveY;
	}
	else if (Player->Y() < -cameraMoveY)
	{
		TheCamera.position.y = -cameraMoveY;
		TheCamera.target.y = -cameraMoveY;
	}
	else
	{
		TheCamera.position.y = 0.0f;
		TheCamera.target.y = 0.0f;
	}
}
