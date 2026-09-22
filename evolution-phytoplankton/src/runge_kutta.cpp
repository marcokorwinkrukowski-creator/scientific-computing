#include "runge_kutta.h"

void runge_kutta(void (*compute_derivatives)(double t,double x[NEQ],double dx[NEQ],double con[NCON]),double &simulationTime, double x[NEQ][NPART], double timeStep,double con[NCON])
{
 
    double fk1[NEQ], fk2[NEQ], fk3[NEQ], fk4[NEQ];
    double  xt[NEQ],  dx[NEQ];
    int equation;
    double halfStep = timeStep / 2.;

    for (int particle = 0; particle < NPART; particle++)
    {   
        for (equation = 0; equation < NEQ; equation++)
        {
            xt[equation] = x[equation][particle];
        }

        compute_derivatives(simulationTime, xt, dx, con);
        for (equation = 0; equation < NEQ; equation++)
        {
            fk1[equation] = timeStep * dx[equation];
            xt[equation] = x[equation][particle] + fk1[equation] * 0.5;
        }

        compute_derivatives(simulationTime + halfStep, xt, dx, con);
        for (equation = 0; equation < NEQ; equation++)
        {
            fk2[equation] = timeStep * dx[equation];
            xt[equation] = x[equation][particle] + fk2[equation] * 0.5 ;
        }

        compute_derivatives(simulationTime + halfStep, xt, dx, con);
        for (equation = 0; equation < NEQ; equation++)
        {
            fk3[equation] = timeStep * dx[equation];
            xt[equation] = x[equation][particle] + fk3[equation];
        }

        compute_derivatives(simulationTime + timeStep, xt, dx, con);
        for (equation = 0; equation < NEQ; equation++)
        {   
            fk4[equation] = timeStep * dx[equation];
            x[equation][particle] = x[equation][particle] + (fk1[equation] + 2. * fk2[equation] + 2. * fk3[equation] + fk4[equation]) / 6.;
        }
    }

    simulationTime = simulationTime + timeStep;

}
