//---------------------------------------------------------------------------//
//!
//! \file   KNLinRej.cpp
//! \author Luke Kersting
//! \brief  Klein-Nishina Rejection Sampling using a Linear Function
//!
//---------------------------------------------------------------------------//

#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <eigen3/Eigen/Dense>

// Linear rejection function
double s;


//	----- BEGIN KNpdf -----
void KNpdf ( double& q, double& alpha, double& mu ) {	// Sample the unormalized K-N pdf

double
// 1st term in q
trm1,
// 2nd term in q
trm2;

trm1 = alpha*(1.0 - mu);
trm2 = 1.0/(1.0 + trm1);
q = pow(trm2,2)*( trm2 + trm1 + pow(mu,2) );
}
//	----- END KNpdf -----

//	----- BEGIN LinearRejFnct -----
void LinearRejFnct ( double (&alpha), double (&mu) ) {

// Term in qmin
double trm = 1.0/( 1.0 + 2.0*alpha );

// minimum q = q( mu=-1 )
double qmin = pow(trm,3) + trm;

// maximum q = q( mu= 1 )
double qmax = 2;

s = 0.5*( qmax - qmin )*( mu + 1.0 ) + qmin;

}
//	----- END LinearRejFnct -----

/* Math to calculate mu sampling
 * integral of s:	s_int = ( qmax + qmin ) 
 * phi = s/s_int = 0.5*(mu + 1.0) + qmin
 * integral of phi: PHI = 0.25*( mu + 1.0 )*( 4*qmin + mu + 1.0 ) 
 * PHI = random # xi
 * solve for mu
 * mu = 2.0*sqrt( qmin^2 + xi ) -2.0*qmin -1
 */

main () {

const int
// Number of Trials
ntrials = 10, //1000000;
// Max value of mu
val_max = 1,
// Min value of mu
val_min = -1,
// number of histogram bins
num_bins = 200,
// number of different photon energies
num_energy = 5;

Eigen::MatrixXd
// histogram bin center points
xc(num_bins,5),		
// counts per histogram bin
nc(num_bins,5),
// energy of photon relative to electron rest mass
alpha(5,1);
double
// Unormalized pdf for K-N scattering
q,
// cos(theta) of scattering angle
mu,
// 1st random number for sampling ( 0 < xi_1 < 1 )
xi_1,
// 2nd random number for sampling ( 0 < xi_2 < 1 )
xi_2,
// Uniform bin width
bin_width = (double)(val_max - val_min) / num_bins;
int
// number of kept values
i_counter,
// Bin number of the data point
bin_idx;


//this defines 200 bin centers in increments of 0.01
for ( int i = 0; i < 200; i++ ) {
	for ( int j = 0; j < 5; j++ ) {
		xc(i,j) = -0.995 + 0.01*i;  
	}
}

/* The values of alpha specified below are for illustration; 
 * they could be changed to anything, but are physically equal
 * to the ratio of initial photon energy to electron rest mass energy */
alpha << 0.0, 0.5 , 1.0, 5.0, 10.0;

for ( int j = 0; j < 5; j++) {
	i_counter = 0;		// initalize the number of kept values
	
	for ( int i = 0; i < ntrials; i++ ) {
		xi_1 = std::rand()/(double)RAND_MAX;                    
		xi_2 = std::rand()/(double)RAND_MAX;
		/* Convert the random number (xi_1) to range appropriate 
		 * for the cosine of the scattering angle (mu) */
		mu = 2.0*xi_1 - 1.0;
		// Calculate the linear rejection function
		LinearRejFnct ( alpha(j,0), mu );
//std::cout << "  alpha = " << alpha(j,0) << std::endl;
		// Sample the unormalized K-N pdf (q)
		KNpdf ( q, alpha(j,0), mu );
//std::cout << "q = " << q << "  xi_2*s = " << xi_2*s << std::endl;
		if ( xi_2*s < q ) {	// if this criterion is satisfied, increment the
			// number of kept values and count mu			
			i_counter++;
			// Find the histogram bin index for given data point
			bin_idx = (int)((mu - val_min) / bin_width);
//std::cout << "q = " << q << "  s = " << s << std::endl;
//std::cout << "  bin # = " << bin_idx << "  mu = " << mu <<  std::endl;
			// Put data point in the histogram bin
			nc(bin_idx,j)++;	
		}
	}
}
} // end of program
