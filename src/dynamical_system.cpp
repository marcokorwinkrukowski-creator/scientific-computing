#include "dynamical_system.h"
#include <cmath>

void compute_derivatives(double t,double x[][15],double dx[][15],double con[][15],int caseIndex)
{

    // Compute the derivatives of the particle state and of the three tangent vectors.
    //
    // The first three components of x describe the particle state, the equations are written in dimensionless variables:
    //   x[0] = k * x
    //   x[1] = k * yThe corresponding dimensionless evolution equations are:
    //   x[2] = alpha
    //
    // Time is also dimensionless
    // t = t * U * k
    //
    // Components 3-5, 6-8 and 9-11 contain three tangent vectors.
    //
    // The parameter array con contains:
    //   con[0] = 1/Psi = 1/(U*k*B)
    //   con[1] = F    = V/U
    //   con[2] = sigma
    // Two alternating flow configurations are implemented.
    //   con[3] = flow configuration switch
    //
    // caseIndex = index of the parameter case with a given value of Psi



    double oneOverPsi = con[0][caseIndex];
    double F = con[1][caseIndex];
    double sigma = con[2][0];
    int flowSwitch = con[3][0];

    if (flowSwitch == 1)
    {
         // Flow configuration 1      
         double phase = x[1][caseIndex] + sigma; 
         double alpha = x[2][caseIndex];

         double sinPhase = sin(phase);
         double cosPhase = cos(phase);

         double sinAlpha = sin(alpha);
         double cosAlpha = cos(alpha);
      
         // Physical state equations
         dx[0][caseIndex] = cosPhase + F * cosAlpha;
         dx[1][caseIndex] = F * sinAlpha;
         dx[2][caseIndex] = (oneOverPsi * cosAlpha - sinPhase) / 2;
      
         // Variational equations for the tangent vectors
         dx[3][caseIndex] = -sinPhase * x[4][caseIndex] - F * sinAlpha * x[5][caseIndex];
         dx[4][caseIndex] = F * cosAlpha * x[5][caseIndex];
         dx[5][caseIndex] = -(oneOverPsi * sinAlpha * x[5][caseIndex] + cosPhase * x[4][caseIndex]) / 2;
      
         dx[6][caseIndex] = -sinPhase * x[7][caseIndex] - F * sinAlpha * x[8][caseIndex];
         dx[7][caseIndex] = F * cosAlpha * x[8][caseIndex];
         dx[8][caseIndex] = -(oneOverPsi * sinAlpha * x[8][caseIndex] + cosPhase * x[7][caseIndex]) / 2;
      
      
         dx[9][caseIndex] = -sinPhase * x[10][caseIndex] - F * sinAlpha * x[11][caseIndex];
         dx[10][caseIndex] = F * cosAlpha * x[11][caseIndex];
         dx[11][caseIndex] = -(oneOverPsi * sinAlpha * x[11][caseIndex] + cosPhase * x[10][caseIndex]) / 2;
            
    }	
    else
    {
         // Flow configuration 2
         double phase = x[0][caseIndex] + sigma; 
         double alpha = x[2][caseIndex];

         double sinPhase = sin(phase);
         double cosPhase = cos(phase);

         double sinAlpha = sin(alpha);
         double cosAlpha = cos(alpha);
       
         // Physical state equations
         dx[0][caseIndex] = F * cosAlpha;
         dx[1][caseIndex] = cosPhase + F * sinAlpha;
         dx[2][caseIndex] = (oneOverPsi * cosAlpha - sinPhase) / 2;	
      
         // Variational equations for the tangent vectors
   	     dx[3][caseIndex] = -F * sinAlpha * x[5][caseIndex];
   	     dx[4][caseIndex] = -sinPhase * x[3][caseIndex] + F * cosAlpha * x[5][caseIndex];
         dx[5][caseIndex] = -(oneOverPsi * sinAlpha * x[5][caseIndex] + cosPhase * x[3][caseIndex]) / 2;

         dx[6][caseIndex] = -F * sinAlpha * x[8][caseIndex];
         dx[7][caseIndex] = -sinPhase * x[6][caseIndex] + F * cosAlpha * x[8][caseIndex];
         dx[8][caseIndex] = -(oneOverPsi * sinAlpha * x[8][caseIndex] + cosPhase * x[6][caseIndex]) / 2;

         dx[9][caseIndex] = -F * sinAlpha * x[11][caseIndex];
         dx[10][caseIndex] = -sinPhase * x[9][caseIndex] + F * cosAlpha * x[11][caseIndex];
	     dx[11][caseIndex] = -(oneOverPsi * sinAlpha * x[11][caseIndex] + cosPhase * x[9][caseIndex]) / 2;
	
    }
 
}
