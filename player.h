/**
 * Author: MoonPresident
 * Date: January 4th 2020
 * 
 * 
 */

#include "DisplayObject.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    GLfloat location[4];
    std::vector<DisplayObject> display_objects;
    
    
    Player() {
        for(int i = 0; i < 4; i++) location[i] = 0.f;
    }
    
    void setLocation(GLfloat scale[]) {
        for(auto obj: display_objects) obj.setLocation(location, scale);
    }
};

#endif /* PLAYER_H */