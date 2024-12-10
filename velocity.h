/***********************************************************************
 * Header File:
 *    VELOCITY
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about speed
 ************************************************************************/

#pragma once

#include "angle.h"

// for unit tests
class TestPosition;
class TestVelocity;
class TestAcceleration;
class TestHowitzer;
class TestProjectile;

// for add()
class Acceleration;
class Angle;

 /*********************************************
  * Velocity
  * I feel the need, the need for speed
  *********************************************/
class Velocity
{
   // for unit tests
   friend TestPosition;
   friend TestVelocity;
   friend TestHowitzer;
    friend TestProjectile;
   
public:
   // constructors
    Velocity()                     ;
    Velocity(double dx, double dy) ;

   // getters
    double getDX()       const;
    double getDY()       const;
    double getSpeed()    const;

    double getAngle() const
        {
            return atan2(dy, dx); // Angle in radians
        }
        
        // Optional: Convert angle to degrees if needed
    double getAngleDegrees() const
    {
            return atan2(dy, dx) * (180.0 / M_PI); // Angle in degrees
    }

   // setters
    void setDX(double dx);
    void setDY(double dy);
    void set(const Angle & angle, double magnitude);
    void addDX(double dx) ;
    void addDY(double dy) ;
    void add(const Acceleration & acceleration, double time);
    void reverse();
    void addV(const Velocity &v);

private:
    double dx;           // horizontal velocity
    double dy;
    
    // vertical velocity
};

