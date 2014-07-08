//---------------------------------------------------------------------------//
//!
//! \file   ComptonEffect.hpp
//! \author Luke Kersting
//! \brief  Incoherent (Compton) scattering class
//!
//---------------------------------------------------------------------------//

#ifndef COMPTON_EFFECT_HPP
#define COMPTON_EFFECT_HPP

// Std Lib Includes
//#include <math.h>
#include <iostream>
#include <fstream>


//	----- BEGIN getLogInterpolation -----

void getLogInterpolation ( std::string filename, 
									double (&x),
									double (&y) )
{
	// The lower x used in the Logarithmic interpolation
	float x_a; 

	// The upper x used in the Logarithmic interpolation
	float x_b;

	// The value of y at y(x_a)
	float y_a;

	// The value of y at y(x_b)
	float y_b;

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
		file >> x_b >> y_b;
		if ( x <= x_b ) 
		{
			search = false;
		}
	}
	file.close();

	// Calculate linear weight factor
	weight = ( x_b - x )/( x_b - x_a );

	// Linearly interpolate y(x)
	y = pow(y_a,1-weight) * pow(y_b,weight);
}
//	----- END getLogInterpolation -----


//	----- BEGIN getLinearInterpolation -----

void getLinearInterpolation ( std::string filename, 
									double (&x),
									double (&y) )
{
	// The lower x used in the Linear interpolation
	float x_a; 

	// The upper x used in the Linear interpolation
	float x_b;

	// The value of y at y(x_a)
	float y_a;

	// The value of y at y(x_b)
	float y_b;

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
		file >> x_b >> y_b;
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
}
//	----- END getLinearInterpolation -----


//	----- BEGIN ComptonScatter -----

void ComptonScatter ( std::string file,
						double (&alpha),
						double (&mu) )
{
// The initial photon wavelength in Compton units
double Lambda = 1.0/alpha;

// The final photon wavelength in Compton units
double LambdaPrime; 

// The ratio of final to initial photon wavelength
double t;

// The track PDFs normalized over the range t[1, 1+Lambda/2]
double g;

// A sampling function confined to the unit interval
double h;

// The random number ranging from 0 to 1
double r1, r2, r3;

// The momentum transfer parameter
double x;

// Incoherent scatter function
double S;

// Atomic number of scattering medium (electrons/atom)
int Z = 26.0;

// Continue sampling while track = true
bool track = true;

while (track)
{

	// Set the 1st random number to sample track
	r1 = std::rand()/(double)RAND_MAX;

	/*	----- Track 1 -----	*/
	if ( r1 <= ( Lambda + 2.0 )/( 9.0*Lambda + 2.0 ) ) {

		// Set the 2nd random number
		r2 = std::rand()/(double)RAND_MAX;

		// Sampled for t
		t = 2.0*r2/Lambda + 1.0;

		// Calculate x 
		x = 29.1433*alpha*sqrt( Lambda*( t - 1.0 ) );

		// Calculate S(x,Z)
		getLinearInterpolation ( file, x, S );
		//getLogInterpolation ( file, x, S );

		// Calcluate h1
		h = 4.0*( 1.0/t - 1.0/pow(t,2) )*S/Z;

		// Set the 3rd random number
		r3 = std::rand()/(double)RAND_MAX;

		// Apply rejection criterion
		if ( r3 <= h ) {
			// Calculate cosine of scatter angle
			mu = ( 1.0 + alpha - t )/alpha;

			// Terminate track loop
			track = false;
		}
	}
	/*	----- End Track 1 -----	*/

	/*	----- Track 2 -----	*/
	else {
		// Set the 2nd random number
		r2 = std::rand()/(double)RAND_MAX;
	
		// Obtain sampled t
		t = ( Lambda + 2.0 )/ ( Lambda + 2.0*( 1.0 - r2 ) );

		// Calculate x 
		x = 29.1433*alpha*sqrt( Lambda*( t - 1.0 ) );

		// Calculate S(x,Z)
		getLinearInterpolation ( file, x, S );
		//getLogInterpolation ( file, x, S );
	
		// Calcluate h2
		h = ( 1.0/t + pow(1.0 + Lambda - Lambda*t,2) )*S/( 2.0*Z );
	 
		// Set the 3rd random number
		r3 = std::rand()/(double)RAND_MAX;
	
		// Apply rejection criterion
		if ( r3 <= h ) {
			// Calculate cosine of scatter angle
			mu = ( 1.0 + alpha - t )/alpha;

			// Terminate track loop
			track = false;
		}
	}
/*	----- End Track 2 -----	*/

} //End of while track loop

}
//	----- END ComptonScatter -----


#endif // end COMPTON_EFFECT_HPP
