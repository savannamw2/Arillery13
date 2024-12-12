/***********************************************************************
 * Source File:
 *    PROJECTILE
 * Author:
 *    Savanna Whittaker & Alexandra Green
 * Summary:
 *    Everything we need to know about a projectile
 ************************************************************************/


 #include "projectile.h"
 #include "angle.h"
 using namespace std;

void Projectile::advance(double simulationTime, int &age)
 {
     if (flightPath.empty())
         return;
     
     PositionVelocityTime pvt = flightPath.back();
     
     double speed = pvt.v.getSpeed();
     double altitude = pvt.pos.getMetersY();
     double interval = simulationTime - currentTime();
     
     double density = densityFromAltitude(altitude);
     double speedOfSound = speedSoundFromAltitude(altitude);
     double mach = speed / speedOfSound;
     
     double dragCoef = dragFromMach(mach);
     double windResist = forceFromDrag(density, dragCoef, radius, speed);
     double magWind = accelerationFromForce(windResist, mass);
     
     Acceleration aWind(-pvt.v.getAngle(), magWind);
     
     double magGravity = gravityFromAltitude(altitude);
     
     Angle angleGravity;
     angleGravity.setDown();
     Acceleration aGravity(angleGravity, magGravity);
     
     Acceleration aTotal = aGravity + aWind;
     
     pvt.pos.add(aTotal, pvt.v, interval);
     pvt.v.add(aTotal, interval);
     pvt.t = simulationTime;
    
    age++; 
     
     flightPath.push_back(pvt);
 }

 void Projectile::fire(const Position &posHowitzer, double simulationTime, const Angle &elevation,
                       double muzzleVelocity)
{
     PositionVelocityTime pvt;
     pvt.pos = posHowitzer;
     pvt.t = simulationTime;
     pvt.v.set(elevation, muzzleVelocity);
     flightPath.push_back(pvt);
     
}
