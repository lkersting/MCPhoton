//---------------------------------------------------------------------------//
//!
//! \file   ComptonEffect.cpp
//! \author Luke Kersting
//! \brief  Sampling Incoherent Scattering (Compton Effect)
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
//#include <math.h>
//#include <iostream>

#include "ComptonEffect2.hpp"

main () {

// The photon initial realtive energy (units of e- rest mass)
double E = 1.0;

// The photon final realtive energy (units of e- rest mass)
double EPrime;

// The initial photon wavelength in Compton units
double Lambda = 1/E;

// The final photon wavelength in Compton units
double LambdaPrime; 

// The photon scattering angle
double mu;

// The ratio of final to initial photon wavelength
double t;

// The variable of interest w
double w;

// The track PDFs normalized over the range t[1, 1+Lambda/2]
double g;

// A sampling function confined to the unit interval
double h1, h2;

// The random number ranging from 0 to 1
double r1, r2, r3;

// The momentum transfer parameter
double x;

// The scattering medium
std::string name = "S_Fe.txt";
// Electron rest mass (kg)
//const double m_e = .511; // (Mev/c^2)
const double m_e =9.109534E-31;

// Speed of light (m/s)
const double c = 2.99792458E8;

// Pi
const double pi = acos(0.0);;

// Planck's constant (m^2*kg/s)
const double h = 6.62606957E-34;

// Incoherent scatter function
double S;

// Atomic number of scattering medium (electrons/atom)
int Z = 26.0;

// Set the 1st random number to sample track
r2 = std::rand()/(double)RAND_MAX;

/*	----- Track 1 -----	*/
if ( r1 <= ( Lambda + 2 )/( 9*Lambda + 2 ) ) {
std::cout << "track 1" << std::endl;
	// Set the 2nd random number
	r2 = std::rand()/(double)RAND_MAX;

	// Obtain sampled t
	t = 2.0*r2/Lambda + 1.0;
//std::cout << "t = " << t << std::endl;
	// Calcluate EPrime
	EPrime = 1.0/( Lambda*t );

	// Calculate x 
//	x = (double) m_e*c*pow(10,-10)*
//				 sqrt( pow(E,2) + pow(EPrime,2) - E*EPrime*mu )/( 2*h );
	x = 29.1433*E*sqrt( Lambda*( t - 1 ) );
std::cout << "x = " << x << std::endl;
	// Calculate S(x,Z)
	//S = ComptonEffect::getLinearInterpolation ( name, x );
	S = getLogInterpolation ( name, x );
std::cout << "S = " << S << std::endl;
	// Calcluate h1
	h1 = 4*( 1/t - 1/pow(t,2) )*S/Z;
std::cout << "h1 = " << h1 << std::endl;
	// Set the 3rd random number
	r3 = std::rand()/(double)RAND_MAX;

	// Apply rejection criterion: Accept t if
	if ( r3 <= h1 ) {
		// Calcluate EPrime
		EPrime = 1.0/( Lambda*t );
		std::cout << "E'= "<<EPrime << std::endl;
		w = 1.0 - Lambda*( t - 1.0 );
	}
}
/*	----- End Track 1 -----	*/

/*	----- Track 2 -----	*/
else {
std::cout << "track 2" << std::endl;
	// Set the 2nd random number
	r2 = std::rand()/(double)RAND_MAX;

	// Obtain sampled t
	t = ( Lambda + 2.0 )/ ( Lambda + 2.0*( 1.0 - r2 ) );

	// Calcluate EPrime
	//EPrime = 1.0/( Lambda*t );

	// Calculate x 
	//x = (double) m_e*c*sqrt( pow(E,2) + pow(EPrime,2) - E*EPrime*mu )/( 2*h );
	x = 29.1445*E*sqrt( Lambda*( t - 1 ) );

	// Calculate S(x,Z)
	S = getLogInterpolation ( name, x );
std::cout << "S = " << S << std::endl;

	// Calcluate h2
	h2 = ( 1.0/t + pow(1 + Lambda - Lambda*t,2) )*S/( 2.0*Z );
 
	// Set the 3rd random number
	r3 = std::rand()/(double)RAND_MAX;

	// Apply rejection criterion
	if ( r3 <= h2 ) {
		// Calcluate EPrime
		EPrime = 1.0/( Lambda*t );
		std::cout << EPrime << std::endl;
		w = 1.0 - Lambda*( t - 1.0 );
	}
}
/*	----- End Track 2 -----	*/

}
// END PROGRAM
