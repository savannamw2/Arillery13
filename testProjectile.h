/***********************************************************************
 * Header File:
 *    TEST PROJECTILE
 * Author:
 *    <your name here>
 * Summary:
 *    All the unit tests for Projectile
 ************************************************************************/


#pragma once

#include "projectile.h"
#include "position.h"
#include "howitzer.h"
#include "unitTest.h"
#include "angle.h"
#include <iostream>

using namespace std;

/*******************************
 * TEST PROJECTILE
 * A friend class for Projectile which contains the Projectile unit tests
 ********************************/
class TestProjectile : public UnitTest
{
public:
   void run()
   {
      // Ticket 3: Setup
      defaultConstructor();
      reset_empty();
      reset_full();
      fire_right();
      fire_left();
      fire_up();

      // Ticket 4: Advance
      advance_nothing();
      advance_fall();
      advance_horizontal();
      advance_up();
      advance_diagonalUp();
      advance_diagonalDown();

      report("Projectile");
   }

private:
   double metersFromPixels = -1.0;


   /*****************************************************************
    *****************************************************************
    * CONSTRUCTOR
    *****************************************************************
    *****************************************************************/

   /*********************************************
    * name:    DEFAULT CONSTRUCTOR
    * input:   nothing
    * output:  mass=46.7, radius=0.077545 flightPath={}
    *********************************************/
   void defaultConstructor()
   {
       Projectile projectile;

       assertEquals(projectile.mass, 46.7);
       assertEquals(projectile.radius, 0.077545);
       assertEquals(projectile.flightPath.size(), 0);
   }

   /*********************************************
    * name:    RESET from empty
    * input:   mass=-99, radius=-99, flightPath={}
    * output:  mass=46.7, radius=0.077545 flightPath={}
    *********************************************/
   void reset_empty()
   {
       Projectile projectile;

       projectile.mass = -99;
       projectile.radius = -99;
       projectile.flightPath = {};

       Projectile projectile2;

       projectile = projectile2;

       assertEquals(projectile.mass, 46.7);
       assertEquals(projectile.radius, 0.077545);
       assertEquals(projectile.flightPath.size(), 0);
   }

   /*********************************************
    * name:    RESET with a non-zero flight path
    * input:   mass=-99, radius=-99, flightPath={0,1,2}
    * output:  mass=46.7, radius=0.077545 flightPath={}
    *********************************************/
   void reset_full()
   {
       Projectile projectile;

       projectile.mass = -99;
       projectile.radius = -99;
       Projectile::PositionVelocityTime p1;
       Projectile::PositionVelocityTime p2;
       Projectile::PositionVelocityTime p3;

       projectile.flightPath = { p1, p2, p3 };

       Projectile projectile2;

       projectile = projectile2;

       assertEquals(projectile.mass, 46.7);
       assertEquals(projectile.radius, 0.077545);
       assertEquals(projectile.flightPath.size(), 0);
   }


   /*****************************************************************
    *****************************************************************
    * FIRE
    *****************************************************************
    *****************************************************************/

   /*********************************************
    * name:    FIRE horizontally right
    * input:   angle=90  pos=(111,222) muzzleVelocity=100
    * output:  flightPath={pos=111,222 v=100,0 t=1}
    *********************************************/
   void fire_right()
   {
       setupStandardFixture();
       Projectile p;
       Position pos;
       
       pos.x = 111;
       pos.y = 222;
       
       double simulationTime(1.0);
       
       Angle a;
       a.radians = M_PI / 2.0;
       double muzzleVelocity = 100;
       
       
       p.fire(pos, simulationTime, a, muzzleVelocity);
       
       assertUnit(p.flightPath.size() == 1);
       assertEquals(p.mass, 46.7);
       assertEquals(p.radius, 0.077545);
       
       if(!p.flightPath.empty())
       {
           assertEquals(p.flightPath.front().pos.x,  111);
           assertEquals(p.flightPath.front().pos.y,  222);
           assertEquals(p.flightPath.front().v.dx,  100);
           assertEquals(p.flightPath.front().v.dy,  0);
           assertEquals(p.flightPath.front().t,  1.0);
       }
       teardownStandardFixture();
   }

   /*********************************************
    * name:    FIRE horizontally left
    * input:   angle=-90  pos=(111,222) muzzleVelocity=100
    * output:  flightPath={pos=111,222 v=-100,0 t=1}
    *********************************************/
   void fire_left()
   {
       setupStandardFixture();
       Projectile p;
       Position pos;
       
       pos.x = 111;
       pos.y = 222;
       
       double simulationTime(1.0);
       
       Angle d;
       d.radians = -M_PI / 2.0;
       double muzzleVelocity = 100;
       
       
       p.fire(pos, simulationTime, d, muzzleVelocity);
       
       assertUnit(p.flightPath.size() == 1);
       assertEquals(p.mass, 46.7);
       assertEquals(p.radius, 0.077545);
       
       if(!p.flightPath.empty())
       {
           assertEquals(p.flightPath.front().pos.x,  111);
           assertEquals(p.flightPath.front().pos.y,  222);
           assertEquals(p.flightPath.front().v.dx,  -100);
           assertEquals(p.flightPath.front().v.dy,  0);
           assertEquals(p.flightPath.front().t,  1.0);
       }
       teardownStandardFixture();
   }

   /*********************************************
    * name:    FIRE straight up
    * input:   angle=0  pos=(111,222) muzzleVelocity=100
    * output:  flightPath={pos=111,222 v=0,100 t=1}
    *********************************************/
   void fire_up()
   {
       setupStandardFixture();
       Projectile p;
       Position pos;
       
       pos.x = 111;
       pos.y = 222;
       
       double simulationTime(1.0);
       
       Angle a;
       a.radians = 0;
       double muzzleVelocity = 100;
       
       
       p.fire(pos, simulationTime, a, muzzleVelocity);
       
       assertUnit(p.flightPath.size() == 1);
       assertEquals(p.mass, 46.7);
       assertEquals(p.radius, 0.077545);
       
       if(!p.flightPath.empty())
       {
           assertEquals(p.flightPath.front().pos.x,  111);
           assertEquals(p.flightPath.front().pos.y,  222);
           assertEquals(p.flightPath.front().v.dx,  0.0);
           assertEquals(p.flightPath.front().v.dy,  100);
           assertEquals(p.flightPath.front().t,  1.0);
       }
       teardownStandardFixture();
   }

   /*****************************************************************
    *****************************************************************
    * ADVANCE
    *****************************************************************
    *****************************************************************/

   /*********************************************
    * name:    ADVANCE : the projectile is not fired. Nothing will happen
    * input:   flightPath={}
    * output:  flightPath={}
    *********************************************/
   void advance_nothing()
   {
       setupStandardFixture();
       Projectile p;
       int age = 0;
       p.mass = 333.3;
       p.radius = 444.4;
       
       p.advance(1.0,age);
       
       assertUnit(p.flightPath.size() == 0);
       assertEquals(p.mass, 333.3);
       assertEquals(p.radius, 444.4);
       assertEquals(age, 1);
       
       teardownStandardFixture();
       
   }

   /*********************************************
    * name:    ADVANCE : the projectile is stationary and falls down
    * input:   flightPath={pos=100,200 v=0,0 t=100}
    * output:  flightPath={}{pos.x=100      = 100 + 0*1
    *                        pos.y=195.0968 = 200 + 0*1 + .5(-9.806)*1*1
    *                        v.dx =0        = 0 + 0*1
    *                        v.dy =-9.8     = 0 + (-9.8064)*1
    *                        t=101}
    *********************************************/
   void advance_fall()
   {
       setupStandardFixture();
       Position pos;
       Projectile p;
       Projectile::PositionVelocityTime pvt;
       int age = 0;
       
       pvt.pos.x = 100;
       pvt.pos.y = 200;
       pvt.v.dx = 0;
       pvt.v.dy = 0;
       pvt.t = 100;
       p.flightPath.push_back(pvt);
       
       p.advance(101.0, age);
       
       
       assertUnit(p.flightPath.size() == 2);
       assertEquals(p.mass, 46.7);
       assertEquals(p.radius, .077545);
       
       if(!p.flightPath.empty())
       {
           assertEquals(p.flightPath.back().pos.x,  100);
           assertEquals(p.flightPath.back().pos.y,  195.0968);
           assertEquals(p.flightPath.back().v.dx,  0.0);
           assertEquals(p.flightPath.back().v.dy,  -9.8064);
           assertEquals(p.flightPath.back().t,  101.0);
           
       }
       teardownStandardFixture();
   }

   /*********************************************
    * name:    ADVANCE : the projectile is traveling horizontally
    * input:   flightPath={pos=100,200 v=50,0 t=100}
    * output:  flightPath={}{pos.x=149.9756 = 100 + 50*1 + .5(-0.0487)*1*1
    *                        pos.y=195.0968 = 200 + 0*1  + .5(-9.8064)*1*1
    *                        v.dx =49.9513  = 50 + (-0.0487)*1
    *                        v.dy =-9.8064  = 0  + (-9.8064)*1
    *                        t=101}
    *********************************************/
   void advance_horizontal()
   {
       setupStandardFixture();
       Position pos;
       Projectile p;
       Projectile::PositionVelocityTime pvt;
       int age = 0;
       pvt.pos.x = 100;
       pvt.pos.y = 200;
       pvt.v.dx = 50;
       pvt.v.dy = 0;
       pvt.t = 100;
       p.flightPath.push_back(pvt);
       
       p.advance(101.0, age);
       
       assertUnit(p.flightPath.size() == 2);
       assertEquals(p.mass, 46.7);
       assertEquals(p.radius, .077545);
       
       if(!p.flightPath.empty())
       {
           assertEquals(p.flightPath.back().pos.x,  149.9756);
           assertEquals(p.flightPath.back().pos.y,  195.0968);
           assertEquals(p.flightPath.back().v.dx,  49.9513);
           assertEquals(p.flightPath.back().v.dy,  -9.8064);
           assertEquals(p.flightPath.back().t,  101.0);
       }
       teardownStandardFixture();
       
   }

   /*********************************************
    * name:    ADVANCE : the projectile is traveling up, no horizontal position change
    * input:   flightPath={pos=100,200 v=0,100 t=100}
    * output:  flightPath={}{pos.x=100      = 0   + 0*1   + .5(0)*1*1
    *                        pos.y=294.9021 = 200 + 100*1 + .5(-9.8064-.3893)*1*1
    *                        v.dx =0        = 0   + 0*1
    *                        v.dy =89.8042  = 100 + (-9.8064-.3893)
    *                        t=101}
    *********************************************/
   void advance_up()
   {
       setupStandardFixture();
       Position pos;
       Projectile p;
       Projectile::PositionVelocityTime pvt;
       int age = 0;
       pvt.pos.x = 100;
       pvt.pos.y = 200;
       pvt.v.dx = 0;
       pvt.v.dy = 100;
       pvt.t = 100;
       p.flightPath.push_back(pvt);
       
       p.advance(101.0, age);
       
       cout << "pos: x" << p.flightPath.back().pos.x;
       cout << "pos: y" << p.flightPath.back().pos.y;
       cout << "pos: dx" << p.flightPath.back().v.dx;
       cout << "velocity dy" << p.flightPath.back().v.dy;
       
       assertUnit(p.flightPath.size() == 2);
       assertEquals(p.mass, 46.7);
       assertEquals(p.radius, .077545);
       
       if(!p.flightPath.empty())
       {
           assertEquals(p.flightPath.back().pos.x,  100);
           assertEquals(p.flightPath.back().pos.y,  294.9021);
           assertEquals(p.flightPath.back().v.dx,  0.0);
           assertEquals(p.flightPath.back().v.dy,  89.8042);
           assertEquals(p.flightPath.back().t,  101.0);
       }
       teardownStandardFixture();
   }

   /*********************************************
    * name:    ADVANCE : the projectile is traveling up and across
    * input:   flightPath={pos=100,200 v=50,40 t=100}
    * .5 * drag * density * (velocity * velocity) * (M_PI * (radius * radius));
    * output:  flightPath={}{pos.x=149.9600 = 100 + 50*1 + .5(-0.0799)*1*1
    *                        pos.y=235.0648 = 200 + 40*1 + .5(-9.8064-0.0638)*1*1
    *                        v.dx =49.9201  = 50 + (-.0799)*1
    *                        v.dy =30.1297  = 40 + (-9.8064-0.0638)*1
    *                        t=101}
    *********************************************/
   void advance_diagonalUp()
   {
       setupStandardFixture();
       Position pos;
       Projectile p;
       Projectile::PositionVelocityTime pvt;
       int age = 0;
       
       p.flightPath.push_back(pvt);
       p.flightPath.push_back(pvt);
       pvt.pos.x = 100;
       pvt.pos.y = 200;
       pvt.v.dx = 50;
       pvt.v.dy = 40;
       pvt.t = 100;
       p.flightPath.push_back(pvt);

       p.advance(101, age);
       

       assertUnit(p.flightPath.size() == 4);
       assertEquals(p.mass, 46.7);
       assertEquals(p.radius, 0.077545);
       assertUnit(!p.flightPath.empty());
       if (!p.flightPath.empty())
       {
          assertEquals(p.flightPath.back().pos.x, 149.6000); 
          assertEquals(p.flightPath.back().pos.y, 235.0648);
          assertEquals(p.flightPath.back().v.dx, 49.9201);
          assertEquals(p.flightPath.back().v.dy, 30.1297);
          assertEquals(p.flightPath.back().t, 101.0);
       }
   }

   /*********************************************
    * name:    ADVANCE : the projectile is traveling down and across
    * input:   flightPath={}{}{pos=100,200 v=50,-40 t=100}
    * output:  flightPath={}{}{}{pos.x=149.9201 = 100 + 50*1 + .5(-0.0799)*1*1
    *                            pos.y=155.1287 = 200 +-40*1 + .5(-9.8064+0.0638)*1*1
    *                            v.dx = 49.9201 =  50 + (-0.0799)*1
    *                            v.dy =-49.7425 = -40 + (-9.8064+0.0638)*1*1
    *                            t=101}
    *********************************************/
   void advance_diagonalDown()
   {  // setup
      setupStandardFixture();
      Position pos;
      Projectile p;
      Projectile::PositionVelocityTime pvt;
       
       int age = 0;
      p.flightPath.push_back(pvt);
      p.flightPath.push_back(pvt);
      pvt.pos.x = 100.0;
      pvt.pos.y = 200.0;
      pvt.v.dx = 50.0;
      pvt.v.dy = -40.0;
      pvt.t = 100.0;
      p.flightPath.push_back(pvt);
      // exercise
      p.advance(101.0, age);
      // verify
      assertUnit(p.flightPath.size() == 4);
      assertEquals(p.mass, 46.7);
      assertEquals(p.radius, 0.077545);
      assertUnit(!p.flightPath.empty());
      if (!p.flightPath.empty())
      {
         assertEquals(p.flightPath.back().pos.x, 149.9601); // 100 + 50*1 + .5(-0.0799)*1*1
         assertEquals(p.flightPath.back().pos.y, 155.1287); // 200 +-40*1 + .5(-9.8064+0.0638)*1*1
         assertEquals(p.flightPath.back().v.dx, 49.9201);   // 50 + (-0.0799)*1
         assertEquals(p.flightPath.back().v.dy, -49.7425);  //-40 + (-9.8064+0.0638)*1*1
         assertEquals(p.flightPath.back().t, 101.0);
      }
      // teardown
      teardownStandardFixture();
   }

   /*****************************************************************
    *****************************************************************
    * STANDARD FIXTURE
    *****************************************************************
    *****************************************************************/

   // setup standard fixture - set the zoom to 1100m per pixel
   void setupStandardFixture()
   {
      Position p;
      metersFromPixels = p.metersFromPixels;
      p.metersFromPixels = 1.0;
   }

   // teardown the standard fixture - reset the zoom to what it was previously
   void teardownStandardFixture()
   {
      assert(metersFromPixels != -1.0);
      Position p;
      p.metersFromPixels = metersFromPixels;
   }

};
