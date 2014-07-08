//---------------------------------------------------------------------------//
//!
//! \file   LogInterp.hpp
//! \author Luke Kersting
//! \brief  Logarithmic Interpolation of a two column data y(x) txt file 
//!
//---------------------------------------------------------------------------//

#ifndef LOG_INTERP_HPP
#define LOG_INTERP_HPP

// Std Lib Includes
//#include <iostream>
#include <fstream>

//	----- BEGIN getLogInterpolation -----
void getLogInterpolation ( std::string filename, 
									double (&x),
									double (&y),
									double (&z) )
{
	// The lower x used in the Logarithmic interpolation
	float x_a; 

	// The upper x used in the Logarithmic interpolation
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

	// Logarithmic interpolate y(x)
	y = pow(y_a,1-weight) * pow(y_b,weight);

	// Logarithmic interpolate z(x)
	z = pow(z_a,1-weight) * pow(z_b,weight);

}
//	----- END getLogInterpolation -----

#endif // end LOG_INTERP_HPP



