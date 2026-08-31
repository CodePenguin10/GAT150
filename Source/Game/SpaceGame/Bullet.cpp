#include "Bullet.h"
#include "Math/MathUtility.h"
#include "Components/PhysicsComponent.h"
#include "Engine.h"

FACTORY_REGISTER(Bullet)

void Bullet::Update(float dt)
{
	nu::PhysicsComponent* physicsComponent = GetComponent<nu::PhysicsComponent>();
	if (physicsComponent)
	{
		nu::Vector2 forward{ 1, 0 }; // ->
		nu::Vector2 force = forward.Rotate(m_transform.rotation * nu::DegToRad) * m_speed;
		physicsComponent->SetVelocity(force);

		nu::Vector2 position = physicsComponent->GetPosition();
		position.x = nu::Wrap(0.0f, 1280.0f, position.x);
		position.y = nu::Wrap(0.0f, 1024.0f, position.y);
		physicsComponent->SetPosition(position);
	}

	Actor::Update(dt);
}

void Bullet::Read(const nu::json::value_t& value)
{
	Actor::Read(value);

	JSON_READ_NAME(value, "speed", m_speed);
}