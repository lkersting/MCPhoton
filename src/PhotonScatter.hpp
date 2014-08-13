//---------------------------------------------------------------------------//
//!
//! \file   PhotonScatter.hpp
//! \author Luke Kersting
//! \brief  New photon energy and orientation forward declaration header 
//!
//---------------------------------------------------------------------------//

#ifndef PHOTON_SCATTER_HPP
#define PHOTON_SCATTER_HPP

#include <deque>

// Calculate new photon orientation and energy after a scattering event
void PhotonScatter( double (&u)[3],
					double (&E)		); 

/*
// Calculate new photon orientation and energy after a scattering event 
// using the two path rejection method
void PhotonScatter(	std::deque<double> E_data,
					std::deque<double> S_data, 
								double (&u)[3],
								double (&E)		);
*/
#endif // end PHOTON_SCATTER_HPP

//---------------------------------------------------------------------------//
// end PhotonScatter.hpp
//---------------------------------------------------------------------------//
