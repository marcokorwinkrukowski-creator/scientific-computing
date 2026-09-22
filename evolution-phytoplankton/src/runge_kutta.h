#ifndef RGK_H
#define RGK_H

#include "config.h"

void runge_kutta(void (*compute_derivatives)(double simulationTime, double x[NEQ], double dx[NEQ], double con[NCON]), double &simulationTime, double x[NEQ][NPART], double timeStep, double con[NCON]);

#endif
