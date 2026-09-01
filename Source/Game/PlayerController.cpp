#include "pch.h"
#include "PlayerController.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteAnimationRendererComponent.h"
#include "Engine.h"

using namespace nu;

void PlayerController::Start()
{
	Actor::Start();

	m_physicsComponent = GetComponent<PhysicsComponent>();
	assert(m_physicsComponent);
	m_rendererComponent = GetComponent<SpriteAnimationRendererComponent>();
	assert(m_rendererComponent);
}

void PlayerController::Update(float dt)
{
	float dir = 0.0f;
	if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) dir = -1.0f;
	if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) dir = 1.0f;

	Vector2 velocity = m_physicsComponent->GetVelocity();
	if (dir != 0)
	{
		velocity.x = dir * 1000;
	}

	m_physicsComponent->SetVelocity(velocity);

	Actor::Update(dt);
}

void PlayerController::OnCollision(Actor* other)
{

}

void PlayerController::Read(const nu::json::value_t& value)
{

}
