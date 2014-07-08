//---------------------------------------------------------------------------//
//!
//! \file   Compton.cpp
//! \author Luke Kersting
//! \brief  Incoherent (Compton) scattering
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <math.h>
#include <iostream>
#include <fstream>

#include "PhotonScatter.hpp"


main() {

// Current photon energy [MeV]
double E = 1.0;		// Initial energy

// Current photon Orientation (u_x, u_y, u_z)
double u[3];

// Set initial photon Orientation
u[0] = u[1] = 0.0;
u[2] = 1.0;

PhotonScatter( u, E );

std::cout << E << std::endl;
}

