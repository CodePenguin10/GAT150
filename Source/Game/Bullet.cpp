#include "Bullet.h"
#include "Math/MathUtility.h"
#include "Engine.h"

FACTORY_REGISTER(Bullet)

void Bullet::Update(float dt)
{
	nu::Vector2 forward{ 1.0f, 0.0f };
	nu::Vector2 velocity = forward.Rotate(m_transform.rotation * nu::DegToRad) * m_speed;

	SetVelocity(velocity);

	Actor::Update(dt);
}