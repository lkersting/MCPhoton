//---------------------------------------------------------------------------//
//!
//! \file   AzimuthalRej.cpp
//! \author Luke Kersting
//! \brief  Azimuthal angle rejection sampling
//!
//---------------------------------------------------------------------------//

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

void AzRej( double (&sin_az),
			double (&cos_az)	)
{
	// Random numbers used for sampling
	double rnd1, rnd2;

	// Points for sampling the azimuthal scattering angle
	double x1, x2;

	// Boolean variable for rejection loop
	bool reject = true;

	srand( clock() );

	// Azimuthal angle (phi) rejection loop
	while (reject) 
	{                    
		rnd1 = std::rand()/(double)RAND_MAX;
		rnd2 = std::rand()/(double)RAND_MAX;
		x1 = 2.0*rnd1 - 1.0;
		x2 = 2.0*rnd2 - 1.0;

		// Apply rejection criteria
		if ( pow(x1,2) + pow(x2,2) < 1 ) 
		{
			// Accept the value of phi and terminate loop
			reject = false;
	
			//Calculate the Cosine and Sine of the azimuthal angle
			cos_az = ( pow(x1,2) - pow(x2,2) )/( pow(x1,2) + pow(x2,2) );
			sin_az = ( 2*x1*x2 )/( pow(x1,2) + pow(x2,2) );		
		}	// End rejection citeria

	}	// End of while rejection loop

}

//---------------------------------------------------------------------------//
// end AzimuthalRej.cpp
//---------------------------------------------------------------------------//

