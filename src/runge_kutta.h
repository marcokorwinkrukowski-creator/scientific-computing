#ifndef RGK_H
#define RGK_H

#include "config.h"

void runge_kutta_step(void (*fun)(double t,double x[nEquations][nCases],double dx[nEquations][nCases],double con[nCons][nCases],int caseIndex),
         double &t, 
         double x[nEquations][nCases], 
         double timeStep,
         double con[nCons][nCases]);

#endif
