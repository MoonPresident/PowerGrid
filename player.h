/**
 * Author: MoonPresident
 * Date: January 4th 2020
 * 
 * 
 */


#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    float x_offset;
    float y_offset;
    float bearing;
    float scale;
    
    
    Player();
    void setPosition(float pos[2]);
    void getPosition(float pos[2]);
    float getX();
    void setX(float x);
    float getY();
    void setY(float y);
    float getBearing();
    void setBearing(float new_bearing);
    float getScale();
    void setScale(float new_scale);
};

#endif /* PLAYER_H */