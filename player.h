/**
 * Author: MoonPresident
 * Date: January 4th 2020
 * 
 * 
 */


#ifndef PLAYER_H
#define PLAYER_H

class Player {
private:
    float x_offset;
    float y_offset;
public:
    player();
    void setPosition(float pos[2]);
    void getPosition(float pos[2]);
    void setX(float x);
    void setY(float y);
    float getX();
    float getY();
};

#endif /* PLAYER_H */