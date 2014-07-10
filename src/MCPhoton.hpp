//---------------------------------------------------------------------------//
//!
//! \file   MCPhoton.hpp
//! \author Luke Kersting
//! \brief  Monte Carlo Photon transport forward declaration header
//!
//---------------------------------------------------------------------------//

#ifndef MC_PHOTON_HPP
#define MC_PHOTON_HPP

// Linear Interpolation
//#define _INTERPOLATOR2 getLinearInterpolation2
//#define _INTERPOLATOR3 getLinearInterpolation3

// Log Interpolation
//#define _INTERPOLATOR2 getLogInterpolation2
//#define _INTERPOLATOR3 getLogInterpolation3

// Define home directory
#define xstr(s) str(s)
#define str(s) #s
//#define DIR "/home/lujoke/Documents/CPP/MCPhoton/data"

#include "PhotonTransport.hpp"
#include "PhotonScatter.hpp"
#include "Interpolate.hpp"
#include "RingDetector.hpp"
#include <iostream>
#include <fstream>


#endif // end MC_PHOTON_HPP

//---------------------------------------------------------------------------//
// end MCPhoton.hpp
//---------------------------------------------------------------------------//

