#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"
#include "Obstacle.h"

class Renderer
{
public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  /// Rendering initial static obstacles
  void Render(Snake const snake, SDL_Point const &food, const std::vector<Obstacle> &obstacles);

  void UpdateWindowTitle(int score, int fps);

private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  // Obstacle surface
  SDL_Surface *obstacleSurface;
  // Obstacle Texture
  SDL_Texture *obstacleTexture;

  void placeObstacles(const std::vector<Obstacle> &obstacles) const;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif