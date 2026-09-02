#include "SpriteGame.h"
#include "Engine.h"

#include <memory>

using namespace nu;

bool SpriteGame::Initialize()
{
	SetWorkingDirectory("SpriteGame");

	Game::Initialize();

	m_scene = std::make_unique<Scene>();
	m_scene->SetGame(this);
	m_scene->Load("data/scene.json");

	m_titleText = new Text(Resources().GetWithID<Font>("title_font", "fonts/Private Teacher.ttf", 128.0f));
	m_titleText->Create(Engine::Get().GetRenderer(), "Some Sprite Game IG", nu::Color{ 1.0f, 1.0f, 1.0f });

	m_scoreText = new Text(Resources().GetWithID<Font>("game_font", "fonts/Private Teacher.ttf", 32.0f));
	m_livesText = new Text(Resources().Get<Font>("game_font", 32.0f));



	return true;
}

void SpriteGame::Update(float dt)
{
	switch (m_gameState)
	{
	case GameState::Title:
		//Draw title
		if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE))
		{
			m_gameState = GameState::StartGame;
		}
		break;
	case GameState::StartGame:
		m_score = 0;
		m_lives = 6;
		m_spawnTimer = 5.0f;
		m_stateTimer = 0.5f;
		m_gameState = GameState::StartLevel;
		break;
	case GameState::StartLevel:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_scene->RemoveAllActors();
			m_scene->Load("data/level.json");
			SpawnPlayer();
			m_gameState = GameState::Game;
		}
		break;
	case GameState::Game:
		// Draw score/lives
		m_spawnTimer -= dt;
		if (m_spawnTimer <= 0.0f)
		{
			m_spawnTimer = nu::RandomFloat(3.0f, 5.0f);
			SpawnEnemy();
		}
		break;
	case GameState::GameOver:
		//Draw GameOver
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_scene->RemoveAllActors();
			m_gameState = GameState::Title;
		}
		break;
	default:
		break;
	}

	Game::Update(dt);
}

void SpriteGame::Draw(class nu::Renderer& renderer)
{
	renderer.EnableCamera(false);

	renderer.DrawTexture(*nu::Resources().Get<Texture>("textures/background.jpg", Engine::Get().GetRenderer()), 500.0f, 500.0f);

	switch (m_gameState)
	{
	case GameState::Title:
		//Draw title
		m_titleText->Draw(renderer, 400.0f, 400.0f);
		break;
	case GameState::StartGame:
	case GameState::StartLevel:
	case GameState::Game:
		// Draw score/lives
		m_scoreText->Create(renderer, "Score: " + std::to_string(m_score), { 1.0f, 1.0f, 1.0f });
		m_scoreText->Draw(renderer, 30.0f, 30.0f);

		m_livesText->Create(renderer, "lives: " + std::to_string(m_lives / 2), { 1.0f, 1.0f, 1.0f });
		m_livesText->Draw(renderer, renderer.GetWidth() - 130.0f, 30.0f);
		break;
	case GameState::GameOver:
		//Draw GameOver
		break;
	default:
		break;
	}
	renderer.EnableCamera(true);

	Game::Draw(renderer);
}

void SpriteGame::OnPlayerDeath()
{
	m_lives--;
	if (m_lives <= 0)
	{
		m_gameState = GameState::GameOver;
	}
	else
	{
		m_gameState = GameState::StartLevel;
	}
}

void SpriteGame::SpawnPlayer()
{
	auto actor = Factory::Instance().Create<Actor>("PlayerPrototype");
	m_scene->AddActor(std::move(actor));
}

void SpriteGame::SpawnEnemy()
{
	auto actor = Factory::Instance().Create<Actor>("EnemyPrototype");
	actor->SetPosition({ RandomFloat(1024.0f), RandomFloat(800.0f) });
	m_scene->AddActor(std::move(actor));
	auto actor2 = Factory::Instance().Create<Actor>("FlyingEnemyPrototype");
	actor2->SetPosition({ RandomFloat(1024.0f), RandomFloat(800.0f) });
	m_scene->AddActor(std::move(actor2));
}
