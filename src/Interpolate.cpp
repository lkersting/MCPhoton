//---------------------------------------------------------------------------//
//!
//! \file   Interpolate.cpp
//! \author Luke Kersting
//! \brief  Interpolation of a N column x, y_1(x), ... ,y_n(x) data set 
//!
//---------------------------------------------------------------------------//

// Includes
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include "Interpolate.hpp"

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

// Extract 2 column data from file to deque array
void getDataFile2(	std::string filename,
					std::deque<double> &x_data,
					std::deque<double> &y1_data)
{
	// x value (data from the 1st column)
	double x;

	// y1 value (data from the 2nd column)
	double y1;

	// Open data file called filename
	std::ifstream file( filename.c_str() );

	// Check to see if file is open
	if (!file)
	{ 
   		// Show error message
   		std::cout << "Error!\n" << filename << "\nThe file path is invalid!\n";
		exit (EXIT_FAILURE);
	}

	while (file) 
	{
		file >> x >> y1;
		x_data.push_back(x);
		y1_data.push_back(y1);
	}

	file.close();
}

// Extract 3 column data from file to deque array
void getDataFile3(	std::string filename,
					std::deque<double> &x_data,
					std::deque<double> &y1_data,
					std::deque<double> &y2_data )
{
	// x value (data from the 1st column)
	double x;

	// y1 value (data from the 2nd column)
	double y1;

	// y2 value (data from the 3rd column)
	double y2;

	// Open data file called filename
	std::ifstream file( filename.c_str() );

	// Check to see if file is open
	if (!file)
	{ 
   		// Show error message
   		std::cout << "Error!\n" << filename << "\nThe file path is invalid!\n";
		exit (EXIT_FAILURE);
	}

	while (file) 
	{
		file >> x >> y1 >> y2;
		x_data.push_back(x);
		y1_data.push_back(y1);
		y2_data.push_back(y2);
	}

	file.close();
}

// Linear interpolate from a 2 coulumn data set ( x, y1(x) )
void getLinearInterpolation2 (	std::deque<double> &x_data,
								std::deque<double> &y1_data,
												double (&x),
												double (&y1) )
{
	// Set i to the 1st index in the array
	int i = 0;

	// Set j to the last index in the array
	int j = x_data.size();

	// Perform a binary search of the index of the closest x_data value below x
	while ( j - i > 1 )
	{
		int k = (int) ( i + j )/2;
		if ( x_data[k] < x )
		{
			i = k;
		}
		else
		{
			j = k;
		}
	}

	// Assign x_a to the closest x_data value below x
	x_a = x_data[i];

	// Assign x_b to the closest x_data value above x
	x_b = x_data[i+1];

	// Assign y1_a to the equivalent x_a value
	y1_a = y1_data[i];

	// Assign y1_b to the equivalent x_b value
	y1_b = y1_data[i+1];

	// Calculate weight factor
	weight = ( x_b - x )/( x_b - x_a );

	// Linearly interpolate y(x)
	y1 = ( 1.0 - weight )*y1_b + weight*y1_a;
}

// Linear interpolate from 3 array data set ( x, y1(x), y2(x) )
void getLinearInterpolation3 (	std::deque<double> &x_data,
								std::deque<double> &y1_data,
								std::deque<double> &y2_data,
												double (&x),
												double (&y1),
												double (&y2) )
{
	// Set i to the 1st index in the array
	int i = 0;

	// Set j to the last index in the array
	int j = x_data.size();

	// Perform a binary search of the index of the closest x_data value below x
	while ( j - i > 1 )
	{
		int k = (int) ( i + j )/2;
		if ( x_data[k] < x )
		{
			i = k;
		}
		else
		{
			j = k;
		}
	}

	// Assign x_a to the closest x_data value below x
	x_a = x_data[i];

	// Assign x_b to the closest x_data value above x
	x_b = x_data[i+1];

	// Assign y1_a & y2_a to their equivalent x_a value
	y1_a = y1_data[i];
	y2_a = y2_data[i];

	// Assign y1_b & y2_b to their equivalent x_b value
	y1_b = y1_data[i+1];
	y2_b = y2_data[i+1];
	
	// Calculate weight factor
	weight = ( x_b - x )/( x_b - x_a );

	// Linearly interpolate y1(x)
	y1 = ( 1.0 - weight )*y1_b + weight*y1_a;

	// Linearly interpolate y2(x)
	y2 = ( 1.0 - weight )*y2_b + weight*y2_a;
}
/*
// Linear interpolate from a 3 coulumn data set ( x, y1(x), y2(x) )
void getLinearInterpolation3 (	std::deque<double> &x_data,
								std::deque<double> &y1_data,
								std::deque<double> &y2_data,
								double (&x),
								double (&y1),
								double (&y2) )
{
	int i = 0;
	
	// Search for two closest values to x in data set
	search = true;
	while (search)
	{ 
		if ( x <= x_data[i] ) 
		{
			x_a  =  x_data[i-1];
			x_b  =  x_data[i];  
			y1_a = y1_data[i-1];
			y1_b = y1_data[i];
			y2_a = y2_data[i-1];
			y2_b = y2_data[i];

			search = false;
		}
	i++;
	}

	// Calculate weight factor
	weight = ( x_b - x )/( x_b - x_a );

	// Linearly interpolate y1(x)
	y1 = ( 1.0 - weight )*y1_b + weight*y1_a;

	// Linearly interpolate y2(x)
	y2 = ( 1.0 - weight )*y2_b + weight*y2_a;
}
*/
// Logarithmicly interpolate from a 2 coulumn data set ( x, y1(x) )
void getLogInterpolation2 ( std::deque<double> &x_data,
							std::deque<double> &y1_data,
											double (&x),
											double (&y1) )
{
	// Set i to the 1st index in the array
	int i = 0;

	// Set j to the last index in the array
	int j = x_data.size();

	// Perform a binary search of the index of the closest x_data value below x
	while ( j - i > 1 )
	{
		int k = (int) ( i + j )/2;
		if ( x_data[k] < x )
		{
			i = k;
		}
		else
		{
			j = k;
		}
	}

	// Assign x_a to the closest x_data value below x
	x_a = x_data[i];

	// Assign x_b to the closest x_data value above x
	x_b = x_data[i+1];

	// Assign y1_a to the equivalent x_a value
	y1_a = y1_data[i];

	// Assign y1_b to the equivalent x_b value
	y1_b = y1_data[i+1];

	// Calculate weight factor
	weight = ( x_b - x )/( x_b - x_a );

	// Logarthmicly interpolate y(x)
	y1 = pow(y1_b,1.0 - weight) * pow(y1_a,weight);
}

// Logarithmicly interpolate from a 3 coulumn data set ( x, y1(x), y2(x) )
void getLogInterpolation3 (	std::deque<double> &x_data,
							std::deque<double> &y1_data,
							std::deque<double> &y2_data,
											double (&x),
											double (&y1),
											double (&y2) )
{
	// Set i to the 1st index in the array
	int i = 0;

	// Set j to the last index in the array
	int j = x_data.size();

	// Perform a binary search of the index of the closest x_data value below x
	while ( j - i > 1 )
	{
		int k = (int) ( i + j )/2;
		if ( x_data[k] < x )
		{
			i = k;
		}
		else
		{
			j = k;
		}
	}

	// Assign x_a to the closest x_data value below x
	x_a = x_data[i];

	// Assign x_b to the closest x_data value above x
	x_b = x_data[i+1];

	// Assign y1_a & y2_a to their equivalent x_a value
	y1_a = y1_data[i];
	y2_a = y2_data[i];

	// Assign y1_b & y2_b to their equivalent x_b value
	y1_b = y1_data[i+1];
	y2_b = y2_data[i+1];

	// Calculate weight factor
	weight = ( x_b - x )/( x_b - x_a );

	// Logarithmicly interpolate y1(x)
	y1 = pow(y1_b,1.0 - weight) * pow(y1_a,weight);

	// Logarithmicly interpolate y2(x)
	y2 = pow(y2_b,1.0 - weight) * pow(y2_a,weight);
}

//---------------------------------------------------------------------------//
// end Interpolate.cpp
//---------------------------------------------------------------------------//



