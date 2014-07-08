//---------------------------------------------------------------------------//
//!
//! \file   KNLinRej.cpp
//! \author Luke Kersting
//! \brief  Klein-Nishina Rejection Sampling using a Linear Function
//!
//---------------------------------------------------------------------------//

#include <cmath>
#include <cstdlib>
#include <iostream>

// Linear rejection function
double s;


// Sample the unormalized K-N pdf
void KNpdf ( 	double (&q), 
				double (&alpha),
				double (&mu)    )
{
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


// Calculate the linear rejection function
void LinearRejFnct ( 	double (&alpha), 
						double (&mu)    ) 
{

	// Term in qmin
	double trm1 = 1.0/( 1.0 + 2.0*alpha );

	// minimum q = q( mu=-1 )
	double qmin = pow(trm1,3) + trm1;

	// maximum q = q( mu= 1 )
	double qmax = 2;

	// Term in mu
	double trm2 = ( qmax - qmin )/( qmax + qmin );

	// Random number for sampling ( 0 < rnd < 1 )
	double rnd = std::rand()/(double)RAND_MAX;

	// Sample for mu
	//mu = 2.0*sqrt( pow(qmin,2) + rnd ) - 2.0*qmin - 1;
	mu = ( sqrt( pow(trm2,2) + 4*( trm2*rnd + 1.0 - trm2 ) ) - 2.0 )/trm2;

	// Calculate value of S
	s = 0.5*( qmax - qmin )*( mu + 1.0 ) + qmin;
}


// Apply rejection criteria for sampled value of mu
void KNLinRej( 	double (&alpha),
				double (&mu)	)
{
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

//---------------------------------------------------------------------------//
// end KNLinRej.cpp
//---------------------------------------------------------------------------//

