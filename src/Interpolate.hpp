//---------------------------------------------------------------------------//
//!
//! \file   Interpolate.hpp
//! \author Luke Kersting
//! \brief  linear and log interpolation forward declaration header
//!
//---------------------------------------------------------------------------//

#ifndef INTERPOLATE_HPP
#define INTERPOLATE_HPP

#include <string>

// Linear interpolate from a 2 coulumn data set ( x, y1(x) )
void getLinearInterpolation2 ( std::string filename, 
									double (&x),
									double (&y1) );

// Linear interpolate from a 3 coulumn data set ( x, y1(x), y2(x) )
void getLinearInterpolation3 ( std::string filename, 
									double (&x),
									double (&y1),
									double (&y2) );

// Logarithmicly interpolate from a 2 coulumn data set ( x, y1(x) )
void getLogInterpolation2 ( std::string filename, 
									double (&x),
									double (&y1) );

// Logarithmicly interpolate from a 2 coulumn data set ( x, y1(x), y2(x) )
void getLogInterpolation3 ( std::string filename, 
									double (&x),
									double (&y1),
									double (&y2) );

#endif // end INTERPOLATE_HPP

//---------------------------------------------------------------------------//
// end Interpolate.hpp
//---------------------------------------------------------------------------//
