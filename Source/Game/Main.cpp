#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"
#include "Bullet.h"
#include "SpaceGame.h"

#include <fmod.hpp>

#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <random>


using namespace nu;

class Object
{
public:
    Object() { std::cout << "constructor\n"; }
    ~Object() { std::cout << "destructor\n"; }

    Object(const Object& object) { std::cout << "copy\n"; }
    Object& operator = (const Object& object) { std::cout << "assignment\n"; return *this; }
};

uint32_t seed = 1234;

uint32_t RNG()
{
    seed = (seed * 1103515245) + 12345;
    return seed;
}

int main()
{
    //rand()
    for (size_t i = 0; i < 10; i++)
    {
        std::cout << RNG() << " ";
    }

    std::cout << std::endl;
    seed = 1234;

    for (size_t i = 0; i < 10; i++)
    {
        std::cout << RNG() << " ";
    }

    std::cout << std::endl;
    //srand((unsigned int)time(NULL));
	SeedRandom((unsigned int)time(NULL)); //-> srand((unsigned int)time(NULL));

    for (size_t i = 0; i < 10; i++)
    {
        std::cout << rand() << " ";
    }
    std::cout << std::endl;
  

    // random<>
    std::random_device randomdevice;
    std::cout << randomdevice.min() << std::endl;
    std::cout << randomdevice.max() << std::endl;
    std::cout << randomdevice.entropy() << std::endl;

    std::mt19937 generator(randomdevice());
    std::uniform_int_distribution<> dist(0, 20);
    for (size_t i = 0; i < 10; i++)
    {
        std::cout << dist(generator) << " ";
    }

    std::cout << std::endl;

    std::uniform_real_distribution<float> distReal(-10.0f, 20.0f);
    for (size_t i = 0; i < 10; i++)
    {
        std::cout << distReal(generator) << " ";
    }

    return 0;

    // INITILALIZATION
    Engine::Get().Initialize();

    SpaceGame game;
    game.Initialize();

    // create texture, using shared_ptr so texture can be shared
    //std::shared_ptr<Texture> texture = std::make_shared<Texture>();
    //texture->Load("assets/textures/JimmySnowgrave.png", Engine::Get().GetRenderer());
   
    // MAIN LOOP
    bool quit = false;
    while (!quit) 
    {
        // UPDATE
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
                quit = true;
			}
        }


        // ENGINE
        Engine::Get().Update();
        float dt = Engine::Get().GetTime().GetDeltaTime();

        // GAME
        game.Update(dt);
		

        // RENDER
        Engine::Get().GetRenderer().SetColor(0.0f, 0.0f, 0.0f);
		Engine::Get().GetRenderer().Clear();

		Engine::Get().GetRenderer().DrawTexture(*Resources().Get<Texture>("assets/textures/JimmySnowgrave.png", Engine::Get().GetRenderer()), 30, 30);

        game.Draw(Engine::Get().GetRenderer());

        Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());

        // CHARACTER
	    Engine::Get().GetRenderer().Present();
    }

    // SHUTDOWN
    Engine::Get().Shutdown();

    return 0;
}