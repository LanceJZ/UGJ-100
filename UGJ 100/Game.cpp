#include "Game.h"

Game::Game()
{
	Managers.EM.AddCommon(Logic = DBG_NEW GameLogic());
	Managers.EM.AddLineModel(Player = DBG_NEW ThePlayer());
	Managers.EM.AddCommon(Enemies = DBG_NEW EnemyControl());
	Managers.EM.AddCommon(Particles = DBG_NEW ParticleManager());

	Managers.EM.AddCommon(Background = DBG_NEW TheBackground());
}

Game::~Game()
{
}

bool Game::Initialize(Utilities* utilities) //Initialize
{
	Common::Initialize(utilities);

	SetTargetFPS(120);
	SetWindowTitle("UGJ 100 Pre Alpha");
	float multi = 2.0f;
	FieldSize = { GetScreenWidth() * multi, GetScreenHeight() * multi };

	Logic->SetPlayer(Player);
	Logic->SetEnemies(Enemies);
	Logic->SetBackground(Background);
	Logic->SetParticles(Particles);

	//Any Entities added after this point need this method fired manually.

	return true;
}

bool Game::Load()
{
	Particles->Load();

	//Models
	Player->SetModel(Managers.CM.LoadAndGetModel("Player"));
	Background->SetFloorModel(Managers.CM.LoadAndGetModel("Floor64"));
	Background->SetWallModel(Managers.CM.LoadAndGetModel("Wall64"));
	Enemies->SetZombieModel(Managers.CM.LoadAndGetModel("Zombie"));

	return true;
}

bool Game::BeginRun()
{
	//Any Entities added after this point need this method fired manually.
	Particles->SetManagers(Managers);
	Player->SetParticleManager(Particles);
	Enemies->SetParticleManager(Particles);
	Enemies->SetPlayer(Player);

	return true;
}

void Game::ProcessInput()
{
	GameInput();
}


void Game::Update(float deltaTime)
{
	if (Logic->State == Pause)
		return;

}

void Game::FixedUpdate(float deltaTime)
{
	if (Logic->State == Pause)
		return;

}

void Game::NewGame()
{
	Logic->State = InPlay;

	Player->Reset();
	Player->SetWalls(Background->Walls);

	Enemies->Reset();
	Enemies->SetWalls(Background->Walls);
	Enemies->NewGame();
}

void Game::Draw3D() const
{

#ifdef _DEBUG
	int fsx = int(FieldSize.x * 0.5f);
	int fsy = int(FieldSize.y * 0.5f);

	DrawLine(-fsx, -fsy, fsx, -fsy, { DARKBLUE }); //Top
	DrawLine(fsx, -fsy, fsx, fsy, { DARKBLUE }); //Right side.
	DrawLine(fsx, fsy - 1, -fsx, fsy - 1, { DARKBLUE }); //Bottom.
	DrawLine(-fsx + 1, fsy - 1, -fsx + 1, -fsy - 1, { DARKBLUE }); //Left side.
#endif
}

void Game::Draw2D() const
{

}

void Game::GameInput()
{
	if (Logic->State == MainMenu)
	{
		if (IsGamepadAvailable(0))
		{
			if (IsGamepadButtonPressed(0, 15))//Start button
			{
				NewGame();
			}
		}

		if (IsKeyPressed(KEY_N))
		{
			NewGame();
		}

		if (IsKeyPressed(KEY_D))
		{

		}
	}

	if (Logic->State == InPlay)
	{
		if (IsGamepadAvailable(0))
		{
			if (IsGamepadButtonPressed(0, 13)) //Menu Button
			{
				Logic->State = Pause;
			}

			if (IsGamepadButtonPressed(0, 8)) //X button
			{
				PlayBackgroundMusic = !PlayBackgroundMusic;
			}
		}

		if (IsKeyPressed(KEY_M))
		{
			PlayBackgroundMusic = !PlayBackgroundMusic;
		}


		if (IsKeyPressed(KEY_P))
		{
			Logic->State = Pause;
		}
	}
	else if (Logic->State == Pause)
	{
		if (IsKeyPressed(KEY_P))
		{
			Logic->State = InPlay;
		}

		if (IsGamepadAvailable(0))
		{
			if (IsGamepadButtonPressed(0, 13)) //Menu Button
			{
				Logic->State = InPlay;
			}
		}
	}
}