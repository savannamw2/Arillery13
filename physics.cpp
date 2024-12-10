/***********************************************************************
 * Source File:
 *    PHYSICS
 * Author:
 *    <your name here>
 * Summary:
 *    Laws of motion, effects of gravity, wind resistence, etc.
 ************************************************************************/
  
 #include "physics.h"  // for the prototypes
 
 /*********************************************************
 * LINEAR INTERPOLATION
 * From a list of domains and ranges, linear interpolate
 *********************************************************/
double linearInterpolation(const Mapping mapping[], int numMapping, double domain)
{
   if (domain < mapping[0].domain)
       return mapping[0].range;
    
    for (int i = 0; i < numMapping - 1; i++)
    {
        if (mapping[i + 0].domain <= domain && domain <= mapping[i + 1].domain)
            return linearInterpolation(mapping[i + 0], mapping[i + 1], domain);
    }
    
    return mapping[numMapping - 1].range;
}

/*********************************************************
 * GRAVITY FROM ALTITUDE
 * Determine gravity coefficient based on the altitude
 *********************************************************/
double gravityFromAltitude(double altitude)
{
    const Mapping gravityMapping[] =
    {
        {0, 9.807},
        {1000, 9.804},
        {2000, 9.801},
        {3000, 9.797},
        {4000, 9.794},
        {5000, 9.791},
        {6000, 9.788},
        {7000, 9.785},
        {8000, 9.782},
        {9000, 9.779},
        {10000, 9.776},
        {15000, 9.761},
        {20000, 9.745},
        {25000, 9.730},
        {30000, 9.715},
        {40000, 9.684},
        {50000, 9.654},
        {60000, 9.624},
        {70000, 9.594},
        {80000, 9.564}
    };
    
    double gravity = linearInterpolation(gravityMapping, sizeof(gravityMapping) / sizeof(gravityMapping[0]), altitude);
    
    return gravity;
}

/*********************************************************
 * DENSITY FROM ALTITUDE
 * Determine the density of air based on the altitude
 *********************************************************/
double densityFromAltitude(double altitude)
{
    const Mapping densityMapping[] =
    {
        {0, 1.225},
        {1000, 1.112},
        {2000, 1.007},
        {3000, 0.9093},
        {4000, 0.8194},
        {5000, 0.7364},
        {6000, 0.6601},
        {7000, 0.5900},
        {8000, 0.5258},
        {9000, 0.4671},
        {10000, 0.4135},
        {15000, 0.1948},
        {20000, 0.08891},
        {25000, 0.04008},
        {30000, 0.01841},
        {40000, 0.003996},
        {50000, 0.001027},
        {60000, 0.00030977},
        {70000, 0.00008288},
        {80000, 0.0000185}
    };
    
    double density = linearInterpolation(densityMapping, sizeof(densityMapping) / sizeof(densityMapping[0]), altitude);
    
    return density;

}

/*********************************************************
 * SPEED OF SOUND FROM ALTITUDE
 * determine the speed of sound for a given altitude.
 ********************************************************/
double speedSoundFromAltitude(double altitude)
{
    const Mapping machMapping[] =
    {
        {0, 340},
        {1000, 336},
        {2000, 332},
        {3000, 328},
        {4000, 324},
        {5000, 320},
        {6000, 316},
        {7000, 312},
        {8000, 308},
        {9000, 303},
        {10000, 299},
        {15000, 295},
        {20000, 295},
        {25000, 295},
        {30000, 305},
        {40000, 324},
        {50000, 337},
        {60000, 319},
        {70000, 289},
        {80000, 269}
    };
    
    double mach = linearInterpolation(machMapping, sizeof(machMapping) / sizeof(machMapping[0]), altitude);
    
    return mach;
}


/*********************************************************
 * DRAG FROM MACH
 * Determine the drag coefficient for a M795 shell given speed in Mach
 *********************************************************/
double dragFromMach(double speedMach)
{
    const Mapping dragMapping[] =
    {
        {0.0, 0.0},
        {0.30, 0.1629},
        {0.50, 0.1659},
        {0.70, 0.2031},
        {0.89, 0.2597},
        {0.92, 0.3010},
        {0.96, 0.3287},
        {0.98, 0.4002},
        {1.00, 0.4258},
        {1.02, 0.4335},
        {1.06, 0.4483},
        {1.24, 0.4064},
        {1.53, 0.3663},
        {1.99, 0.2897},
        {2.87, 0.2297},
        {2.89, 0.2306},
        {5.00, 0.2656}
    };
    
    double drag = linearInterpolation(dragMapping, sizeof(dragMapping) / sizeof(dragMapping[0]), speedMach);
    
    return drag;
}

