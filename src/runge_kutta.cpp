#include "runge_kutta.h"

// Fourth-order Runge-Kutta algorithm
void runge_kutta_step(void (*fun)(double t,double x[nEquations ][nCases],double dx[nEquations][nCases],double con[nCons][nCases],int caseIndex),double &t, double x[nEquations ][nCases], double timeStep,double con[nCons][nCases])
{
    double fk1[nEquations], fk2[nEquations], fk3[nEquations], fk4[nEquations];
    double  xt[nEquations][nCases],  dx[nEquations][nCases];
    int equation;

    double halfStep = timeStep / 2.0;

    for (int caseIndex = 0; caseIndex < nCases; caseIndex++)
    {
       fun(t, x, dx, con, caseIndex);
       for (equation = 0; equation < nEquations; equation++)
       {
           fk1[equation] = timeStep * dx[equation][caseIndex];
           xt[equation][caseIndex] = x[equation][caseIndex] + fk1[equation] * 0.5;
       }

       fun(t + halfStep, xt, dx, con, caseIndex);
       for (equation = 0; equation < nEquations; equation++)
       {
           fk2[equation] = timeStep * dx[equation][caseIndex];
           xt[equation][caseIndex] = x[equation][caseIndex] + fk2[equation] * 0.5;
       }

       fun(t + halfStep, xt, dx, con, caseIndex);
       for (equation = 0; equation < nEquations; equation++)
       {
           fk3[equation] = timeStep * dx[equation][caseIndex];
           xt[equation][caseIndex] = x[equation][caseIndex] + fk3[equation];
       }

       fun(t + timeStep, xt, dx, con, caseIndex);
       for (equation = 0; equation < nEquations; equation++)
       {   
           fk4[equation] = timeStep * dx[equation][caseIndex];
           x[equation][caseIndex] = x[equation][caseIndex] + (fk1[equation] + 2.0 * fk2[equation] + 2.0 * fk3[equation] + fk4[equation]) / 6.0;
       }
    }
    t = t + timeStep;

}
