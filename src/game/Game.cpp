#include "Game.h"

void Game::init()
{
    scene.init();
}

void Game::update(
    float dt,
    SDL_Window* window
)
{
    scene.update(dt, window);
}

void Game::render()
{
    scene.render();
}