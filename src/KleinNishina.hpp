//---------------------------------------------------------------------------//
//!
//! \file   KleinNishina.hpp
//! \author Luke Kersting
//! \brief  Translation Klein-Nishina angular scat dist from matlab code
//!
//---------------------------------------------------------------------------//

#ifndef KLEIN_NISHINA_HPP
#define KLEIN_NISHINA_HPP

// Std library icludes
#include <stdlib.h>
#include <math.h>
#include <iostream>


//	----- BEGIN KNRej -----
void KNRej(  double& alpha, double& mu ) {

// Max value of mu
const int val_max = 1;

// Min value of mu
const int val_min = -1;

// Random numbers for sampling ( 0 < xi < 1 )
double xi_1, xi_2;

// Term in ang_diff_scat
double trm1, trm2, trm3;

// Angular differntial scattering cross section
double ang_diff_scat;

// Boolean variable for mu rejection loop
bool reject = true;

while (reject) {
	xi_1 = std::rand()/(double)RAND_MAX;                    
	xi_2 = std::rand()/(double)RAND_MAX;

	/* this converts the random number, which lies in the 
	 * interval 0 < xi < 1, to a range appropriate for the 
	 * cosine of the scattering angle */
	mu = -1 + 2*xi_1;

	// Calculate terms
	trm1 = (1 + mu*mu)/2.0;
	trm2 = 1/(1 + alpha*(1 - mu));
	trm3 = 2*pow(alpha,2)*pow(1 - mu,2)*trm2/trm1;

	// Calculate the angular differntial scattering cross section
	ang_diff_scat = trm1*pow(trm2,2)*(1 + trm3);

	// Apply rejection criteria
	if ( xi_2 < ang_diff_scat ) {	
		// Accept the value of mu and terminate loop
		reject = false;
	}

} //End while loop

}
//	----- BEGIN KNRej -----

#endif // end KLEIN_NISHINA_HPP
