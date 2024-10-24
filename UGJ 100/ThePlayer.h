#pragma once
#include "Globals.h"
#include "Model3D.h"
#include "ParticleManager.h"
#include "Shot.h"
#include "TheCrowbar.h"

class ThePlayer : public Model3D
{
public:
	ThePlayer();
	virtual ~ThePlayer();

	bool GameOver = false;

	int Score { 0 };
	int HighScore { 0 };
	int Lives { 0 };
	int HP { 100 };

	std::vector<Shot*> Shots = {};
	TheCrowbar* Crowbar = nullptr;

	void SetParticleManager(ParticleManager* particleManager);
	void SetWalls(std::vector<Entity*> walls);
	void SetCrowbarModel(Model crowbarModel);

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void Input();
	void Update(float deltaTime);
	void Draw3D();

	void Hit();
	void Hit(Vector3 location, Vector3 velocity);
	void ScoreUpdate(int addToScore);
	void Reset();
	void NewGame();

private:
	bool MoveForwardPressed = false;

	int NextNewLifeScore = 10000;

	ParticleManager* Particles = {};
	std::vector<Entity*> Walls = {};

	void Dead();
	void Gamepad();
	void Keyboard();
	void MoveForward(float deltaTime);
	void UseWeapon();
};
