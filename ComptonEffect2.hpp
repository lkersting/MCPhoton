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
#include <math.h>
#include <iostream>
#include <fstream>

//namespace MCPhoton{

class ComptonEffect 
{

public:

	static float getLinearInterpolation ( std::string txtfile,	// name of data txt file
										  float x );			// (1/Angstrom)

//	static float getLogInterpolation ( std::string txtfile,	// name of data txt file
//									   float x );			// (1/Angstrom)
/*
	// Electron rest mass (kg)
	const double m_e =9.109534E-31;

	// Speed of light (m/s)
	const double c = 2.99792458E8;

	// Pi
	const double pi = asin(0.0);

	// Planck's constant (m^2*kg/s)
	const double h = 6.62606957E-34;
*/
	
};

//} // End MCPhoton namespace

#endif // end COMPTON_EFFECT_HPP


//---------------------------------------------------------------------------//
// end ComptonEffect.hpp
//---------------------------------------------------------------------------//

float ComptonEffect::getLinearInterpolation ( std::string filename, 
									  float x )
{
	// The lower x used in the linear interpolation
	float x_a; 

	// The upper x used in the linear interpolation
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
	weight = ( x_b - x )/( x_b - x_a );
	return (1-weight)*y_a + weight*y_b;
}

static float getLogInterpolation ( std::string filename, 
								   float x )
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
	weight = ( x_b - x )/( x_b - x_a );
	return pow(y_a,1-weight) * pow(y_b,weight);
}




