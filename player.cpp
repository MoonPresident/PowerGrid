/**
 * Author: MoonPresident
 * Date: January 4th 2020
 * 
 * 
 */

#include "player.h"


/**
 * @brief Constructor function.
 */
Player::player() {
    x_offset = 0.f;
    y_offset = 0.f;
    bearing = 0.f;
    scale = 1.f;
};

/**
 * @brief Exposes internal state variable.
 * @param pos
 */
void Player::setPosition(float pos[]) {
    x_offset = pos[0];
    y_offset = pos[1];
};

void Player::getPosition(float pos[]) {
    pos[0] = x_offset;
    pos[1] = y_offset;
}

float Player::getX() {
    return x_offset;
}

void Player::setX(float x) {
    x_offset = x;
}

float Player::getY() {
    return y_offset;
}

void Player::setY(float y) {
    y_offset = y;
}

float Player::getBearing() {
    return bearing;
}

void Player::setBearing(float new_bearing) {
    bearing = new_bearing;
}

float Player::getScale() {
    return scale;
}

void Player::setScale(float new_scale) {
    scale = new_scale;
}