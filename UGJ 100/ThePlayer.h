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
	int MaxHP { 100 };

	std::vector<Shot*> Shots = {};
	TheCrowbar* Crowbar = nullptr;

	void SetParticleManager(ParticleManager* particleManager);
	void SetWalls(std::vector<Entity*> walls);
	void SetCrowbarModel(Model crowbarModel);
	void SetCubeModel(Model cubeModel);

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void Input();
	void Update(float deltaTime);
	void Draw3D();

	void Hit();
	void Hit(float damage);
	void Hit(Vector3 location, Vector3 velocity);
	void ScoreUpdate(int addToScore);
	void Reset();
	void NewGame();

private:
	bool MoveForwardPressed = false;

	size_t HitTimerID = 0;

	int NextNewLifeScore = 10000;

	Model CubeModel = {};
	ParticleManager* Particles = {};
	std::vector<Entity*> Walls = {};
	Model3D* HealthBar = nullptr;
	Model3D* HealthBarBackground = nullptr;

	void Dead();
	void Gamepad();
	void Keyboard();
	void MoveForward(float deltaTime);
	void UseWeapon();
};
