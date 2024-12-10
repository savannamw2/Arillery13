/**********************************************************************
 * Header File:
 *    SIMULATION
 * Author:
 *    <your name here>
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

#pragma once
#include "position.h"
#include "howitzer.h"
#include "ground.h"
#include "projectile.h"

 /*********************************************
  * Simulation
  * Execute one simulation of a projectile being fired.
  *********************************************/
class Simulator
{
public:
   Simulator(Position & posUpperRight) : howitzer(Howitzer(posUpperRight)), ground(Ground(posUpperRight)) {
       ground.reset(howitzer.getPosition());
   }
   Howitzer howitzer;
   Ground ground;
   Projectile projectile;
};
