/**
 * Author: MoonPresident
 * Date: January 4th 2020
 * 
 * 
 */


#ifndef PLAYER_H
#define PLAYER_H

#include "main.h"

class Player {
private:
    float x_offset;
    float y_offset;
public:
    player();
    void setPosition(float pos[2]);
    void getPosition(float pos[2]);
};

#endif /* PLAYER_H */