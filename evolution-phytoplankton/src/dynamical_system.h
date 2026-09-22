#ifndef DSYS_H
#define DSYS_H

#include "config.h"

void compute_derivatives(double simulationTime, double x[NEQ], double dx[NEQ], double con[NCON]);

#endif
