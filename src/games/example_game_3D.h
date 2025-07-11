/**
 * Author: MoonPresident
 * Date: August 31st 2021
 * 
 * Game sequence for squares.
 */
 
#include "ExplorableSimulation.h"

#ifndef EXAMPLE_GAME_3D_H
#define EXAMPLE_GAME_3D_H

class ExampleGame3D: public ExplorableSimulation {
public:
    ExampleGame3D();
    ~ExampleGame3D();
    
    void run() override;
};


int example_game_3D();

#endif /* EXAMPLE_GAME_3D_H */
