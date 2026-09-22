#include "dynamical_system.h"
#include <cmath>

void compute_derivatives(double /*t*/ ,double x[NEQ],double dx[NEQ],double con[NCON])
{
    // Compute the derivatives of the particle state.
    //
    // The first three components of x describe the particle state, the equations are written in dimensionless variables:
    //   x[0] = k * x
    //   x[1] = k * y The corresponding dimensionless evolution equations are:
    //   x[2] = alpha
    //
    // Time is also dimensionless
    // t = t * U * k
    //
    // The parameter array con contains:
    //   con[0] = 1/Psi = 1/(U*k*B)
    //   con[1] = F    = V/U
    //   con[2] = sigma
    // Two alternating flow configurations are implemented.
    //   con[3] = flow configuration switch


    double oneOverPsi = con[0];
    double F = con[1];
    double sigma = con[2];
    int flowSwitch = con[3];

    if (flowSwitch == 1)
    {
         // Flow configuration 1      
         double phase = x[1] + sigma; 
         double alpha = x[2];

         double sinPhase = sin(phase);
         double cosPhase = cos(phase);

         double sinAlpha = sin(alpha);
         double cosAlpha = cos(alpha);
      
         // Physical state equations
         dx[0] = cosPhase + F * cosAlpha;
         dx[1] = F * sinAlpha;
         dx[2] = (oneOverPsi * cosAlpha - sinPhase) / 2;
            
    }	
    else
    {
         // Flow configuration 2
         double phase = x[0] + sigma; 
         double alpha = x[2];

         double sinPhase = sin(phase);
         double cosPhase = cos(phase);

         double sinAlpha = sin(alpha);
         double cosAlpha = cos(alpha);
       
         // Physical state equations
         dx[0] = F * cosAlpha;
         dx[1] = cosPhase + F * sinAlpha;
         dx[2] = (oneOverPsi * cosAlpha - sinPhase) / 2;	
	
    }
}


