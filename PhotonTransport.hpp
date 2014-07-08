//---------------------------------------------------------------------------//
//!
//! \file   PhotonTransport.hpp
//! \author Luke Kersting
//! \brief  Sample and transport photon to next collision location 
//!
//---------------------------------------------------------------------------//

#ifndef PHOTON_TRANSPORT_HPP
#define PHOTON_TRANSPORT_HPP

// Std Lib Includes
#include <math.h>
#include <cstdlib>
#include <ctime>
//#include <iostream>

//	----- BEGIN PhotonTransport -----

void PhotonTransport( double (&z),
					  double (&uz),
					  const double (&Sigma_t) ) 
{
// Random number used for sampling
double rnd = std::rand()/(double)RAND_MAX;

// Mean free paths to next collision
double tau;

// Distance to next collision
double dr;

// Start and end times for timer
//std::clock_t start, end;

// Run time duration
//double long duration;

// Start timer
//start = std::clock();

// -- Calculate next collision location --

// Sample mean free paths to next collision
tau = -log(rnd);

// Calculate distance traveled in given medium
dr = tau/Sigma_t;

// Update particle location
//r[0] += dr*u[0];
//r[1] += dr*u[1];
z += dr*uz;

//end = std::clock();
//duration += ( end - start )/(double) CLOCKS_PER_SEC;
}
//	----- End PhotonTransport -----

#endif // end PHOTON_TRANSPORT_HPP



