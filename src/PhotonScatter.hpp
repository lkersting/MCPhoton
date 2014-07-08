//---------------------------------------------------------------------------//
//!
//! \file   PhotonScatter.hpp
//! \author Luke Kersting
//! \brief  Sample the new photon orientation and energy after scattering 
//!
//---------------------------------------------------------------------------//

#ifndef PHOTON_SCATTER_HPP
#define PHOTON_SCATTER_HPP

// Std library includes
#include <math.h>
#include <cstdlib>
//#include <ctime>
//#include <iostream>

#include "KNLinRej.hpp"
#include "KleinNishina.hpp"
#include "ComptonEffect.hpp"

//	----- BEGIN PhotonScatter -----

void PhotonScatter( double (&u)[3],
					double (&E) ) 
{
// Random numbers used for sampling
double rnd1, rnd2;

// Points for sampling the azimuthal scattering angle
double x1, x2;

// Sine of azimuthal scattering angle
double sin_phi;

// Cosine of azimuthal scattering angle
double cos_phi;

// Boolean variable for phi rejection loop
bool reject = true;

// Sine of polar scattering angle
double sin_theta;

// Cosine of polar scattering angle
double mu;

// Photon energy normalized to electron rest mass (units m_e*c^2)
double alpha = E/.5110034;

// Start and end times for timer
//std::clock_t start, end;

// Run time duration
//double duration;

// Start timer
//start = std::clock();

// Reject phi while reject = true
while (reject) {                    
	rnd1 = std::rand()/(double)RAND_MAX;
	rnd2 = std::rand()/(double)RAND_MAX;
	x1 = 2.0*rnd1 - 1.0;
	x2 = 2.0*rnd2 - 1.0;

	// Apply rejection criteria
	if ( pow(x1,2) + pow(x2,2) < 1 ) {
		// Accept the value of mu and terminate loop
		reject = false;

		//Calculate the Cosine and Sine of the azimuthal angle
		cos_phi = ( pow(x1,2) - pow(x2,2) )/( pow(x1,2) + pow(x2,2) );
		sin_phi = ( 2*x1*x2 )/( pow(x1,2) + pow(x2,2) );		
	}
}	// End of while rejection loop
/*
const double pi = acos(-1.0);
rnd1 = std::rand()/(double)RAND_MAX;
double phi = 2*pi*rnd1;
sin_phi = sin(phi);
cos_phi = cos(phi);
*/

// -- Sample the polar scattering angle --
// Sample for mu
//KNLinRej( alpha, mu );
//KNRej( alpha, mu );

std::string file = "S_Fe.txt";
ComptonScatter ( file, alpha, mu );

// -- Calculate new photon energy
E = E/( 1.0 + alpha*( 1 - mu ) );

// Calculate sine of theta
sin_theta = sqrt( 1.0 - pow(mu,2) );

// -- Calculate new photon orientation
u[0] = cos_phi*mu*u[0] - sin_phi*u[1] + cos_phi*sin_theta*u[2];
u[1] = sin_phi*mu*u[0] + cos_phi*u[1] + sin_phi*sin_theta*u[2];
u[2] = -sin_theta*u[0] +     0.0*u[1] +                mu*u[2];

//end = std::clock();
//duration += ( end - start )/(double) CLOCKS_PER_SEC;
}
//	----- End PhotonScatter -----

#endif // end PHOTON_SCATTER_HPP


