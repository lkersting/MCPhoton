//---------------------------------------------------------------------------//
//!
//! \file   Interpolate.hpp
//! \author Luke Kersting
//! \brief  linear and log interpolation forward declaration header
//!
//---------------------------------------------------------------------------//

#ifndef INTERPOLATE_HPP
#define INTERPOLATE_HPP

#include <cstring>
#include <deque>

// Extract data from file to 2 deque array
void getDataFile2(	std::string filename,
					std::deque<double> &x_data,
					std::deque<double> &y1_data );

// Extract data from file to 3 deque array
void getDataFile3(	std::string filename,
					std::deque<double> &x_data,
					std::deque<double> &y1_data,
					std::deque<double> &y2_data );

// Linear interpolate from a 2 array data set ( x, y1(x) )
void getLinearInterpolation2 (	std::deque<double> &x_data,
								std::deque<double> &y1_data,
												double (&x),
												double (&y1) );

// Linear interpolate from a 3 array data set ( x, y1(x), y2(x) )
void getLinearInterpolation3 (	std::deque<double> &x_data,
								std::deque<double> &y1_data,
								std::deque<double> &y2_data,
												double (&x),
												double (&y1),
												double (&y2) );

// Logarithmicly interpolate from a 2 array data set ( x, y1(x) )
void getLogInterpolation2 ( std::deque<double> &x_data,
							std::deque<double> &y1_data,
											double (&x),
											double (&y1) );

// Logarithmicly interpolate from a 3 array data set ( x, y1(x), y2(x) )
void getLogInterpolation3 (	std::deque<double> &x_data,
							std::deque<double> &y1_data,
							std::deque<double> &y2_data,
											double (&x),
											double (&y1),
											double (&y2) );

#endif // end INTERPOLATE_HPP

//---------------------------------------------------------------------------//
// end Interpolate.hpp
//---------------------------------------------------------------------------//
