//---------------------------------------------------------------------------//
//!
//! \file   KNLinRej.hpp
//! \author Luke Kersting
//! \brief  Klein-Nishina linear rejection forward declaration header
//!
//---------------------------------------------------------------------------//

#ifndef KN_LIN_REJ_HPP
#define KN_LIN_REJ_HPP

// Sample the unormalized K-N pdf
void KNpdf ( 	double (&q), 
				double (&alpha),
				double (&mu)    );

// Calculate the linear rejection function
void LinearRejFnct ( 	double (&alpha), 
						double (&mu)    );

// Apply rejection criteria for sampled value of mu
void KNLinRej( 	double (&alpha),
				double (&mu)	);



#endif // end KN_LIN_REJ_HPP 

//---------------------------------------------------------------------------//
// end KNLinRej.pp
//---------------------------------------------------------------------------//

