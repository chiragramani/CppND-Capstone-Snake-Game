#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"
#include "Obstacle.h"
#include "Booster.h"
#include <memory>
#include "Obstacles.h"

class Renderer
{
public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  /// Rendering initial static obstacles
  void Render(Snake const snake,
              SDL_Point const &food,
              const std::shared_ptr<Obstacles> obstacles,
              const std::vector<Booster> &boosters);

  void UpdateWindowTitle(int score, int fps);

private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  // Obstacle surface
  SDL_Surface *obstacleSurface;
  // Obstacle Texture
  SDL_Texture *obstacleTexture;

  // Booster surface
  SDL_Surface *boosterSurface;
  // Booster Texture
  SDL_Texture *boosterTexture;

  void placeObstacles(const std::shared_ptr<Obstacles> obstacles) const;
  void placeBoosters(const std::vector<Booster> &boosters) const;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif