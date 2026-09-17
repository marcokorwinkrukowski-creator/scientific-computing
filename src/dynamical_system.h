#ifndef FUNZIONE_H
#define FUNZIONE_H

#include "config.h"

void compute_derivatives(double t,
       double x[nEquations][nCases],
       double dx[nEquations][nCases],
       double con[nEquations][nCases],
       int caseIndex);

#endif
