/***********************************************************************
 * Source File:
 *    VELOCITY
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about speed
 ************************************************************************/

#include "velocity.h"
#include "acceleration.h"
#include "angle.h"

#include <math.h>  // for sqrt()

/*********************************************
 * VELOCITY : ADD
 *  v = v_0 + a t
 *********************************************/
void Velocity::add(const Acceleration& acceleration, double time)
{
    dx += acceleration.getDDX() * time;
    dy += acceleration.getDDY() * time;
}

/*********************************************
 * VELOCITY : GET SPEED
 *  find the magnitude of velocity
 *********************************************/
double Velocity::getSpeed() const
{
    return sqrt((dx * dx) + (dy * dy));
}

/*********************************************
 * VELOCITY : SET
 *  set from angle and direction
 *********************************************/
void Velocity::set(const Angle & angle, double magnitude)
{
    dx = magnitude * sin(angle.getRadians());
    dy = magnitude * cos(angle.getRadians());
}

double Velocity::getDX() const
{
    return dx;
}

double Velocity::getDY() const
{
    return dy;
}

void Velocity::setDX(double dx)
{
    this -> dx = dx;
}

void Velocity::setDY(double dy)
{
    this -> dy = dy;
}

Velocity::Velocity()
{
    dx = 0.0;
    dy = 0.0;
}

Velocity::Velocity(double dx, double dy)
{
    this -> dx = dx;
    this -> dy = dy;
}
//+ addDX(ddx : Double)
//+ addDY(ddy : Double)

void Velocity::addDX(double ddx)
{
    this -> dx += ddx;
}

void Velocity::addDY(double ddy)
{
    this -> dy += ddy;
}

void Velocity::reverse()
{
    this -> dx = - dx;
    this -> dy = - dy;
}

void Velocity::addV(const Velocity &v)
{
    this -> dx += v.dx;
    this -> dy += v.dy;
}

