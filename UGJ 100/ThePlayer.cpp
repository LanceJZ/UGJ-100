#include "ThePlayer.h"

ThePlayer::ThePlayer()
{
	Managers.EM.AddModel3D(Crowbar = DBG_NEW TheCrowbar);
	Managers.EM.AddModel3D(HealthBar = DBG_NEW Model3D);
	Managers.EM.AddModel3D(HealthBarBackground = DBG_NEW Model3D);

	HitTimerID = Managers.EM.AddTimer();
}

ThePlayer::~ThePlayer()
{
}

void ThePlayer::SetParticleManager(ParticleManager* particleManager)
{
	Particles = particleManager;
}

void ThePlayer::SetWalls(std::vector<Entity*> walls)
{
	Walls = walls;
}

void ThePlayer::SetCrowbarModel(Model crowbarModel)
{
	Crowbar->SetModel(crowbarModel);
}

void ThePlayer::SetCubeModel(Model cubeModel)
{
	CubeModel = cubeModel;
}

bool ThePlayer::Initialize(Utilities* utilities)
{
	Model3D::Initialize(utilities);

	Enabled = false;
	Crowbar->Enabled = false;
	HealthBar->Enabled = false;
	HealthBarBackground->Enabled = false;

	return false;
}

bool ThePlayer::BeginRun()
{
	Model3D::BeginRun();

	HealthBar->SetModel(CubeModel);
	HealthBarBackground->SetModel(CubeModel);

	Crowbar->SetParent(*this);
	Crowbar->Position = { 15.0f, 7.0f, 0 };

	float barY = -30.0f;
	HealthBar->SetParent(*this);
	HealthBar->Position = { 0.0f, barY, 0.0f };
	HealthBar->ModelColor = { 130, 6, 6, 255 };
	HealthBar->Scale = { 20.0f, 4.0f, 1.0f }; // 20 is for debugging.
	HealthBar->IgnoreParentRotation = true;

	HealthBarBackground->SetParent(*this);
	HealthBarBackground->Position = { 0.0f, barY, 1.0f };
	HealthBarBackground->ModelColor = { 90, 90, 90, 255 };
	HealthBarBackground->Scale = { 50.0f, 4.0f, 1.0f };
	HealthBarBackground->IgnoreParentRotation = true;

	Managers.EM.SetTimer(HitTimerID, 0.5f);

	return false;
}

void ThePlayer::Input()
{
	Model3D::Input();

	Keyboard();

	if (IsGamepadAvailable(0))
	{
		Gamepad();
	}
}

void ThePlayer::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

	if (MoveForwardPressed)
	{
		MoveForward(deltaTime);
	}
	else
	{
		Velocity = { 0.0f, 0.0f, 0.0f };
	}

	if (GetBeenHit())
	{
		if (Managers.EM.TimerElapsed(HitTimerID)) ResetBeenHit();
	}
}

void ThePlayer::Draw3D()
{
	Model3D::Draw3D();

}

void ThePlayer::Hit()
{
	Entity::Hit();

	Acceleration = { 0 };
	Velocity = { 0 };

	Managers.EM.ResetTimer(HitTimerID);
}

void ThePlayer::Hit(float damage)
{
	Hit();

	HP -= damage;

	HealthBar->Scale = { 50.0f * HP / MaxHP, 4.0f, 1.0f };

	if (HP <= 0)
	{
		Dead();
	}
}

void ThePlayer::Hit(Vector3 location, Vector3 velocity)
{
	Entity::Hit();

}

void ThePlayer::ScoreUpdate(int addToScore)
{
	Score += addToScore;

	if (Score > HighScore)
	{
		HighScore = Score;
	}

}

void ThePlayer::Reset()
{
	Position = { 0, 0, 0 };
	Velocity = { 0, 0, 0 };
	Enabled = true;
	Crowbar->Enabled = true;
	HealthBar->Enabled = true;
	HealthBarBackground->Enabled = true;
	HealthBar->Scale = { 50.0f, 4.0f, 1.0f };
}

void ThePlayer::NewGame()
{
	HP = MaxHP;
	Lives = 2;
	Score = 0;
	GameOver = false;
	Reset();
}

void ThePlayer::Dead()
{
}

void ThePlayer::Gamepad()
{
	//Button B is 6 for Shield //Button A is 7 for Fire //Button Y is 8 for Hyperspace
	//Button X is 5	//Left bumper is 9 //Right bumper is 11 for Shield //Left Trigger is 10
	//Right Trigger is 12 for Thrust //Dpad Up is 1 for	//Dpad Down is 3 for
	//Dpad Left is 4 for rotate left //Dpad Right is 2 for rotate right
	//Axis 1 is -1 for , 1 for  on left stick.
	//Axis 0 is -1 for Left, 1 for right on left stick.

	if (IsGamepadButtonDown(0, 12))
	{
	}
	else
	{
	}

	if (IsGamepadButtonDown(0, 4) || GetGamepadAxisMovement(0, 0) < -0.25f)
	{
	}
	else if (IsGamepadButtonDown(0, 2) || GetGamepadAxisMovement(0, 0) > 0.25f)
	{
	}

	if (IsGamepadButtonPressed(0, 7))
	{
	}

	if (IsGamepadButtonDown(0, 11) || IsGamepadButtonDown(0, 6))
	{
	}
	else
	{
	}
}

void ThePlayer::Keyboard()
{
	float adjustment = 3.0f;

	if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D))
	{
		RotationZ += HalfPi / adjustment;
	}
	else if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A))
	{
		RotationZ -= HalfPi / adjustment;
	}
	else
	{
	}

	if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
	{
		MoveForwardPressed = true;
	}
	else
	{
		MoveForwardPressed = false;
		Velocity = { 0.0f, 0.0f, 0.0f };
	}

	if (IsKeyPressed(KEY_RIGHT_CONTROL) || IsKeyPressed(KEY_LEFT_CONTROL) ||
		IsKeyPressed(KEY_SPACE))
	{
	}

	if (IsKeyDown(KEY_DOWN))
	{
	}
	else
	{
	}

	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		UseWeapon();
	}
}

void ThePlayer::MoveForward(float deltaTime)
{
	float adjustment = 4.01f;

	if (Y() > FieldSize.y / 2.1f)
	{
		Position.y = LastFramePosition.y;
		Velocity.y = 0.0f;
		return;
	}

	if (X() < FieldSize.x / adjustment && X() > -(FieldSize.x / adjustment))
	{
		TheCamera.position.x = Position.x;
		TheCamera.target.x = TheCamera.position.x;
	}
	else
	{
	}

	if (Y() > -(FieldSize.y / adjustment))
	{
		TheCamera.position.y = Position.y;
		TheCamera.target.y = TheCamera.position.y;
	}
	else
	{
	}

	bool clear = true;

	for (const auto& wall : Walls)
	{
		if (SquaresIntersect(*wall))
		{
			clear = false;

			break;
		}
	}

	if (clear) Velocity = GetVelocityFromAngleZ(RotationZ, 100.0f);
	else
	{
		Position = LastFramePosition;
		Velocity = { 0.0f, 0.0f, 0.0f };
	}
}

void ThePlayer::UseWeapon()
{
	Crowbar->Swing();
}
