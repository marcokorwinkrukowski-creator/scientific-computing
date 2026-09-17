#ifndef MOD_H
#define MOD_H

#include "config.h"

void first_tangent_norm(double mods[nCases], double x[nEquations][nCases]);

void second_tangent_norm(double mods[nCases], double x[nEquations][nCases]);

void third_tangent_norm(double mods[nCases], double x[nEquations][nCases]);

#endif
