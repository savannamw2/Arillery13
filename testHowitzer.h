/***********************************************************************
 * Header File:
 *    TEST HOWITZER
 * Author:
 *    <your name here>
 * Summary:
 *    All the unit tests for Howitzer
 ************************************************************************/


#pragma once

#include "howitzer.h"
#include "unitTest.h"
#include <cassert>

/*******************************
 * TEST HOWITZER
 * A friend class for Howitzer which contains the Howitzer unit tests
 ********************************/
class TestHowitzer : public UnitTest
{
public:
   void run()
   {
      // Ticket 1: Getters
      defaultConstructor();
      getPosition_zero();
      getPosition_middle();
      getMuzzleVelocity_slow();
      getMuzzleVelocity_standard();
      getElevation_up();
      getElevation_right();
      getElevation_left();

      // Ticket 2: Setters
      generatePosition_small();
      generatePosition_large();
      raise_rightDown();
      raise_rightUp();
      raise_leftDown();
      raise_leftUp();
      rotate_clock();
      rotate_counterClock();
      rotate_wrapClock();
      rotate_wrapCounterClock();

      report("Howitzer");
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
     * output:  zeros (except angle is at 45 degrees,
     *                 and the muzzle velocity is correct)
     *********************************************/
   void defaultConstructor()
   {
       //setup
       Howitzer howitzer;

       //exercise
       double v = howitzer.muzzleVelocity;
       Angle elevation = howitzer.elevation;
       double radians = elevation.radians;

       //verify
       assertEquals(v, 827.00);
       assertEquals(radians, M_PI/4);
   }

   /*****************************************************************
    *****************************************************************
    * GETTERS
    *****************************************************************
    *****************************************************************/

    /*********************************************
     * name:    GET POSITION ZERO
     * input:   h.pos=(0,0)
     * output:  pos=(0,0)
     *********************************************/
   void getPosition_zero()
   {
       Howitzer howitzer;

       //Setup
       howitzer.position.x = 0;
       howitzer.position.y = 0;

       //Exercise
       Position position  = howitzer.getPosition();
       
       //Verify
       assertEquals(position.x, 0);
       assertEquals(position.y, 0);
   } // Teardown

   /*********************************************
    * name:    GET POSITION MIDDLE
     * input:   h.pos=(123.4, 567.8)
     * output:  pos=(123.4, 567.8)
    *********************************************/
   void getPosition_middle()
   {
       Howitzer howitzer;

       howitzer.position.x = 123.4;
       howitzer.position.y = 567.8;

       //Exercise
       Position position = howitzer.getPosition();

       assertEquals(howitzer.position.x, 123.4);
       assertEquals(howitzer.position.y, 567.8);
   }

   /*********************************************
    * name:    GET MUZZLE VELOCITY - SLOW SPEED
     * input:   h.muzzleVelocity=(24.68)
     * output:  m=24.68
    *********************************************/
   void getMuzzleVelocity_slow()
   {
       Howitzer howitzer;

       howitzer.muzzleVelocity = 24.68;

       double v = howitzer.getMuzzleVelocity();

       assertEquals(v, 24.68);
   }

   /*********************************************
    * name:    GET MUZZLE VELOCITY - STANDARD SPEED
     * input:   h.muzzleVelocity=(827.00)
     * output:  m=827
    *********************************************/
   void getMuzzleVelocity_standard()
   {
       Howitzer howitzer;

       howitzer.muzzleVelocity = 827.00;

       double v = howitzer.getMuzzleVelocity();

       assertEquals(v, 827.00);
   }

   /*********************************************
    * name:    GET ELEVATION - up
     * input:   h.elevation=0
     * output:  e=0
    *********************************************/
   void getElevation_up()
   {
       Howitzer howitzer;

       howitzer.elevation = 0;

       Angle e = howitzer.getElevation();

       assertEquals(e.radians, 0);
   }

   /*********************************************
    * name:    GET ELEVATION - right
     * input:   h.elevation=0.4
     * output:  e=0.4
    *********************************************/
   void getElevation_right()
   {
       Howitzer howitzer;

       howitzer.elevation.radians = .4;

       Angle e = howitzer.getElevation();

       assertEquals(e.radians, .4);
   }

   /*********************************************
    * name:    GET ELEVATION - left
     * input:   h.elevation=5.8
     * output:  e=5.8
    *********************************************/
   void getElevation_left()
   {
       Howitzer howitzer;

       howitzer.elevation.radians = 5.8;

       Angle e = howitzer.getElevation();

       assertEquals(e.radians, 5.8);
   }

   /*****************************************************************
    *****************************************************************
    * SETTERS
    *****************************************************************
    *****************************************************************/

    /*********************************************
     * name:    GENERATE POSITION small board
     * input:   (10px, 10px)
     * output:  1px <= x <= 9px
     *********************************************/
   void generatePosition_small()
   {
       Howitzer howitzer;
       Position position = Position(10.0, 10.0);

       howitzer.generatePosition(position);

       double howitzer_x = howitzer.position.x;
       assertUnit(1 <= howitzer_x && howitzer_x <= 9);
   }

    /*********************************************
    * name:    GENERATE POSITION large board
    * input:   (1000px, 1000px)
    * output:  100px <= x <= 900px
    *********************************************/
   void generatePosition_large()
   {
       Howitzer howitzer;
       Position position = Position(1000.0, 1000.0);

       howitzer.generatePosition(position);

       double howitzer_x = howitzer.position.x;
       assertUnit(100 <= howitzer_x && howitzer_x <= 900);
   }

   /*********************************************
    * name:    RAISE to the right/down
    * input:   h.elevation=0.5radians  raise(-0.1)
    * output:  h.elevation=0.6radians
    *********************************************/
   void raise_rightDown()
   {
       Howitzer howitzer;

       howitzer.elevation.radians = 0.5;
       howitzer.raise(-0.1);

       assertEquals(howitzer.elevation.radians, 0.6);
   }

   /*********************************************
    * name:    RAISE to the right/up
    * input:   h.elevation=0.5radians  raise(0.1)
    * output:  h.elevation=0.4radians
    *********************************************/
   void raise_rightUp()
   {
       Howitzer howitzer;

       howitzer.elevation.radians = 0.5;
       howitzer.raise(0.1);

       assertEquals(howitzer.elevation.radians, 0.4);
   }

   /*********************************************
    * name:    RAISE to the left down
    * input:   h.elevation=-0.5radians  raise(-0.1)
    * output:  h.elevation=-0.6radians
    *********************************************/
   void raise_leftDown()
   {
       Howitzer howitzer;

       howitzer.elevation.radians = -0.5;
       howitzer.raise(-0.1);

       assertEquals(howitzer.elevation.radians, M_PI * 2 -.6);
   }

   /*********************************************
    * name:    RAISE to the left up
    * input:   h.elevation=-0.5radians  raise(0.1)
    * output:  h.elevation=0.4radians
    *********************************************/
   void raise_leftUp()
   {
       Howitzer howitzer;

       howitzer.elevation.radians = -0.5;
       howitzer.raise(0.1);

       assertEquals(howitzer.elevation.radians, M_PI * 2 - .4);
   }

   /*********************************************
    * name:    ROTATE CLOCKWISE no wrapping
    * input:   h.elevation=1.23 rotate=.3
    * output:  h.elevation=1.53
    *********************************************/
   void rotate_clock()
   {
       Howitzer howitzer;

       howitzer.elevation.radians = 1.23;
       howitzer.rotate(0.3);

       assertEquals(howitzer.elevation.radians, 1.53);
   }

   /*********************************************
    * name:    ROTATE COUNTER CLOCKWISE no wrapping
    * input:   h.elevation=1.23 rotate=-.3
    * output:  h.elevation=0.93
    *********************************************/
   void rotate_counterClock()
   {
       Howitzer howitzer;

       howitzer.elevation.radians = 1.23;
       howitzer.rotate(-0.3);

       assertEquals(howitzer.elevation.radians, .93);
   }

   /*********************************************
    * name:    ROTATE CLOCKWISE CLOCKWISE WRAP BY 2PI
    * input:   h.elevation=6.1 (2pi + -0.1) rotate=.2
    * output:  h.elevation=.1
    *********************************************/
   void rotate_wrapClock()
   {
       Howitzer howitzer;

       howitzer.elevation.radians = 6.1;
       howitzer.rotate(.2);

       assertEquals(howitzer.elevation.radians, 6.3 - (M_PI * 2));
   }

   /*********************************************
    * name:    ROTATE COUNTER CLOCKWISE WRAP BY 4PI
    * input:   h.elevation=0.1 rotate=-.2 - 4PI6
    * output:  h.elevation=6.1 (2pi + -0.1)
    *********************************************/
   void rotate_wrapCounterClock()
   {
       Howitzer howitzer;

       howitzer.elevation.radians = .1;
       howitzer.rotate(-.2 - (M_PI * 4));

       assertEquals(howitzer.elevation.radians, -.1 + (M_PI * 2));
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
      p.metersFromPixels = 1100.0;
   }

   // teardown the standard fixture - reset the zoom to what it was previously
   void teardownStandardFixture()
   {
      assert(metersFromPixels != -1.0);
      Position p;
      p.metersFromPixels = metersFromPixels;
   }
};
