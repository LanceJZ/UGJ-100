#pragma once
#include "Globals.h"
#include "Model3D.h"
#include "ParticleManager.h"
#include "Shot.h"

class ThePlayer : public Model3D
{
public:
	ThePlayer();
	virtual ~ThePlayer();

	bool GameOver = false;

	int Score { 0 };
	int HighScore { 0 };
	int Lives { 0 };

	std::vector<Shot*> Shots = {};

	void SetParticleManager(ParticleManager* particleManager);

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
	int NextNewLifeScore = 10000;

	ParticleManager* Particles = {};

	void Dead();
	void Gamepad();
	void Keyboard();
};
