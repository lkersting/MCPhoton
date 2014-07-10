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
#include <ctime>

// Transport the photon to the next event location ( z )
void PhotonTransport( 	double (&r)[3],
						double (&u)[3],
						const double (&Sigma_t) ) 
{
	// Random number used for sampling
	double rnd;

	// Mean free paths to next collision
	double tau;

	// Distance to next collision
	double dr;

	srand( clock() );
	rnd = std::rand()/(double)RAND_MAX;

	// Sample mean free paths to next collision
	tau = -log(rnd);

	// Calculate distance traveled in given medium
	dr = tau/Sigma_t;

	// Update particle r location
	r[0] += dr*u[0];
	r[1] += dr*u[1];
	r[2] += dr*u[2];
}

//---------------------------------------------------------------------------//
// end PhotonTransport.cpp
//---------------------------------------------------------------------------//
