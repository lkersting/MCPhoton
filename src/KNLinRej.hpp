//---------------------------------------------------------------------------//
//!
//! \file   KNLinRej.hpp
//! \author Luke Kersting
//! \brief  Klein-Nishina Rejection Sampling using a Linear Function
//!
//---------------------------------------------------------------------------//

#ifndef KN_LIN_REJ_HPP
#define KN_LIN_REJ_HPP

//#include <stdlib.h>
#include <math.h>
#include <iostream>

// Linear rejection function
double s;


//	----- BEGIN KNpdf -----
void KNpdf ( double& q, double& alpha, double& mu )
{	// Sample the unormalized K-N pdf

// 1st term in q
double term1;

// 2nd term in q
double term2;

// Calculate the 1st term in q
term1 = alpha*(1.0 - mu);

// Calculate the 2nd term in q
term2 = 1.0/(1.0 + term1);

// Calculate value of q
q = pow(term2,2)*( term2 + term1 + pow(mu,2) );
}
//	----- END KNpdf -----



//	----- BEGIN LinearRejSample -----
void LinearRejFnct ( double& alpha, double& mu ) 
{

// Term in qmin
double trm = 1.0/( 1.0 + 2.0*alpha );

// minimum q = q( mu=-1 )
double qmin = pow(trm,3) + trm;

// maximum q = q( mu= 1 )
double qmax = 2;

// Random number for sampling ( 0 < rnd < 1 )
double rnd = std::rand()/(double)RAND_MAX;

// Sample for mu
mu = 2.0*sqrt( pow(qmin,2) + rnd ) - 2.0*qmin - 1;

// Calculate value of S
s = 0.5*( qmax - qmin )*( mu + 1.0 ) + qmin;
}
//	----- END LinearRejFnct -----



//	----- BEGIN KNLinRej -----
void KNLinRej( double& alpha, double& mu ) {

// Unormalized pdf for K-N scattering
double q;

// Random numbers for sampling ( 0 < rnd < 1 )
double rnd;

// Boolean variable for mu rejection loop
bool reject = true;

// Reject mu while reject = true
while (reject) {                    
	rnd = std::rand()/(double)RAND_MAX;

	// Sample mu and Calculate the linear rejection function
	LinearRejFnct ( alpha, mu );

	// Sample the unormalized K-N pdf (q)
	KNpdf ( q, alpha, mu );

	// Apply rejection criteria
	if ( rnd*s < q ) {
		// Accept the value of mu and terminate loop
		reject = false;
	}
}	// End of while loop

}
//	----- END KNLinRej -----

#endif // end KN_LIN_REJ_HPP 
