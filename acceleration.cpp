/***********************************************************************
 * Source File:
 *    ACCELERATION
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about changing speed
 ************************************************************************/

#include "acceleration.h"
#include "angle.h"
#include <cmath>

/*********************************************
 * ACCELERATION : ADD
 *  a += a
 *********************************************/
void Acceleration::add(const Acceleration& acceleration)
{
    this -> ddx += acceleration.ddx;
    this -> ddy += acceleration.ddy;
}

/*********************************************
 * ACCELERATION : SET
 *  set from angle and direction
 *********************************************/
void Acceleration::set(const Angle & angle, double magnitude)
{
    ddx = magnitude * sin(angle.getRadians());
    ddy = magnitude * cos(angle.getRadians());
}

double Acceleration::getDDX()const
{
    return ddx;
}

double Acceleration::getDDY()const
{
    return ddy;
}

void Acceleration::setDDX(double ddx)
{
    this -> ddx = ddx;
}

void Acceleration::setDDY(double ddy)
{
    this -> ddy = ddy;
}

Acceleration::Acceleration()
{
    ddx = 0.0;
    ddy = 0.0;
}

Acceleration::Acceleration(double ddx, double ddy)
{
    this -> ddx = ddx;
    this -> ddy = ddy;
}

void Acceleration::addDDX(double ddx)
{
    this -> ddx += ddx;
}
void Acceleration::addDDY(double ddy)
{
    this -> ddy += ddy;
}


