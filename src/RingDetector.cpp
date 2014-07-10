//---------------------------------------------------------------------------//
//!
//! \file   RingDetector.cpp
//! \author Luke Kersting
//! \brief  Calculate particles crossing plane within a circular area 
//!
//---------------------------------------------------------------------------//

#include <iostream>
#include <fstream>
#include <cmath>

void Ring ( std::string data,
			double (&radius),
			int (&Transmitted),
			int (&N)			)
{

// Constant pi
const double PI = 3.14159265359;

// Area of the ring
double area = 2.0*PI*pow(radius,2);

// x crossing location
double x;

// y crossing location
double y;

// Cosine of crossing angle to z plane
double mu;

// # of crossings normalized to ring area, total particles, and mu
double flux = 0;

// Open data file called data
std::ifstream file( data.c_str() );

// Check to see if file is open
if (!file)
{ 
   	// Show error message
   	std::cout << "Error!\n" << data << "\nThe above file path is invalid!\n";
	exit (EXIT_FAILURE);
}

for ( int i = 0; i < Transmitted; i++ )
{
	file >> x >> y >> mu;

	if ( sqrt( pow(x,2) + pow(y,2) ) <= radius ) 
	{
		flux += fabs( (double) 1.0/mu );
	}
}

flux = flux/( area );

std::cout << "\nThe flux normalized to a ring of radius " << radius <<
" cm was:\n" << flux << " photons/cm\u00b2\n" << std::endl; 

}

//---------------------------------------------------------------------------//
// end RingDetector.cpp
//---------------------------------------------------------------------------//


