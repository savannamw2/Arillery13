/***********************************************************************
 * Source File:
 *    ANGLE
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#include "angle.h"
#include <math.h>  // for floor()
#include <cassert>
using namespace std;

#define TWO_PI 6.28318530718

 /************************************
  * ANGLE : NORMALIZE
  ************************************/
double Angle::normalize(double radians) const
{
    radians = fmod(radians, TWO_PI);
    if (radians < 0)
    {
        radians += TWO_PI;
    }
    
    return radians;
}
/************************************
 * convertToRadians
 ************************************/
double convertToRadians(double degrees)
{
    double r;
    r = degrees * (M_PI /  180.0);
    return r;
}
/************************************
 * convertToDegrees
 ************************************/
double convertToDegrees(double r)
{
    double degrees;
    degrees = r * (180.0 / M_PI);
    return degrees;
}

double Angle::getDegrees() const
{
    double degrees = convertToDegrees(Angle::radians);
    return degrees;
}
double Angle::getRadians() const
{
    return radians;
}
 void Angle::setDegrees(double degrees)
{
     radians = convertToRadians(degrees);
     radians = normalize(radians);
}

void Angle::setRadians(double radians)
{
    this -> radians = normalize(radians);
}

void Angle::setUp()
{
    radians = convertToDegrees(0);
}

void Angle::setDown()
{
    radians = convertToRadians(180);
}

void Angle::setLeft()
{
    radians = convertToRadians(270);
}

void Angle::setRight()
{
    radians = convertToRadians(90);
}

void Angle::reverse()
{
    radians += convertToRadians(180);
    radians = normalize(radians);
}

Angle& Angle::add(double delta)
{
    radians = radians + delta;
    radians = normalize(radians);
    return *this;
}

Angle::Angle()
{
    radians = 0;
}

Angle::Angle(const Angle& rhs)
{
    this -> radians = rhs.radians;
}

Angle::Angle(double degrees)
{
    radians = convertToRadians(degrees);
}

double Angle::getDx()
{
    dx = 1 * sin(radians);
    return dx;
}

double Angle::getDy()
{
    dy = 1 * cos(radians);
    return dy;
}

void Angle::setDxDy(double dx, double dy)
{
    this ->  dx = dx;
    this ->  dy = dy;
    radians = normalize(atan2(dx, dy));
}

bool Angle::isLeft()
{
    if (radians >= M_PI && radians <= TWO_PI)
    {
        return true;
    }
    return false;
}

bool Angle::isRight()
{
    if (radians >= 0 && radians <= M_PI )
    {
        return true;
    }
    return false;
}
