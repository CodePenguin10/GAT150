#include "FlyingEnemyController.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteAnimatorRendererComponent.h"
#include "Core/Factory.h"
#include "Engine.h"

using namespace nu;

FACTORY_REGISTER(FlyingEnemyController)

void FlyingEnemyController::Start()
{
	Actor::Start();

	m_physicsComponent = GetComponent<PhysicsComponent>();
	assert(m_physicsComponent);
	m_rendererComponent = GetComponent<SpriteAnimatorRendererComponent>();
	assert(m_rendererComponent);
}

void FlyingEnemyController::Update(float dt)
{
	Vector2 velocity = m_physicsComponent->GetVelocity();

	auto player = m_scene->GetActorByName<Actor>("PlayerPrototype");
	if (player)
	{
		Vector2 position = GetTransform().position;
		Vector2 playerPosition = player->GetTransform().position;

		Vector2 direction = playerPosition - position;

		m_physicsComponent->ApplyForce(direction.Normalized() * 500.0f);
	}


	Actor::Update(dt);
}

void FlyingEnemyController::OnCollision(Actor* other)
{

}

void FlyingEnemyController::Read(const nu::json::value_t& value)
{
	Actor::Read(value);
}
