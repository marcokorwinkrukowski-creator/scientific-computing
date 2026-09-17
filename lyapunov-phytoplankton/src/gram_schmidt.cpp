#include "tangent_norm.h"
#include "gram_schmidt.h"

// Apply the Gram-Schmidt orthogonalization process to the second tangent vector with respect to the first tangent vector.
//
// The tangent vectors are:
// first tangent vector (x[3], x[4], x[5])
// second tangent vector (x[6], x[7], x[8])
// third tangent vector (x[9], x[10], x[11])

void orthogonalize_second_tangent(double x[nEquations][nCases])
{
    // Calculate first tangent vector norms.
    double mods[nCases];
    first_tangent_norm(mods, x);

    for (int caseIndex = 0; caseIndex < nCases; caseIndex++)
    {
        double projectionCoefficient = (x[6][caseIndex] * x[3][caseIndex] + x[7][caseIndex] * x[4][caseIndex] + x[8][caseIndex] * x[5][caseIndex]) / (mods[caseIndex] * mods[caseIndex]);

        x[6][caseIndex] = x[6][caseIndex] - x[3][caseIndex] * projectionCoefficient;
        x[7][caseIndex] = x[7][caseIndex] - x[4][caseIndex] * projectionCoefficient;
        x[8][caseIndex] = x[8][caseIndex] - x[5][caseIndex] * projectionCoefficient;
    }
}
// Apply the Gram-Schmidt orthogonalization process to the third tangent vector with respect to the first and second tangent vectors both previously orthogonalized
void orthogonalize_third_tangent(double x[nEquations][nCases])
{
    // Calculate first and second tangent vector norms.
    double mods1[nCases];
    double mods2[nCases];
    first_tangent_norm(mods1, x);
    second_tangent_norm(mods2, x);

    for (int caseIndex = 0; caseIndex < nCases; caseIndex++)
    { 
        double projectionCoefficient1 = (x[9][caseIndex] * x[3][caseIndex] + x[10][caseIndex] * x[4][caseIndex] + x[11][caseIndex] * x[5][caseIndex]) / (mods1[caseIndex] * mods1[caseIndex]);
        double projectionCoefficient2 = (x[9][caseIndex] * x[6][caseIndex] + x[10][caseIndex] * x[7][caseIndex] + x[11][caseIndex] * x[8][caseIndex]) / (mods2[caseIndex] * mods2[caseIndex]);

        x[9][caseIndex] = x[9][caseIndex] - x[3][caseIndex] * projectionCoefficient1 - x[6][caseIndex] * projectionCoefficient2;
        x[10][caseIndex] = x[10][caseIndex] - x[4][caseIndex] * projectionCoefficient1 - x[7][caseIndex]*projectionCoefficient2;
        x[11][caseIndex] = x[11][caseIndex]- x[5][caseIndex] * projectionCoefficient1 - x[8][caseIndex]*projectionCoefficient2;
    }
}
 
