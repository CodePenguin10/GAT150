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
#include <fstream>

using namespace nu;

class Animal
{
public:
    virtual void Speak() { std::cout << "???"; }
};

class Cat : public Animal
{
    void Speak() override { std::cout << "Meow"; }
};

class Dog : public Animal
{
    void Speak() override { std::cout << "Woof"; }
};

class Bird : public Animal
{
    void Speak() override { std::cout << "EY! I'M FLYING ERE'"; }
};

/*
enum class Type
{
    Cat = 1,
    Dog,
    Bird
};

Animal* AnimalFactory(Type id)
{
    Animal* animal = nullptr;

    switch (id)
    {
    case Type::Cat:
        animal = new Cat();
        break;
    case Type::Dog:
        animal = new Dog();
        break;
    case Type::Bird:
        animal = new Bird();
        break;
    default:
        break;
    }

    return animal;
}

*/

Animal* AnimalFactory(const std::string& id)
{
    Animal* animal = nullptr;

    if (nu::ToLower(id) == "cat") animal = new Cat;
    else if (nu::EqualsIgnoreCase(id, "dog")) animal = new Dog;
    else if (id == "bird") animal = new Bird;
    return animal;
}

//class Icreator
//{
//public:
//    virtual ~Icreator() = default;
//    virtual std::unique_ptr<Animal> Create() = 0;
//};
//
//template <typename T>
//class Creator : public Icreator
//{
//public:
//    std::unique_ptr<Animal> Create() override { return std::make_unique<T>(); }
//};
//
//std::map<std::string, std::unique_ptr<Icreator>> registry;

int main()
{
    Factory::Instance().Register<Actor>("Actor");
    auto actor = Factory::Instance().Create<Actor>("Actor");
    std::cout << actor->IsActive() << std::endl;

    /*registry["Cat"] = std::make_unique<Creator<Cat>>();
    registry["Dog"] = std::make_unique<Creator<Dog>>();
    registry["Bird"] = std::make_unique<Creator<Bird>>();

    auto animal = registry["Bird"]->Create();
    animal->Speak();*/


    /*std::string selection;
    std::cout << "Select Aniaml: ";
    std::cin >> selection;

    auto animal = AnimalFactory(selection);
    if (animal) animal->Speak();*/

    return 0;

    // INITILALIZATION
    Engine::Get().Initialize();

    SpaceGame game;
    game.Initialize();

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

        game.Draw(Engine::Get().GetRenderer());
        Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());

	    Engine::Get().GetRenderer().Present();
    }

    // SHUTDOWN
    Engine::Get().Shutdown();

    return 0;
}