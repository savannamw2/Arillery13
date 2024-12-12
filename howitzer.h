/**********************************************************************
 * Header File:
 *    HOWITZER
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a howitzer (aka the gun)
 ************************************************************************/

#pragma once

#include <list>
#include "angle.h"
#include "position.h"
#include "velocity.h"
#include "physics.h"
#include "uiDraw.h"


#pragma once

#define DEFAULT_MUZZLE_VELOCITY   827.00     // m/s


class TestHowitzer;
//class TestProjectile;

 /*********************************************
  * Howitzer
  * Everything we need to know about a howitzer (aka the gun)
  *********************************************/
class Howitzer
{
public:
    // for unit tests
    friend ::TestHowitzer;
    friend TestProjectile;
    
    int age;
    // default constructor
    Howitzer() : muzzleVelocity(DEFAULT_MUZZLE_VELOCITY), elevation(Angle(45.0)), age(-1) {
    }

    Howitzer(Position positionUpperRight) : muzzleVelocity(DEFAULT_MUZZLE_VELOCITY), elevation(Angle(45.0)), age(-1) {
        generatePosition(positionUpperRight);
    }
    // draw
    void draw(ogstream& gout) const
    {
        gout.drawHowitzer(position,
            elevation.getRadians(), age);
    }

    // where is the howitzer at right now?
    Position& getPosition() { return position; }

    // generate a new position for the howitzer
    void generatePosition(Position& posUpperRight)
    {
        double xPixels = random(posUpperRight.getPixelsX() * 0.1,
            posUpperRight.getPixelsX() * 0.9);
        position.setPixelsX(xPixels);
        position.setPixelsY(0);
    }

    // get the muzzle velocity
    double getMuzzleVelocity() const { return muzzleVelocity; }

    // move the angle of the howitzer
    void rotate(double radian) { elevation.add(radian); }

    // raise (or lower) the howitzer
    void raise(double radian)
    {
        elevation.add(elevation.isRight() ? -radian : radian);
    }

    // get the elevation
    const Angle& getElevation() const { return elevation; }

private:
    Position position;      // initial position of the projectile
    double muzzleVelocity;  // muzzle velocity, defaults to 827.0 m/s
    Angle elevation;        // the elevation of the howitzer where 0 is up and positive is right.
  
};
