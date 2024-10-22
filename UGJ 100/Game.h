#pragma once
#include <memory>
#include "Globals.h"
#include "Utilities.h"
#include "GameLogic.h"
#include "EnemyControl.h"
#include "ParticleManager.h"
#include "ThePlayer.h"
#include "TheBackground.h"

class Game : Common
{
public:
	Game();
	virtual ~Game();

	bool PlayBackgroundMusic = true;

	GameLogic* Logic = {};

	bool Initialize(Utilities* utilities);
	bool Load();
	bool BeginRun();
	void ProcessInput();
	void Update(float deltaTime);
	void FixedUpdate(float deltaTime);
	void Draw3D() const;
	void Draw2D() const;

private:
	int Roll = 0;
	float Rollf = 0;

	//When adding classes to EM, must be heap pointer.
	ThePlayer* Player = {};
	EnemyControl* Enemies = {};
	ParticleManager* Particles = {};
	TheBackground* Background = {};

	void GameInput();
	void NewGame();
};

