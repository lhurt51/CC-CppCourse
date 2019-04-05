#include "Game.hpp"
#include "TextureManager.h"
#include "Scene.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"

Manager		manager;
Scene*		scene;

bool Game::isRunning = false;

SDL_Rect Game::camera = { 0, 0, 1100, 1200 };

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

AssetManager* Game::assets = new AssetManager(&manager);

auto& player(manager.addEntity());
auto& ai(manager.addEntity());
auto& ai1(manager.addEntity());
auto& ai2(manager.addEntity());

Game::Game()
{
}


Game::~Game()
{
}

void Game::init(const char * title, int xPos, int yPos, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialised! ..." << std::endl;

		window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
		if (window)
		{
			std::cout << "Window created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}

		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	assets->AddTexture("terrain", "assets/terrain_ss.png");
	assets->AddTexture("player", "assets/player_anims.png");
	assets->AddTexture("projectile", "assets/circle.png");
	assets->AddTexture("snake", "assets/snake.png");
	assets->AddTexture("rabbit", "assets/rabbit_1939x1714.png");
	assets->AddTexture("turtle", "assets/turtle_400x400.png");

	scene = new Scene("terrain", 3, 32);

	scene->loadScene("assets/map.map", 25, 20);
	
	player.addComponent<TransformComponent>(1800, 640, 32, 32, 4.0f);
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	ai.addComponent<TransformComponent>(350, 950, 911, 2403, 0.1f);
	ai.addComponent<SpriteComponent>("snake", false);
	ai.addComponent<AIRaceComponent>(Vector2D(2.2, 0), 1000, 4);
	ai.addComponent<ColliderComponent>("ai");
	ai.addGroup(groupAI);

	ai1.addComponent<TransformComponent>(350, 1070, 1714, 1939, 0.1f);
	ai1.addComponent<SpriteComponent>("rabbit", false);
	ai1.addComponent<AIRaceComponent>(Vector2D(1.75, 0), 1000, 3);
	ai1.addComponent<ColliderComponent>("ai");
	ai1.addGroup(groupAI);

	ai2.addComponent<TransformComponent>(350, 760, 400, 400, 0.5f);
	ai2.addComponent<SpriteComponent>("turtle", false);
	ai2.addComponent<AIRaceComponent>(Vector2D(1.2, 0), 950, 2);
	ai2.addComponent<ColliderComponent>("ai");
	ai2.addGroup(groupAI);
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& AIs(manager.getGroup(Game::groupAI));
auto& colliders(manager.getGroup(Game::groupColliders));

void Game::handleEvents()
{
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
	}
}

void Game::update()
{
	SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
	Vector2D playerPos = player.getComponent<TransformComponent>().position;
	Vector2D AIpos[3];

	for (int i = 0; i < 3; i++)
	{
		AIpos[i] = AIs[i]->getComponent<TransformComponent>().position;
	}

	manager.refresh();
	manager.update();

	for (auto& c : colliders)
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;

		if (Collision::AABB(cCol, playerCol))
		{
			player.getComponent<TransformComponent>().position = playerPos;
		}
		for (int i = 0; i < 3; i++)
		{
			SDL_Rect aiCol = AIs[i]->getComponent<ColliderComponent>().collider;
			if (Collision::AABB(cCol, aiCol))
			{
				AIs[i]->getComponent<TransformComponent>().velocity = AIpos[i];
			}
		}
	}

	float tmpx, tmpy;
	if (ai.getComponent<TransformComponent>().velocity.x == 0 &&
		ai1.getComponent<TransformComponent>().velocity.x == 0 &&
		ai2.getComponent<TransformComponent>().velocity.x == 0)
	{
		if (!player.hasComponent<SpriteComponent>())
		{
			player.addComponent<SpriteComponent>("player", true);
			player.addComponent<KeyboardController>();
		}
		tmpx = player.getComponent<TransformComponent>().position.x - 540;
		tmpy = player.getComponent<TransformComponent>().position.y - 340;
	}
	else
	{
		tmpx = ai.getComponent<TransformComponent>().position.x - 540;
		tmpy = ai.getComponent<TransformComponent>().position.y - 340;
	}
	camera.x = tmpx;
	camera.y = tmpy;

	if (camera.x < 0) camera.x = 0;
	if (camera.y < 0) camera.y = 0;
	if (camera.x > camera.w) camera.x = camera.w;
	if (camera.y > camera.h) camera.y = camera.h;
}

void Game::render()
{
	SDL_RenderClear(renderer);
	for (auto& t : tiles)
	{
		t->draw();
	}
	for (auto& ai : AIs)
	{
		ai->draw();
	}
	for (auto& p : players)
	{
		p->draw();
	}
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Clean" << std::endl;
}
