/**********************************************************************
 * Header File:
 *    PROJECTILE
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a projectile
 ************************************************************************/

#pragma once

#include <list>
#include "position.h"
#include "velocity.h"
#include "acceleration.h"
#include "physics.h"
#include "howitzer.h"
#include "uiDraw.h"
#include <iostream>
using namespace std;

#define DEFAULT_PROJECTILE_WEIGHT 46.7       // kg
#define DEFAULT_PROJECTILE_RADIUS 0.077545   // m

// forward declaration for the unit test class
class TestProjectile;

 /**********************************************************************
  * Projectile
  *    Everything we need to know about a projectile
  ************************************************************************/
class Projectile
{
public:
   // Friend the unit test class
   friend TestProjectile;

   // create a new projectile with the default settings
   Projectile() : mass(46.7), radius(0.077545) {}

    void draw(ogstream& gout, double flightTime)
    {
        while (!flightPath.empty())
        {
            gout.drawProjectile(flightPath.front().pos, flightTime);
            flightPath.pop_front();
        }
    }

    void reset(int &age)
    {
        flightPath.clear();
        age = -1; 
    }

   // advance the round forward until the next unit of time
   void advance(double simulationTime, int &age);

   void fire(const Position &posHowitzer, double simulationTime, const Angle &elevation,
             double muzzleVelocity);

    bool flying() const {return !flightPath.empty(); }
    double currentTime() const {return flying() ? flightPath.back().t : 0.0; }

private:

   // keep track of one moment in the path of the projectile
   struct PositionVelocityTime
   {
      //friend TestProjectile;
      PositionVelocityTime() : pos(), v(), t(0.0) {}
      Position pos;
      Velocity v;
      double t;

//      PositionVelocityTime operator=(Howitzer& rhs)
//      {
//          this->pos = rhs.getPosition();
//          this->v = Velocity();
//          this->t = 0.0;
//          return *this;
//      }
   };

   double mass;           // weight of the M795 projectile. Defaults to 46.7 kg
   double radius;         // radius of M795 projectile. Defaults to 0.077545 m
   std::list<PositionVelocityTime> flightPath;
};
