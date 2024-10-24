#include "ThePlayer.h"

ThePlayer::ThePlayer()
{
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

bool ThePlayer::Initialize(Utilities* utilities)
{
	Model3D::Initialize(utilities);

	Enabled = false;

	return false;
}

bool ThePlayer::BeginRun()
{
	Model3D::BeginRun();

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
}

void ThePlayer::Draw3D()
{
	Model3D::Draw3D();

}

void ThePlayer::Hit()
{
	Acceleration = { 0 };
	Velocity = { 0 };
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
}

void ThePlayer::NewGame()
{
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

	if (IsKeyPressed(KEY_RIGHT))
	{
		RotationZ += HalfPi / adjustment;
	}
	else if (IsKeyPressed(KEY_LEFT))
	{
		RotationZ -= HalfPi / adjustment;
	}
	else
	{
	}

	if (IsKeyPressed(KEY_SPACE))
	{
		Position = { 0, 0, 0 };
		Velocity = { 0, 0, 0 };
	}

	if (IsKeyDown(KEY_UP))
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
}

void ThePlayer::MoveForward(float deltaTime)
{
	if (Y() > FieldSize.y / 4.0f)
	{
		Position.y = LastFramePosition.y;
		Velocity.y = 0.0f;
		return;
	}

	if (X() < FieldSize.x / 4.0f && X() > -(FieldSize.x / 4.0f))
	{
		TheCamera.position.x = Position.x;
		TheCamera.target.x = TheCamera.position.x;
	}
	else
	{
	}

	if (Y() > -(FieldSize.y / 4.0f))
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
