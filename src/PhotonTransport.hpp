//---------------------------------------------------------------------------//
//!
//! \file   PhotonTransport.hpp
//! \author Luke Kersting
//! \brief  Photon transport forward declaration header 
//!
//---------------------------------------------------------------------------//

#ifndef PHOTON_TRANSPORT_HPP
#define PHOTON_TRANSPORT_HPP

// Transport the photon to the next event location ( x, y, z )
void PhotonTransport( 	double (&z),
						double (&uz),
						const double (&Sigma_t) );


#endif // end PHOTON_TRANSPORT_HPP

//---------------------------------------------------------------------------//
// end PhotonTransport.hpp
//---------------------------------------------------------------------------//
