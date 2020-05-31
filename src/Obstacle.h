#ifndef OBSTACLE_H
#define OBSTACLE_H

struct Obstacle
{
    Obstacle(const int x, const int y): xCoordinate(x), yCoordinate(y) {}
    // TODO: See if they can be made const.
    int xCoordinate;
    int yCoordinate;
};

#endif