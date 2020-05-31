#ifndef BOOSTER_H
#define BOOSTER_H

struct Booster
{
    // Constructor
    Booster(const int x, const int y) : xCoordinate(x), yCoordinate(y) {}

    // Getters

    int getXCoordinate() const { return xCoordinate; }
    int getYCoordinate() const { return yCoordinate; }

private:
    int xCoordinate;
    int yCoordinate;
};

#endif