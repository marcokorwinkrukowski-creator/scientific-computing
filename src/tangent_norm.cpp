#include "tangent_norm.h"
#include <cmath>

// Calculate the norm of the first tangent vector
void first_tangent_norm(double mods[nCases], double x[nEquations][nCases])
{
    for (int caseIndex = 0; caseIndex < nCases; caseIndex++)
    {
        mods[caseIndex] = sqrt(x[3][caseIndex] * x[3][caseIndex] + x[4][caseIndex] * x[4][caseIndex] + x[5][caseIndex] * x[5][caseIndex]);
    }
}

// Calculate the norm of the first tangent vector
void second_tangent_norm(double mods[nCases],double x[nEquations][nCases])
{
    for (int caseIndex=0; caseIndex < nCases; caseIndex++)
    {
        mods[caseIndex]=sqrt(x[6][caseIndex] * x[6][caseIndex] + x[7][caseIndex] * x[7][caseIndex] + x[8][caseIndex] * x[8][caseIndex]);
    }
}

// Calculate the norm of the first tangent vector
void third_tangent_norm(double mods[nCases], double x[nEquations][nCases])
{
    for (int caseIndex = 0; caseIndex < nCases; caseIndex++)
    {
    mods[caseIndex] = sqrt(x[9][caseIndex] * x[9][caseIndex] + x[10][caseIndex] * x[10][caseIndex] + x[11][caseIndex] * x[11][caseIndex]);
    }
}
