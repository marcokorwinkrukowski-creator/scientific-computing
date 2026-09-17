#include "tangent_norm.h"
#include "tangent_normalization.h"

// Normalize the first tangent vector
void normalize_first_tangent(double x[nEquations][nCases])
{
    // Calculate the tangent vector norm
    double mods[nCases];
    first_tangent_norm(mods, x);
    for (int caseIndex = 0; caseIndex < nCases; caseIndex++)
    {
        x[3][caseIndex] = x[3][caseIndex] / mods[caseIndex];
        x[4][caseIndex] = x[4][caseIndex] / mods[caseIndex];
        x[5][caseIndex] = x[5][caseIndex] / mods[caseIndex];
    }
}

// Normalize the second tangent vector
void normalize_second_tangent(double x[nEquations][nCases])
{
    // Calculate the tangent vector norm
    double mods[nCases];
    second_tangent_norm(mods, x);
    for (int caseIndex = 0; caseIndex < nCases; caseIndex++)
    {
        
        x[6][caseIndex] = x[6][caseIndex] / mods[caseIndex];
        x[7][caseIndex] = x[7][caseIndex] / mods[caseIndex];
        x[8][caseIndex] = x[8][caseIndex] / mods[caseIndex];
    }
}

// Normalize the third tangent vector
void normalize_third_tangent(double x[nEquations][nCases])
{
    // Calculate the tangent vector norm
    double mods[nCases];
    third_tangent_norm(mods, x);

    for (int caseIndex = 0; caseIndex < nCases; caseIndex++)
    {
        x[9][caseIndex] = x[9][caseIndex] / mods[caseIndex];
        x[10][caseIndex] = x[10][caseIndex] / mods[caseIndex];
        x[11][caseIndex] = x[11][caseIndex] / mods[caseIndex];
    }
}
