#include "SpaceGame.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"
#include <memory>

using namespace nu;

bool SpaceGame::Initialize()
{
	Game::Initialize();

	m_scene = new Scene();
	m_scene->SetGame(this);

	m_titleText = new Text(Resources().GetWithID<Font>("title_font", "assets/fonts/Private Teacher.ttf", 128.0f));
	m_titleText->Create(Engine::Get().GetRenderer(), "Some Space Game IG", nu::Color{ 1.0f, 1.0f, 1.0f });

	m_scoreText = new Text(Resources().GetWithID<Font>("game_font", "assets/fonts/Private Teacher.ttf", 32.0f));
	m_livesText = new Text(Resources().Get<Font>("game_font", 32.0f));



	return true;
}

void SpaceGame::Update(float dt)
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
			SpawnEnemy2();
			SpawnEnemy3();
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

void SpaceGame::Draw(class nu::Renderer& renderer)
{
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
	Game::Draw(renderer);
}

void SpaceGame::OnPlayerDeath()
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

void SpaceGame::SpawnPlayer()
{
	PlayerDesc playerDesc;
	playerDesc.name = "Player";
	playerDesc.tag = "Player";
	playerDesc.model = assets::playerModel;
	//playerDesc.texture = Resources().Get<Texture>("Texture name", Engine::Get().GetRenderer());
	playerDesc.transform = nu::Transform{ nu::Vector2{ 640.0f, 512.0f }, 0.0f, 25.0f };
	playerDesc.damping = 0.75f;
	playerDesc.speed = 750.0f;

	std::unique_ptr<Player> player = std::make_unique<Player>(playerDesc);
	m_scene->AddActor(std::move(player));
}

void SpaceGame::SpawnEnemy()
{
	EnemyDesc enemyDesc;
	enemyDesc.name = "Enemy";
	enemyDesc.tag = "Enemy";
	enemyDesc.model = assets::enemyModel;
	enemyDesc.transform = nu::Transform{ nu::Vector2{ nu::RandomFloat(0.0f, 1280.0f), nu::RandomFloat(0.0f, 1024.0f)}, 0.0f, 25.0f };
	enemyDesc.damping = 0.75f;
	enemyDesc.health = 1.0f;
	enemyDesc.speed = nu::RandomFloat(700.0f, 850.0f);

	m_scene->AddActor(std::move(std::make_unique<Enemy>(enemyDesc)));
}

void SpaceGame::SpawnEnemy2()
{
	EnemyDesc enemyDesc;
	enemyDesc.name = "Enemy2";
	enemyDesc.tag = "Enemy2";
	enemyDesc.model = assets::enemyModel2;
	enemyDesc.transform = nu::Transform{ nu::Vector2{ nu::RandomFloat(0.0f, 1280.0f), nu::RandomFloat(0.0f, 1024.0f)}, 0.0f, 25.0f };
	enemyDesc.damping = 0.75f;
	enemyDesc.health = 2.0f;
	enemyDesc.speed = nu::RandomFloat(600.0f, 750.0f);

	m_scene->AddActor(std::move(std::make_unique<Enemy>(enemyDesc)));
}

void SpaceGame::SpawnEnemy3()
{
	EnemyDesc enemyDesc;
	enemyDesc.name = "Enemy3";
	enemyDesc.tag = "Enemy3";
	enemyDesc.model = assets::enemyModel3;
	enemyDesc.transform = nu::Transform{ nu::Vector2{ nu::RandomFloat(0.0f, 1280.0f), nu::RandomFloat(0.0f, 1024.0f)}, 0.0f, 25.0f };
	enemyDesc.damping = 0.75f;
	enemyDesc.health = 3.0f;
	enemyDesc.speed = nu::RandomFloat(500.0f, 650.0f);

	m_scene->AddActor(std::move(std::make_unique<Enemy>(enemyDesc)));
}
