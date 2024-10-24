#include "TheCrowbar.h"

TheCrowbar::TheCrowbar()
{
}

TheCrowbar::~TheCrowbar()
{
}

bool TheCrowbar::Initialize(Utilities* utilities)
{
	Model3D::Initialize(TheUtilities);

	Radius *= 4.0f;

	return false;
}

bool TheCrowbar::BeginRun()
{
	Model3D::BeginRun();

	return false;
}

void TheCrowbar::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

	if (Swinging) DoTheSwing();
}

void TheCrowbar::Draw3D()
{
	Model3D::Draw3D();
}

void TheCrowbar::Spawn(Vector3 position)
{
	Entity::Spawn(position);

}

void TheCrowbar::Destroy()
{
	Entity::Destroy();

}

void TheCrowbar::Swing()
{
	Swinging = true;
	RotationZ = HalfPi / 1.25f;
	RotationVelocityZ = -10.0f;
}

void TheCrowbar::Hit()
{
	RotationZ = 0.0f;
	RotationVelocityZ = 0.0f;
	Swinging = false;
}

void TheCrowbar::DoTheSwing()
{
	if (RotationZ > HalfPi)
	{
		Hit();
	}
}