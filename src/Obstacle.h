#ifndef OBSTACLE_H
#define OBSTACLE_H

struct Obstacle
{
    Obstacle(const int x, const int y): xCoordinate(x), yCoordinate(y) {};

    // Getters
    int getXCoordinate() const { return xCoordinate; }
    int getYCoordinate() const { return yCoordinate; }

    private:
    int xCoordinate;
    int yCoordinate;
};

#endif