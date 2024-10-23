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

	return false;
}

void Zombie::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

}

void Zombie::Draw3D()
{
	Model3D::Draw3D();
}

void Zombie::Spawn()
{
	float width = (float)FieldSize.y;
	float height = (float)FieldSize.x;

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

	Spawn({ position });
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

}
