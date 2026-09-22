#include <cstdlib>
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>

#include "runge_kutta.h"
#include "dynamical_system.h"



using namespace std;

int main ()
{

    double timeStep = 0.001;
    double x[NEQ][NPART];
    double con[NCON];
    double simulationTime = 0;
    long long maxIterations = 40000;
 

    // con[0] = 1/Psi = 1/U*k*B
    // con[1] = F = V/U
    // con[2] = sigma
    // x[0] = k*x
    // x[1] = k*z
    // x[2] = alfa
    // simulationTime = t*U*k


    // con[0] = 1 / Psi = 1 / (U * k * B)
    // con[1] = F = V / U
    // con[2] = sigma
    // con[3] = flow configuration
    con[0] = 1.25;
    con[1] = 0.4;
    con[3] = 0;


    const unsigned long long flowDuration1 = 3000;     // Number of Runge-Kutta algorithm iteration in the first  flow
    const unsigned long long flowDuration2 = 3000;     // Number of Runge-Kutta algorithm iteration in the second flow
    unsigned long long cycleStart = 0;                 // Start of current flow cycle
 
    double outputInterval = 3;
    double nextOutputTime = outputInterval;
    const int seed = 12;
    //devo determinare vettore z0 random di valore unitario
    srand(seed);
    srand48(seed);

    con[2] = 2 * M_PI * drand48();
	
    for(int particle = 0; particle < NPART; particle++)
    {    
        x[0][particle] = 2 * M_PI * drand48();
        x[1][particle] = 2 * M_PI * drand48();
        x[2][particle] = 2 * M_PI * drand48();
   
        while(x[0][particle] < 0)
	    {
	        x[0][particle] = x[0][particle] + 2 * M_PI;
	    }
      
        while(x[1][particle] < 0)
	    {
	        x[1][particle] = x[1][particle] + 2 * M_PI;
	    }
      
        while(x[0][particle] > 2 * M_PI)
	    {
	        x[0][particle] = x[0][particle] - 2 * M_PI;
	    }
      
        while(x[1][particle] > 2 * M_PI)
	    {
            x[1][particle] = x[1][particle] - 2 * M_PI;
	    }
      
    }

    ofstream outfile;
    outfile.open("results/starting_configuration");

	for(int particle = 0; particle < NPART; particle++)
    {    
        outfile << x[0][particle] << "  " << x[1][particle] << '\n';	    
    }

	outfile.close();
    int outputNumber = 1;

    for (unsigned long long iterationCount = 0; maxIterations < 0 || iterationCount < static_cast<unsigned long long>(maxIterations); iterationCount++)
    {   

        runge_kutta(compute_derivatives, simulationTime, x, timeStep, con);

        for(int particle = 0; particle < NPART; particle++)
	    {    

	        while(x[0][particle] < 0)
	        {
	            x[0][particle] = x[0][particle] + 2 * M_PI;
            }
	  
            while(x[1][particle] < 0)
	        {
                x[1][particle] = x[1][particle] + 2 * M_PI;
            }
	  
            while(x[0][particle]>2*M_PI)
            {
	            x[0][particle] = x[0][particle] - 2 * M_PI;
            }
	  
            while(x[1][particle]>2*M_PI)
            {
                x[1][particle] = x[1][particle] - 2 * M_PI;
            }

        }



        // Switch from flow configuration 0 to flow configuration 1.
        if (iterationCount == cycleStart + flowDuration1 && con[3] == 0)
        {
            con[2] = 2 * M_PI * drand48(); //here we change randomly our sigma (phase)
            con[3] = 1;
        }  
        // Switch from flow configuration 1 to flow configuration 0
        // and start a new flow cycle.
        if (iterationCount == cycleStart + flowDuration1 + flowDuration2 && con[3] == 1)
	    {
	        con[2] = 2 * M_PI * drand48(); //here we change randomly our sigma (phase)	
	        con[3] = 0;	
	        cycleStart = cycleStart + flowDuration1 + flowDuration2;
	    } 


        if(simulationTime > nextOutputTime)
        {
            nextOutputTime = nextOutputTime + outputInterval;
            std::string outputFileName = std::to_string(outputNumber);

	        outputNumber++;

            ofstream outfile;
	        outputFileName = "results/data_file_" + outputFileName;
            outfile.open(outputFileName);
	  
            for(int particle = 0; particle < NPART; particle++)
	        {    
	            outfile << x[0][particle] << "  " << x[1][particle] << '\n';	    
	        }

            cout << outputFileName << " completed" << endl; 
            outfile.close();
	  
	    }      
    }

return 0;
}

