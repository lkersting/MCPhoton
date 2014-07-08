//---------------------------------------------------------------------------//
//!
//! \file   LogInterpTest.cpp
//! \author Luke Kersting
//! \brief  Logarithmic Interpolation of a two column data y(x) txt file 
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <math.h>
#include <iostream>
#include <fstream>

float getLogInterpolation ( float x_a,
							float x_b,
							float y_a,
							float y_b,
							float x )
{
	// The weighted average of the two data points
	double weight;

	// Interpolate the data
	weight = ( x_b - x )/( x_b - x_a );
	return pow(y_a,1-weight) * pow(y_b,weight);
}

float getLinearInterpolation ( float x_a,
							float x_b,
							float y_a,
							float y_b,
							float x )
{
	// The weighted average of the two data points
	double weight;
	
	weight = ( x_b - x )/( x_b - x_a );
	return y_a*(1-weight) + y_b*weight;
}


main () {

// The lower x used in the Logarithmic interpolation
float x_a; 

// The upper x used in the Logarithmic interpolation
float x_b;

// The value of y at y(x_a)
float y_a;

// The value of y at y(x_b)
float y_b;

// The interpolated x location
float x;

// The interpolated value
double y_log, y_lin;

x_a = 0.0;
x_b = 1.0;
y_a = 1.0;
y_b = 100.0;
x = 0.5;

y_log = getLogInterpolation (x_a,x_b,y_a,y_b,x);
y_lin = getLinearInterpolation (x_a,x_b,y_a,y_b,x);

std::cout << "For log interpolation y = " << y_log << std::endl;
std::cout << "For lin interpolation y = " << y_lin << std::endl;
}


