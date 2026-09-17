#include <cstdlib>
#include <cmath>
#include <fstream>
#include <string>

#include "config.h"
#include "runge_kutta.h"      //Runge-Kutta integration
#include "dynamical_system.h" //System of differential equations that describe the system evolution
#include "tangent_norm.h"      //Norms of tangent vectors
#include "tangent_normalization.h"     //Normalization of tangent vectors
#include "gram_schmidt.h"       //Gram-Schmidt orthogonalization
using namespace std;

// Program for the calculation of the Lyapunov exponents using the Benettin algorithm.

int main ()
{
 
    const double timeStep = 0.001;      //Time step of the Runge-Kutta algorithm

    // Number of parameter cases being integrated: nCases

    double con[nCons][nCases];          //Parameters and control variables
    // con[0] = 1 / Psi = 1 / ( U * k * B)
    // con[1] = F = V / U
    // con[2] = sigma
    // con[3] = flow configuration

    double t = 0;          //Simulation time
    // t = t * U * k 

    // Number of differential equations being integrated: nEquations

    double x[nEquations][nCases];       //State variables (1-3 Equation cases) and tangent vectors (4-12 Equation cases)
    // x[0] = k * x
    // x[1] = k * z
    // x[2] = alpha                      //Angle of rotation of the phytoplancton
    //
    // x[3..5]    first tangent vector
    // x[6..8]    second tangent vector
    // x[9..11]   third tangent vector

    double coef[3][nCases];             // Accumulated logarithmic growth factors
    double mods[nCases];                // Norms of tangent vectors
    double dim;                         // Lyapunov dimension
 
  
    // Set the parameter values for the different cases being integrated (1/Psi = 1/U*k*B)
    con[0][0] = 2;
    con[0][1] = 1.8;
    con[0][2] = 1.6;
    con[0][3] = 1.5;
    con[0][4] = 1.3;
    con[0][5] = 1.25;
    con[0][6] = 1.24;
    con[0][7] = 1.23;
    con[0][8] = 1.20;
    con[0][9] = 1.18;
    con[0][10] = 1.16;
    con[0][11] = 1.14;
    con[0][12] = 1.10;
    con[0][13] = 1;
    con[0][14] = 0.9;

    for (int caseIndex = 0; caseIndex < nCases; caseIndex++)
    {
        con[1][caseIndex]=0.4; // Set constant (F = V/U)
        con[3][caseIndex]=0;   // Set initial flow configuration
    }

    // The system alternates between two flow configurations.
    // Simulation data are saved in the "dati" folder at regular iteration intervals.
    const unsigned long long flowDuration1 = 3000;     // Number of Runge-Kutta algorithm iteration in the first  flow
    const unsigned long long flowDuration2 = 3000;     // Number of Runge-Kutta algorithm iteration in the second flow
    unsigned long long cycleStart = 0;                 // Start of current flow cycle
    const unsigned long long outputInterval = 60000;   // Number of iteration between data output
    unsigned long long lastOutput= 0;                  // Iteration of last data outpur

    // Set the initial conditions of the system.
    const unsigned int seed = 12;
    srand(seed);
    srand48(seed);
  
    x[0][0] = 2 * M_PI * drand48();
    x[1][0] = 2 * M_PI * drand48();
    x[2][0] = 2 * M_PI * drand48();

    con[2][0] = 2 * M_PI * drand48(); 

    // Ensure that the initial position lies within the interval [0, 2π].
    while(x[0][0] < 0)
	{
        x[0][0] = x[0][0] + 2 * M_PI;
	}
  
    while(x[1][0] < 0)
    {
        x[1][0] = x[1][0] + 2 * M_PI;
    }
  
    while(x[0][0] > 2 * M_PI)
    {
	    x[0][0] = x[0][0] - 2 * M_PI;
    }
      
    while(x[1][0] > 2 * M_PI)
    {
        x[1][0] = x[1][0] - 2 * M_PI;
    }
    // Use the same initial physical state for all parameter cases.
    for (int caseIndex = 1;  caseIndex < nCases; caseIndex++)
    {
        x[0][caseIndex] = x[0][0];
        x[1][caseIndex] = x[1][0];
        x[2][caseIndex] = x[2][0];
    }  
  
    // Set random values for the tangent vectors
    x[3][0] = (rand() % 100) + 1;
    x[4][0] = (rand() % 100) + 1;
    x[5][0] = (rand() % 100) + 1;
  
    x[6][0] = (rand() % 100) + 1;
    x[7][0] = (rand() % 100) + 1;
    x[8][0] = (rand() % 100) + 1;
  
    x[9][0] = (rand() % 100) + 1;
    x[10][0] = (rand() % 100) + 1;
    x[11][0] = (rand() % 100) + 1;

    // Copy the initial state and tangent vectors to all parameter cases. 
    for (int caseIndex = 1; caseIndex < nCases; caseIndex++)
    {
        for (int eNumber = 0; eNumber < nEquations; eNumber++)
        {
            x[eNumber][caseIndex]=x[eNumber][0];
        }   
    } 
  
    // Initialize the accumulators for the Lyapunov exponents.
    for (int caseIndex = 0; caseIndex < nCases; caseIndex++)
    {
        coef[0][caseIndex]=0;
        coef[1][caseIndex]=0;
        coef[2][caseIndex]=0;
    }
  

    // Open the output file in the "dati" directory.
    ofstream outfile;

    double psi;

    // Write the header for the first group of parameter cases.
    outfile.open( std::string(outputDirectory) + "lyapunov_exponents_group1.dat", std::ofstream::out | std::ofstream::app);  
    for (int caseIndex = 0; caseIndex < 4; caseIndex++)
    {
        psi = 1 / con[0][caseIndex];
        outfile << " esp1   esp2   esp3  PSI:" << psi;	    
    }
    outfile << endl;
	outfile.close();

    // Write the header for the second group of parameter cases.
    outfile.open(std::string(outputDirectory) + "lyapunov_exponents_group2.dat", std::ofstream::out | std::ofstream::app);
    for (int caseIndex = 4; caseIndex < 8; caseIndex++)
    {
        psi = 1 / con[0][caseIndex];
	    outfile << " esp1   esp2   esp3  PSI:" << psi;	    
    }
    outfile << endl;
	outfile.close();

    // Write the header for the third group of parameter cases.
    outfile.open(std::string(outputDirectory) + "lyapunov_exponents_group3.dat",std::ofstream::out | std::ofstream::app);
    for (int caseIndex = 8; caseIndex < 12; caseIndex++)
    {
        psi = 1 / con[0][caseIndex];
	    outfile << " esp1   esp2   esp3  PSI:" << psi;	    
    }
    outfile << endl;
	outfile.close();

    // Write the header for the fourth group of parameter cases.
    outfile.open(std::string(outputDirectory) + "lyapunov_exponents_group4.dat",std::ofstream::out | std::ofstream::app);
    for (int caseIndex = 12; caseIndex < nCases; caseIndex++)
    {
        psi = 1 / con[0][caseIndex];
	    outfile << " esp1   esp2   esp3  PSI:" << psi;	    
    }
    outfile <<" t "<< endl;
	outfile.close();

    // Write the header for the Lyapunov dimensions.
    outfile.open(std::string(outputDirectory) + "lyapunov_dimension.dat",std::ofstream::out | std::ofstream::app);
    for (int caseIndex = 0; caseIndex < nCases; caseIndex++)
    {
        psi = 1 / con[0][caseIndex];
	    outfile<<" p:"<<psi;	    
    }
    outfile <<" t "<< endl;
	outfile.close();

    // Main simulation loop. The program runs indefinitely to monitor convergence.
    for (unsigned long long iterationCount = 0;  true; iterationCount++)
    {       
        // Orthogonalize the tangent vectors using Gram-Schmidt.
        // on the second tangent vector (x[6], x[7], x[8])
        orthogonalize_second_tangent(x); 
        // on the third tangent vector (x[9], x[10], x[11])
        orthogonalize_third_tangent(x);

        // Normalize the tangent vectors.
        // on first tangent vector (x[3], x[4], x[5])
        normalize_first_tangent(x);
        // on the second tangent vector (x[6], x[7], x[8])
        normalize_second_tangent(x);
        // on the third tangent vector (x[9], x[10], x[11])
        normalize_third_tangent(x);

        // Advance the system by one Runge-Kutta time step.
        runge_kutta_step(compute_derivatives, t, x, timeStep, con);

        // Keep the position variables within the interval [0, 2π].
        for (int caseIndex = 0; caseIndex < nCases; caseIndex++)
        {
            while(x[0][caseIndex] < 0)
	        {
	            x[0][caseIndex] = x[0][caseIndex] + 2 * M_PI;
	        }
            while(x[1][caseIndex] < 0)
	        {
	            x[1][caseIndex] = x[1][caseIndex] + 2 * M_PI;
	        }
            while(x[0][caseIndex] > 2 * M_PI)
	        {
	            x[0][caseIndex] = x[0][caseIndex] - 2 * M_PI;
	        }
            while(x[1][caseIndex] > 2 * M_PI)
	        {
	            x[1][caseIndex] = x[1][caseIndex] - 2 * M_PI;
	        }
        }  

        // Calculate and accumulate the logarithmic growth of the tangent vectors. 
        first_tangent_norm(mods, x);
        for (int caseIndex = 0; caseIndex < nCases; caseIndex++)
        {
            coef[0][caseIndex] += log(mods[caseIndex]);
        }

        second_tangent_norm(mods, x);
        for (int caseIndex = 0; caseIndex < nCases; caseIndex++)
        {
            coef[1][caseIndex] += log(mods[caseIndex]);      
        }

        third_tangent_norm(mods,x);
        for (int caseIndex = 0; caseIndex < nCases; caseIndex++)
        {
            coef[2][caseIndex] += log(mods[caseIndex]);
        }        
         
        // Save the current Lyapunov exponents and Lyapunov dimension
        // every outputInterval iterations.
        if(iterationCount == lastOutput + outputInterval)
	    {
	        lastOutput = lastOutput + outputInterval;
    	    outfile.open(std::string(outputDirectory) + "lyapunov_exponents_group1.dat",std::ofstream::out | std::ofstream::app);
	        for (int caseIndex = 0; caseIndex < 4; caseIndex++)
                {
	                outfile << coef[0][caseIndex] / t << "  " << coef[1][caseIndex] / t << "  " << coef[2][caseIndex] / t << "  ";
                }
            outfile<<endl;	    
	        outfile.close();
            
            outfile.open(std::string(outputDirectory) + "lyapunov_exponents_group2.dat",std::ofstream::out | std::ofstream::app);
	        for (int caseIndex = 4; caseIndex < 8; caseIndex++)
            {
	            outfile << coef[0][caseIndex] / t << "  " << coef[1][caseIndex] / t << "  " << coef[2][caseIndex] / t << "  ";
            }
            outfile<<endl;	    
	        outfile.close();
           
            outfile.open(std::string(outputDirectory) + "lyapunov_exponents_group3.dat",std::ofstream::out | std::ofstream::app);
	        for (int caseIndex = 8; caseIndex < 12; caseIndex++)
            {
	            outfile << coef[0][caseIndex] / t << "  " << coef[1][caseIndex] / t << "  " << coef[2][caseIndex] / t << "  ";
            }
            outfile<<endl;	    
	        outfile.close();
            
            outfile.open(std::string(outputDirectory) + "lyapunov_exponents_group4.dat", std::ofstream::out | std::ofstream::app);
	        for (int caseIndex = 12; caseIndex < nCases; caseIndex++)
            {
	            outfile<<coef[0][caseIndex] / t << "  " << coef[1][caseIndex] / t << "  " << coef[2][caseIndex] / t << "  ";
            }
            outfile<<t<<endl;	    
	        outfile.close();
            
            outfile.open(std::string(outputDirectory) + "lyapunov_dimension.dat", std::ofstream::out | std::ofstream::app);
            // Calculate the Lyapunov dimension for each parameter case.
            for (int caseIndex = 0; caseIndex < nCases; caseIndex++)             
            {
                if (coef[0][caseIndex] + coef[1][caseIndex] >= 0)
                {
                    dim = 2 + (coef[0][caseIndex] + coef[1][caseIndex]) / (-coef[2][caseIndex]);
                }
                else 
                {
                    dim = 1 + (coef[0][caseIndex]) / (-coef[1][caseIndex]);
                }
	            
	            outfile<<dim<<"  ";
            }
            outfile<<endl;	    
	        outfile.close();
        } 

        // Switch from flow configuration 0 to flow configuration 1.
        if (iterationCount == cycleStart + flowDuration1 && con[3][0] == 0)
	    {
	        con[2][0] = 2 * M_PI * drand48(); //here we change randomly our sigma (phase)
	        con[3][0] = 1;
	    }  
        // Switch from flow configuration 1 to flow configuration 0
        // and start a new flow cycle.
        if (iterationCount == cycleStart + flowDuration1 + flowDuration2 && con[3][0] == 1)
	    {
	        con[2][0] = 2 * M_PI * drand48(); //here we change randomly our sigma (phase)	
	        con[3][0] = 0;	
	        cycleStart = cycleStart + flowDuration1 + flowDuration2;
	    } 
 
    }


  
  
  return 0;
}

