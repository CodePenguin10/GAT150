#pragma once
#include "Framework/Actor.h"

struct PlayerDesc : public nu::ActorDesc
{
    float speed;
};

class Player : public nu::Actor
{
public:
    Player() = default;
    Player(const PlayerDesc& playerDesc) : Actor{ playerDesc }, m_speed{ playerDesc.speed } {}

    CLASS_PROTOTYPE(Player)

        void Update(float dt) override;
    void OnCollision(Actor* other) override;

    void Read(const nu::json::value_t& value) override;

    float GetSpeed() const { return m_speed; }

private:
    int ammo = 0;
    float m_speed = 1000.0f;
    float m_fireTimer = 0.0f;
};