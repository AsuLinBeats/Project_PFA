#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "GamesEngineeringBase.h"  // Include any necessary dependencies

class CObject;  // Forward declaration if necessary

class Camera {
private:
    int offsetX, offsetY; // Offset of the camera
    int screenWidth, screenHeight;
public:
    Camera(int width, int height) : screenWidth(width), screenHeight(height), offsetX(0), offsetY(0) {}

    void Update(CObject& player);

    int getOffsetX() const { return offsetX; }
    int getOffsetY() const { return offsetY; }
};

#endif // CAMERA_H