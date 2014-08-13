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
AzRej( sin_phi, cos_phi );

// Sample the polar scattering angle
MU_REJECTION_SAMPLING ( alpha, mu );

// Calculate new photon energy
E = E/( 1.0 + alpha*( 1 - mu ) );

// Calculate sin( theta ) from mu
sin_theta = sqrt( 1.0 - pow(mu,2) );

// Calculate new photon orientation
TransformationMatrix ( sin_phi, cos_phi, sin_theta, mu, u );
}

/*
// Calculate new photon orientation and energy after a scattering event 
// using the two path rejection method
void PhotonScatter(	std::deque<double> E_data,
					std::deque<double> S_data, 
								double (&u)[3],
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
AzRej( sin_phi, cos_phi );

// Sample the polar scattering angle
MU_REJECTION_SAMPLING ( E_data, S_data, alpha, mu );

// Calculate new photon energy
E = E/( 1.0 + alpha*( 1 - mu ) );

// Calculate sin( theta ) from mu
sin_theta = sqrt( 1.0 - pow(mu,2) );

// Calculate new photon orientation
TransformationMatrix ( sin_phi, cos_phi, sin_theta, mu, u );
}
*/
//---------------------------------------------------------------------------//
// end PhotonScatter.hpp
//---------------------------------------------------------------------------//

