#ifndef BOOSTERS_H
#define BOOSTERS_H

#include <memory>
#include <vector>
#include "Coordinate.h"

class Boosters
{
    Boosters();

    void addCoordinate(const Coordinate &&coordinate);
    bool BoosterCell(const Coordinate &&coordinate) const;
    void deleteBoosterCellAt(const Coordinate &&coordinate);

    private:
    std::unique_ptr<std::vector<Coordinate>> _coordinates;
};

#endif