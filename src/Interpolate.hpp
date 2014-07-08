//---------------------------------------------------------------------------//
//!
//! \file   Interpolate.hpp
//! \author Luke Kersting
//! \brief  Interpolation of a N column x, y_1(x), ... ,y_n(x) data txt file 
//!
//---------------------------------------------------------------------------//

#ifndef INTERPOLATE_HPP
#define INTERPOLATE_HPP

// Std Lib Includes
#include <fstream>


	// The lower x used in interpolation
	float x_a; 

	// The upper x used in interpolation
	float x_b;

	// The value of y1 at y1(x_a)
	float y1_a;

	// The value of y1 at y1(x_b)
	float y1_b;

	// The value of y2 at y2(x_a)
	float y2_a;

	// The value of y2 at y2(x_b)
	float y2_b;

	// The weighted average of the two data points
	double weight;
	
	// Boolean variable used to end for the closest data ponts
	bool search;

	// Prepare to read data txt file
	std::ifstream file;

/*	----- BEGIN getLinearInterpolation2 -----
 *
 *	The linear interpolation of 2 coulumn data ( x, y1(x) )
 */
void getLinearInterpolation2 ( std::string filename, 
									double (&x),
									double (&y1) )
{
	// Prepare to read data txt file
	std::ifstream file;

	// Open data file called filename
	file.open(filename);

	// Search for two closest values to x
	search = true;
	while (search)
	{ 
		x_a = x_b;
		y1_a = y1_b;	
		file >> x_b >> y1_b;
		if ( x <= x_b ) 
		{
			search = false;
		}
	}
	file.close();

	// Calculate weight factor
	weight = ( x_b - x )/( x_b - x_a );

	// Linearly interpolate y(x)
	y1 = ( 1.0 - weight )*y1_b + weight*y1_a;
}
//	----- END getLinearInterpolation -----


/*	----- BEGIN getLinearInterpolation3 -----
 *
 *	The linear interpolation of 3 coulumn data ( x, y1(x), y2(x) )
 */
void getLinearInterpolation3 ( std::string filename, 
									double (&x),
									double (&y1),
									double (&y2) )
{
	// Open data file called filename
	file.open(filename);

	// Search for two closest values to x
	search = true;
	while (search)
	{ 
		x_a = x_b;
		y1_a = y1_b;
		y2_a = y2_b;	
		file >> x_b >> y1_b >> y2_b;
		if ( x <= x_b ) 
		{
			search = false;
		}
	}
	file.close();

	// Calculate weight factor
	weight = ( x_b - x )/( x_b - x_a );

	// Linearly interpolate y1(x)
	y1 = ( 1.0 - weight )*y1_b + weight*y1_a;

	// Linearly interpolate y2(x)
	y2 = ( 1.0 - weight )*y2_b + weight*y2_a;
}
//	----- END getLinearInterpolation3 -----


/*	----- BEGIN getLogInterpolation2 -----
 *
 *	The logarithmic interpolation of 2 coulumn data ( x, y1(x) )
 */
void getLogInterpolation2 ( std::string filename, 
									double (&x),
									double (&y1) )
{
	// Open data file called filename
	file.open(filename);

	// Search for two closest values to x
	search = true;
	while (search)
	{ 
		x_a = x_b;
		y1_a = y1_b;	
		file >> x_b >> y1_b;
		if ( x <= x_b ) 
		{
			search = false;
		}
	}
	file.close();

	// Calculate weight factor
	weight = ( x_b - x )/( x_b - x_a );

	// Logarthmicly interpolate y(x)
	y1 = pow(y1_b,1.0 - weight) * pow(y1_a,weight);

}
//	----- END getLogInterpolation2 -----


/*	----- BEGIN getLogInterpolation3 -----
 *
 *	The logarithmic interpolation of 3 coulumn data ( x, y1(x), y2(x) )
 */
void getLogInterpolation3 ( std::string filename, 
									double (&x),
									double (&y1),
									double (&y2) )
{
	// Open data file called filename
	file.open(filename);

	// Search for two closest values to x
	search = true;
	while (search)
	{ 
		x_a = x_b;
		y1_a = y1_b;	
		y2_a = y2_b;
		file >> x_b >> y1_b >> y2_b;
		if ( x <= x_b ) 
		{
			search = false;
		}
	}
	file.close();

	// Calculate weight factor
	weight = ( x_b - x )/( x_b - x_a );

	// Logarithmicly interpolate y1(x)
	y1 = pow(y1_a,1.0 - weight) * pow(y1_b,weight);

	// Logarithmicly interpolate y2(x)
	y2 = pow(y2_a,1.0 - weight) * pow(y2_b,weight);

}
//	----- END getLogInterpolation3 -----


#endif // end INTERPOLATE_HPP



