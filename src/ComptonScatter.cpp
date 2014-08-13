//---------------------------------------------------------------------------//
//!
//! \file   ComptonEffect.hpp
//! \author Luke Kersting
//! \brief  Incoherent (Compton) scattering class
//!
//---------------------------------------------------------------------------//

#include <string>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <iostream>

// Other Includes
#include "Interpolate.hpp"

// Sample compton scattering using the two track method
void ComptonScatter (	double (&alpha),
						double (&mu)	)
{
	// X grad data
	extern std::deque<double> X_data;

	// S grid data
	extern std::deque<double> S_data;

	// The initial photon wavelength in Compton units
	double lambda = 1.0/alpha;

	// The ratio of final to initial photon wavelength
	double t;

	// A sampling function confined to the unit interval
	double h;

	// The random number ranging from 0 to 1
	double r1, r2, r3;

	// The momentum transfer parameter
	double x;
	
	// Incoherent scatter function
	double S;

	// Atomic number of scattering medium (electrons/atom)
	int Z = 26.0;

	// Continue sampling while reject = true
	bool reject = true;

	srand( clock() );

	while (reject)
	{
		// Set the 1st random number to sample track
		r1 = std::rand()/(double)RAND_MAX;

//---------------------------------------------------------------------------//
//					TRACK 1
//---------------------------------------------------------------------------//

		if ( r1 <= ( lambda + 2.0 )/( 9.0*lambda + 2.0 ) ) {

			// Set the 2nd random number
			r2 = std::rand()/(double)RAND_MAX;

			// Sampled for t
			t = 2.0*r2/lambda + 1.0;

			// Calculate x 
			x = 29.1433*alpha*sqrt( lambda*( t - 1.0 ) );

			// Calculate S(x,Z)
			INTERPOLATOR2 ( X_data, S_data, x, S );

			// Calcluate h1
			h = 4.0*( 1.0/t - 1.0/pow(t,2) )*S/Z;

			// Set the 3rd random number
			r3 = std::rand()/(double)RAND_MAX;

			// Apply rejection criterion
			if ( r3 <= h ) {
				// Calculate cosine of scatter angle
				mu = ( 1.0 + alpha - t )/alpha;

				// Terminate track loop
				reject = false;
			}
		}

//---------------------------------------------------------------------------//
//					TRACK 2
//---------------------------------------------------------------------------//
		else {
			// Set the 2nd random number
			r2 = std::rand()/(double)RAND_MAX;
	
			// Obtain sampled t
			t = ( lambda + 2.0 )/ ( lambda + 2.0*( 1.0 - r2 ) );

			// Calculate x 
			x = 29.1433*alpha*sqrt( lambda*( t - 1.0 ) );

			// Calculate S(x,Z)
			INTERPOLATOR2 ( X_data, S_data, x, S );
	
			// Calcluate h2
			h = ( 1.0/t + pow(1.0 + lambda - lambda*t,2) )*S/( 2.0*Z );
		 
			// Set the 3rd random number
			r3 = std::rand()/(double)RAND_MAX;
	
			// Apply rejection criterion
			if ( r3 <= h ) {
				// Calculate cosine of scatter angle
				mu = ( 1.0 + alpha - t )/alpha;

				// Terminate track loop
				reject = false;
			}
		}

	} //End of while track loop

	if ( mu > 1.0 || mu < -1.0 )
	{
		std::cout << "Invalid value for mu: " << mu << std::endl;
		exit (EXIT_FAILURE);
	}

	if ( t <= 1.0 )
	{
		std::cout << "Invalid value for t: " << t << std::endl;
		exit (EXIT_FAILURE);
	}

	if ( S/Z > 1.00001 )
	{
		std::cout << "Invalid value for S/Z: " << S/Z << std::endl;
		exit (EXIT_FAILURE);
	}

	if ( r1 > 1.0 || r2 > 1.0 || r3 > 1.0)
	{
		std::cout << "Invalid value for rand" << std::endl;
		exit (EXIT_FAILURE);
	}

}

//---------------------------------------------------------------------------//
// end ComptonScatter.hpp
//---------------------------------------------------------------------------//
