//---------------------------------------------------------------------------//
//!
//! \file   KNRej.cpp
//! \author Luke Kersting
//! \brief  Translation Klein-Nishina angular scat dist from matlab code
//!
//---------------------------------------------------------------------------//

// Std library icludes
#include <cstdlib>
#include <cmath>

// Polar angle rejection criteria for the Klein-Nishin angular scat dist
void KNRej( double (&alpha),
			double (&mu)	)
{
	// Random numbers for sampling ( 0 < rnd < 1 )
	double rnd1, rnd2;

	// Term in ang_diff_scat
	double trm1, trm2, trm3;

	// Angular differntial scattering cross section
	double ang_diff_scat;

	// Boolean variable for mu rejection loop
	bool reject = true;

	while (reject) {
		rnd1 = std::rand()/(double)RAND_MAX;                    
		rnd2 = std::rand()/(double)RAND_MAX;

		/* this converts the random number, which lies in the 
		 * interval 0 < rnd < 1, to a range appropriate for the 
		 * cosine of the scattering angle */
		mu = -1.0 + 2.0*rnd1;

		// Calculate terms
		trm1 = (1.0 + mu*mu)/2.0;
		trm2 = 1.0/(1.0 + alpha*(1.0 - mu));
		trm3 = 2.0*pow(alpha,2)*pow(1.0 - mu,2)*trm2/trm1;

		// Calculate the angular differntial scattering cross section
		ang_diff_scat = trm1*pow(trm2,2)*(1.0 + trm3);
	
		// Apply rejection criteria
		if ( rnd2 < ang_diff_scat ) 
		{	
			// Accept the value of mu and terminate loop
			reject = false;
		}

	} //End while loop

}

//---------------------------------------------------------------------------//
// end KNRej.hpp
//---------------------------------------------------------------------------//

