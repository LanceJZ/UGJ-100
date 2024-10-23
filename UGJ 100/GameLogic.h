#pragma once
#include "Globals.h"
#include "Common.h"
#include "Utilities.h"
#include "ThePlayer.h"
#include "EnemyControl.h"
#include "ParticleManager.h"
#include "TheBackground.h"

enum GameState
{
	PlayerHit,
	Over,
	InPlay,
	Pause,
	HighScores,
	MainMenu
};

class GameLogic : public Common
{
public:
	GameLogic();
	virtual ~GameLogic();

	GameState State = MainMenu;

	void SetPlayer(ThePlayer *player);
	void SetEnemies(EnemyControl *enemies);
	void SetParticles(ParticleManager *particles);
	void SetBackground(TheBackground *background);

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	bool Load();

	void FixedUpdate();

private:

	ThePlayer *Player = nullptr;
	EnemyControl *Enemies = nullptr;
	ParticleManager *Particles = nullptr;
	TheBackground *Background = nullptr;

	void MoveCamera();
	void DoesPlayerMove();
};

