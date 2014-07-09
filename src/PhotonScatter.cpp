//---------------------------------------------------------------------------//
//!
//! \file   PhotonScatter.cpp
//! \author Luke Kersting
//! \brief  Sample the new photon orientation and energy after scattering 
//!
//---------------------------------------------------------------------------//

#define ELECTRON_MASS 0.5110034 // [MeV]

//---------------------------------------------------------------------------//
// CHOOSE POLAR ANGLE REJCTION SAMPLING TECHNIQUE
//---------------------------------------------------------------------------//
// Use linear rejection for sampling mu
//#define MU_REJECTION_SAMPLING KNLinRej

// Use in class rejection for sampling mu
//#define MU_REJECTION_SAMPLING KNRej

// Use two track rejection for sampling mu
//#define MU_REJECTION_SAMPLING ComptonScatter
//---------------------------------------------------------------------------//

// Std library includes
#include <cmath>
#include <cstdlib>
#include <iostream>

// Other includes
#include "KNLinRej.hpp"
#include "KNRej.hpp"
#include "ComptonScatter.hpp"
#include "AzimuthalRej.hpp"

// Calculate new orientation from azimuthal and polar scattering angles
void TransformationMatrix( 	double (&sin_az),
							double (&cos_az),
							double (&sin_pol),
							double (&cos_pol),
							double (&u)[3]		)
{
	u[0] = cos_az*cos_pol*u[0] - sin_az*u[1] + cos_az*sin_pol*u[2];
	u[1] = sin_az*cos_pol*u[0] + cos_az*u[1] + sin_az*sin_pol*u[2];
	u[2] = 		 -sin_pol*u[0] +    0.0*u[1] +        cos_pol*u[2];

}


// Calculate new photon orientation and energy after a scattering event
void PhotonScatter( double (&u)[3],
					double (&E)		) 
{
// Sine of azimuthal scattering angle
double sin_phi;

// Cosine of azimuthal scattering angle
double cos_phi;

// Sine of polar scattering angle
double sin_theta;

// Cosine of polar scattering angle
double mu;

// Photon energy normalized to electron rest mass (units m_e*c^2)
double alpha = E/ELECTRON_MASS;

// Sample azimuthal angle (phi)
//AzRej( sin_phi, cos_phi );

	// Random numbers used for sampling
	double rnd1, rnd2;

	// Points for sampling the azimuthal scattering angle
	double x1, x2;

	// Boolean variable for rejection loop
	bool reject = true;

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
			cos_phi = ( pow(x1,2) - pow(x2,2) )/( pow(x1,2) + pow(x2,2) );
			sin_phi = ( 2*x1*x2 )/( pow(x1,2) + pow(x2,2) );		
		}	// End rejection citeria

	}	// End of while rejection loop



// Sample the polar scattering angle
MU_REJECTION_SAMPLING ( alpha, mu );

// Calculate new photon energy
E = E/( 1.0 + alpha*( 1 - mu ) );
//std::cout << E <<std::endl;
//std::cout << mu <<'\t' <<alpha <<std::endl;

// Calculate sin( theta ) from mu
sin_theta = sqrt( 1.0 - pow(mu,2) );

// Calculate new photon orientation
TransformationMatrix ( sin_phi, cos_phi, sin_theta, mu, u );
}

//---------------------------------------------------------------------------//
// end PhotonScatter.hpp
//---------------------------------------------------------------------------//

