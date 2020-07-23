/**
 * Author: MoonPresident
 * Date: January 4th 2020
 * 
 * 
 */

#include "player.h"

Player::player() {
    x_offset = 0.f;
    y_offset = 0.f;
};

void Player::setPosition(float pos[]) {
    x_offset = pos[0];
    y_offset = pos[1];
};

void Player::getPosition(float pos[]) {
    pos[0] = x_offset;
    pos[1] = y_offset;
}

void Player::setX(float x) {
    x_offset = x;
}

void Player::setY(float y) {
    y_offset = y;
}

float Player::getX() {
    return x_offset;
}

float Player::getY() {
    return y_offset;
}