#include "Zombie.h"

Zombie::Zombie()
{
}

Zombie::~Zombie()
{
}

void Zombie::SetWalls(std::vector<Entity*> walls)
{
	Walls = walls;
}

bool Zombie::Initialize(Utilities* utilities)
{
	Model3D::Initialize(TheUtilities);

	return false;
}

bool Zombie::BeginRun()
{
	Model3D::BeginRun();

	LookAhead.Radius = Radius;

	return false;
}

void Zombie::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

	if (Dead)
	{
		Velocity = { 0.0f, 0.0f, 0.0f };
		return;
	}

	CheckHit();
	CheckPlayerHit();

	if (MoveToWaypoint && !HitPlayer) MoveForward(deltaTime);
	else CalculateDestinationWaypoint(deltaTime);
}

void Zombie::Draw3D()
{
	Model3D::Draw3D();
}

void Zombie::Spawn()
{
	Dead = false;
	MoveToWaypoint = false;
	HitWall = false;
	GoingAfterPlayer = true;

	Speed = 60.666f;

	float width = (float)FieldSize.x / 2.5f;
	float height = (float)FieldSize.y / 1.75f;

	Vector3 position = { 0.0f, 0.0f, 0.0f };

	if (GetRandomValue(0, 10) > 5)
	{
		position.x = GetRandomFloat(-width, -width / 2.0f);
	}
	else
	{
		position.x = GetRandomFloat(width / 2.0f, width);
	}

	if (GetRandomValue(0, 10) > 5)
	{
		position.y = GetRandomFloat(-height, -height / 2.0f);
	}
	else
	{
		position.y = GetRandomFloat(height / 2.0f, height);
	}

	position.y = GetRandomFloat(height / 1.1f, height);

	Spawn(position);
}

void Zombie::Spawn(Vector3 position)
{
	Entity::Spawn(position);

}

void Zombie::Destroy()
{
	Entity::Destroy();

}

void Zombie::MoveForward(float deltaTime)
{
	if (CirclesIntersect(DestinationWaypoint, 10.0f))
	{
		MoveToWaypoint = false;
		GoingAfterPlayer = true;
		return;
	}

	for (const auto& wall : Walls)
	{
		if (SquaresIntersect(*wall))
		{
			MoveToWaypoint = false;
			GoingAfterPlayer = false;
			HitWall = true;
			Velocity = { 0.0f, 0.0f, 0.0f };
			Position = LastFramePosition;
			return;
		}
	}

	SetRotationZFromVector(DestinationWaypoint);

	Velocity = GetVelocityFromAngleZ(RotationZ, Speed);
}

void Zombie::CalculateDestinationWaypoint(float deltaTime)
{
	if (HitWall)
	{
		if (GetRandomValue(0, 10) > 5)
		{
			RotationZ += HalfPi / 2.0f;
		}
		else
		{
			RotationZ -= HalfPi / 2.0f;
		}

		MoveToWaypoint = true;
		HitWall = false;
		DestinationWaypoint = Position + GetVelocityFromAngleZ(RotationZ, 400.0f);
		return;
	}

	if (GoingAfterPlayer)
	{
		ChasePlayer();

		MoveToWaypoint = true;
		DestinationWaypoint = Position + GetVelocityFromAngleZ(RotationZ, 500.0f);
	}

}

void Zombie::CheckHit()
{
	if (CirclesIntersect(Player->Crowbar->GetWorldPosition(), Player->Crowbar->Radius))
	{
		if (Player->Crowbar->Swinging)
		{
			Hit();
			Health -= Player->Crowbar->Damage;
			Player->Crowbar->Hit();
		}
	}
}

void Zombie::CheckPlayerHit()
{
	if (CheckCollisions())
	{
		MoveToWaypoint = false;
		GoingAfterPlayer = false;
		HitPlayer = true;
		Velocity = { 0.0f, 0.0f, 0.0f };
	}
	else if (HitPlayer)
	{
		HitPlayer = false;
		MoveToWaypoint = true;
	}
}
