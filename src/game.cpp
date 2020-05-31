#include "game.h"
#include <vector>
#include <iostream>
#include "SDL.h"
#include "Booster.h"
#include "FileUtils.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width)),
      random_h(0, static_cast<int>(grid_height))
{
  /// Get Config and update variables.
  auto config = FileUtils::getConfigFromFile();
  _numberOfBoosters = config.getNumberOfBoosters();
  _numberOfObstacles = config.getNumberOfObstacles();

  PlaceFood();
  /// Placing the obstacles;
  PlaceObstacles();
  /// Placing the Boosters;
  PlaceBoosters();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration)
{
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;
  while (running)
  {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    /// Placing the static obstacles, snake and food blocks.
    renderer.Render(snake, food, _obstacles, _boosters);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000)
    {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration)
    {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood()
{
  int x, y;
  while (true)
  {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y))
    {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update()
{
  if (!snake.alive)
    return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  if (ObstacleCell(new_x, new_y))
  {
    snake.alive = false;
    return;
  }

  if (BoosterCell(new_x, new_y))
  {
    snake.speed += 0.01;
    deleteBoosterCellAt(new_x, new_y);
    return;
  }

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y)
  {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }

void Game::PlaceObstacles()
{
  int x, y;
  while (true)
  {
    /// Return if we meet the size requiremens.
    if (_numberOfObstacles == _obstacles.size())
    {
      return;
    }

    /// Randomly generate the x and y coordinate.
    x = random_w(engine);
    y = random_h(engine);

    // Check that the location is not occupied by a (snake item + food item) before placing
    // an obstacle.
    auto foodExistsAtThisCell = food.x == x && food.y == y;
    if (!snake.SnakeCell(x, y) && !foodExistsAtThisCell)
    {
      _obstacles.emplace_back(Obstacle(x, y));
    }
  }
}

bool Game::ObstacleCell(int x, int y)
{
  for (const Obstacle &obstacle : _obstacles)
  {
    if (x == obstacle.getXCoordinate() && y == obstacle.getYCoordinate())
    {
      return true;
    }
  }
  return false;
}

bool Game::BoosterCell(int x, int y)
{
  for (const Booster &booster : _boosters)
  {
    if (x == booster.getXCoordinate() && y == booster.getYCoordinate())
    {
      return true;
    }
  }
  return false;
}

void Game::PlaceBoosters()
{
  int x, y;
  while (true)
  {
    /// Return if we meet the size requiremens.
    if (_numberOfBoosters == _boosters.size())
    {
      return;
    }

    /// Randomly generate the x and y coordinate.
    x = random_w(engine);
    y = random_h(engine);

    // Check that the location is not occupied by a (snake + food + obstacle) before placing
    // an obstacle.
    auto foodExistsAtThisCell = food.x == x && food.y == y;
    auto boosterExistsAtThisCell = BoosterCell(x, y);
    if (!snake.SnakeCell(x, y) && !foodExistsAtThisCell && !boosterExistsAtThisCell)
    {
      _boosters.emplace_back(Booster(x, y));
    }
  }
}

void Game::deleteBoosterCellAt(const int &x, const int &y)
{
  /// Early exit.
  if (_boosters.size() == 0)
  {
    return;
  }
  /// Removing the booster.
  for (auto it = _boosters.begin(); it != _boosters.end();)
  {
    if ((*it).getXCoordinate() == x && (*it).getYCoordinate() == y)
    {
      it = _boosters.erase(it);
    }
    else
    {
      ++it;
    }
  }
}