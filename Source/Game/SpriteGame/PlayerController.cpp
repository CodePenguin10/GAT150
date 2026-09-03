#include "PlayerController.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteAnimatorRendererComponent.h"
#include "Core/Factory.h"
#include "Framework/Scene.h"
#include "Damager.h"
#include "Engine.h"

using namespace nu;

FACTORY_REGISTER(PlayerController)

void PlayerController::Start()
{
	CharacterBase::Start();

	m_physicsComponent = GetComponent<PhysicsComponent>();
	assert(m_physicsComponent);
	m_rendererComponent = GetComponent<SpriteAnimatorRendererComponent>();
	assert(m_rendererComponent);
}

void PlayerController::Update(float dt)
{
	Vector2 velocity = m_physicsComponent->GetVelocity();

	switch (m_state)
	{
	case CharacterBase::State::Move:
	{
		float dir = 0.0f;
		if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) dir = -1.0f;
		if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) dir = 1.0f;
		if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE))
		{
			velocity.y = -800.0f;
		}
		if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_RSHIFT))
		{
			

			auto damager = Factory::Instance().Create<Damager>("DamagerPrototype");
			damager->SetDamage(5.0f);
			damager->SetPosition(GetTransform().position + Vector2{ 20.0f, 0.0f});
			damager->SetTag("PlayerDamager");
			m_scene->AddActor(std::move(damager));
			m_state = State::Attack;
		}

		if (dir != 0)
		{
			velocity.x = dir * 100.0f;
			m_rendererComponent->Play("Run");
			m_rendererComponent->SetFlipH(dir < 0);
		}
		else
		{
			m_rendererComponent->Play("Idle");
		}


	}
		break;
	case CharacterBase::State::Attack:
	{
		m_rendererComponent->Play("Attack");
		if (m_rendererComponent->IsAnimationDone())
		{
			m_state = State::Move;
			m_rendererComponent->Play("Idle");
		}
	}
		break;
	case CharacterBase::State::Hit:
		if (m_rendererComponent->IsAnimationDone())
		{
			m_state = State::Move;
			m_rendererComponent->Play("Idle");
		}
		break;
	case CharacterBase::State::Death:
		break;
	default:
		break;
	}


	m_physicsComponent->SetVelocity(velocity);
	Engine::Get().GetRenderer().SetCamera(m_physicsComponent->GetPosition());

	CharacterBase::Update(dt);
}

void PlayerController::OnCollision(Actor* other)
{
	if (other->GetTag() == "EnemyDamager")
	{
		other->SetDestroyed();

		m_state = State::Hit;
		m_rendererComponent->Play("Death");
		Damager* damager = dynamic_cast<Damager*>(other);
		if (damager)
		{
			m_health -= damager->GetDamage();
		}
		else
		{
			m_health -= 1.0f;
		}
		m_health -= 1.0f;
		if (m_health <= 0.0f)
		{
			SetDestroyed();
		}
	}
}

void PlayerController::Read(const nu::json::value_t& value)
{
	CharacterBase::Read(value);
}
