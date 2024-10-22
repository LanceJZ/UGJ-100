#pragma once
#include "Globals.h"
#include "ThePlayer.h"
#include "ParticleManager.h"

class EnemyControl : public Common
{
public:
	EnemyControl();
	virtual ~EnemyControl();

	void SetPlayer(ThePlayer* player);
	void SetParticleManager(ParticleManager* particles);

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void FixedUpdate();

	void NewGame();

private:

	ThePlayer *Player = nullptr;
	ParticleManager *Particles = nullptr;

	void Reset();
};