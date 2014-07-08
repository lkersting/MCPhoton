//---------------------------------------------------------------------------//
//!
//! \file   LinearInterp.hpp
//! \author Luke Kersting
//! \brief  Linear Interpolation of a three column x y(x) z(x) data txt file 
//!
//---------------------------------------------------------------------------//

#ifndef LINEAR_INTERP_HPP
#define LINEAR_INTERP_HPP

// Std Lib Includes
//#include <iostream>
#include <fstream>

//	----- BEGIN getLinearInterpolation -----

void getLinearInterpolation ( std::string filename, 
									double (&x),
									double (&y),
									double (&z) )
{
	// The lower x used in the Linear interpolation
	float x_a; 

	// The upper x used in the Linear interpolation
	float x_b;

	// The value of y at y(x_a)
	float y_a;

	// The value of y at y(x_b)
	float y_b;

	// The value of z at z(x_a)
	float z_a;

	// The value of z at z(x_b)
	float z_b;

	// The weighted average of the two data points
	double weight;
	
	// Boolean variable used to end for the closest data ponts
	bool search;

	// Prepare to read data txt file
	std::ifstream file;

	// Open data file called filename
	file.open(filename);

	// Search for two closest values to x
	search = true;
	while (search)
	{ 
		x_a = x_b;
		y_a = y_b;
		z_a = z_b;	
		file >> x_b >> y_b >> z_b;
		if ( x <= x_b ) 
		{
			search = false;
		}
	}
	file.close();

	// Calculate linear weight factor
	weight = ( x_b - x )/( x_b - x_a );

	// Linearly interpolate y(x)
	y = ( 1.0 - weight )*y_a + weight*y_b;

	// Linearly interpolate z(x)
	z = ( 1.0 - weight )*z_a + weight*z_b;
}
//	----- END getLinearInterpolation -----

#endif // end LINEAR_INTERP_HPP



