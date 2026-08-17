#include "Player.h"
#include "Bullet.h"
#include "Assets.h"
#include "Engine.h"
#include "Renderer.h"
#include "SpaceGame.h"

FACTORY_REGISTER(Player)

using namespace nu;

void Player::Update(float dt)
{
	float thrust = 0.0f;

	if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = m_speed;
	if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -m_speed;

	float rotate = 0.0f;
	if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -180.0f;
    if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +180.0f;

	SetRotation(m_transform.rotation + rotate * dt);

	nu::Vector2 velocity{ 1, 0 };
	velocity = velocity.Rotate(m_transform.rotation * DegToRad) * thrust;
	AddVelocity(velocity * dt);

	//particle system
	nu::Particle particle;

	nu::Vector2 offset{ -20.0f, 0.0f };
	offset = offset.Rotate(m_transform.rotation * nu::DegToRad);

	particle.position = m_transform.position + offset;
	particle.color = { 1.0f, 1.0f, 0.0f };
	particle.lifespan = nu::RandomFloat(0.5f, 1.5f);
	particle.velocity = nu::Vector2{ nu::RandomFloat(-30.0f, -100.0f), 0.0f}.Rotate((m_transform.rotation + nu::RandomInt(-10, 10)) * nu::DegToRad);

	nu::Engine::Get().GetPS().AddParticle(particle);

	//fire
	m_fireTimer -= dt;
	if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_SPACE) && m_fireTimer <= 0)
	{
		m_fireTimer = 0.15f;
		BulletDesc Desc;
		Desc.name = "Bullet";
		Desc.tag = "Friendly_Bullet";
		Desc.texture = Resources().Get<Texture>("assets/textures/Bullet.png", Engine::Get().GetRenderer());
		Desc.transform = m_transform;
		Desc.transform.scale = 2.0f;
		Desc.speed = 1500.0f;
		Desc.lifespan = 1.5f;

		m_scene->AddActor(std::move(std::make_unique<Bullet>(Desc)));
	}

	//Bullet Time
	if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_LSHIFT))
	{
		nu::Engine::Get().GetTime().SetTimeScale(0.5f);
	}
	else
	{
		nu::Engine::Get().GetTime().SetTimeScale(1.0f);
	}

	Actor::Update(dt);
}

void Player::OnCollision(Actor* other)
{
	if (other->GetTag() == "Enemy" || other->GetTag() == "Enemy2" || other->GetTag() == "Enemy3")
	{
		SetDestroyed();
		((SpaceGame*)m_scene->GetGame())->OnPlayerDeath();
	}
}
