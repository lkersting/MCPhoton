//---------------------------------------------------------------------------//
//!
//! \file   PhotonTransport.cpp
//! \author Luke Kersting
//! \brief  Sample and transport photon to next collision location 
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <cmath>
#include <cstdlib>

// Transport the photon to the next event location ( z )
void PhotonTransport( 	double (&z),
						double (&uz),
						const double (&Sigma_t) ) 
{
// Random number used for sampling
double rnd = std::rand()/(double)RAND_MAX;

// Mean free paths to next collision
double tau;

// Distance to next collision
double dr;

// Sample mean free paths to next collision
tau = -log(rnd);

// Calculate distance traveled in given medium
dr = tau/Sigma_t;

// Update particle z location
z += dr*uz;
}

//---------------------------------------------------------------------------//
// end PhotonTransport.cpp
//---------------------------------------------------------------------------//
