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
	DoesPlayerMove();
}

void GameLogic::MoveCamera()
{


	//float cameraMoveX = GetScreenWidth() / 5.0f;
	//float cameraMoveY = GetScreenHeight() / 5.0f;

	//if (Player->X() > cameraMoveX)
	//{
	//	TheCamera.position.x = Player->Position.x;
	//	TheCamera.target.x = TheCamera.position.x;
	//}
	//else if (Player->X() < -cameraMoveX)
	//{
	//	TheCamera.position.x = Player->Position.x;
	//	TheCamera.target.x = TheCamera.position.x;
	//}
	//else
	//{
	//	TheCamera.position.x = 0.0f;
	//	TheCamera.target.x = 0.0f;
	//}

	//if (Player->Y() > cameraMoveY)
	//{
	//	TheCamera.position.y = Player->Position.y;
	//	TheCamera.target.y = TheCamera.position.y;
	//}
	//else if (Player->Y() < -cameraMoveY)
	//{
	//	TheCamera.position.y = Player->Position.y;
	//	TheCamera.target.y = TheCamera.position.y;
	//}
	//else
	//{
	//	TheCamera.position.y = 0.0f;
	//	TheCamera.target.y = 0.0f;
	//}
}

void GameLogic::DoesPlayerMove()
{
}
