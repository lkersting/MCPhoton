//---------------------------------------------------------------------------//
//!
//! \file   KleinNishina.cpp
//! \author Luke Kersting
//! \brief  Klein-Nishina angular scattering distribution
//!
//---------------------------------------------------------------------------//

#include <stdlib.h>
#include <math.h>
#include <iostream>

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
counts(ntrials,5),
// histogram bin center points 
xc(num_bins,5),
nc(num_bins,5),
alpha(5,1);
double
/*
// histogram bin center points 
xc[200][5],
// counts per histogram bin
nc[200][5],
// ratio of initial photon energy to electron rest mass energy
alpha[5][1],
*/

// analytical answer
f_ana[201][5],
mu_x[201],
xi_1,
xi_2,
mu,
trm1,
trm2,
trm3,
ang_diff_scat,
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

/* initialize alpha; the values of alpha specified below are for
 * illustration; they could be changed to anything, but are physically equal
 * to the ratio of initial photon energy to electron rest mass energy */
//alpha[1][0] = 0.0; alpha[2][0] = 0.5 ; alpha[3][0] = 1.0;
//alpha[4][0] = 5.0; alpha[5][0] = 10.0;
alpha << 0.0, 0.5 , 1.0, 5.0, 10.0;

for ( int j = 0; j < 5; j++) {
	i_counter = 0;			// initalize the number of kept values
	for ( int i = 0; i < ntrials; i++ ) {
		xi_1 = std::rand()/(double)RAND_MAX;                    
		xi_2 = std::rand()/(double)RAND_MAX;
		/* this converts the random number, which lies in the 
		 * interval 0 < xi < 1, to a range appropriate for the 
		 * cosine of the scattering angle */
		mu = -1 + 2*xi_1;
//std::cout << "  bin # = " << bin_idx <<
		trm1 = (1 + mu*mu)/2.0;
		trm2 = 1/(1 + alpha(j,0)*(1 - mu));
		trm3 = 2*pow(alpha(j,0),2)*pow(1 - mu,2)*trm2/trm1;
		ang_diff_scat = trm1*pow(trm2,2)*(1 + trm3);
//std::cout << ang_diff_scat << std::endl;
		if ( xi_2 < ang_diff_scat ) {	// if this criterion is satisfied, increment the
			i_counter++;				// number of kept values and count mu
			//counts(i_counter,j) = mu;
			// Put data in the histogram bins
			bin_idx = (int)((mu - val_min) / bin_width);
std::cout << "  bin # = " << bin_idx << 
		     "  mu = " << mu <<  std::endl;
			nc(bin_idx,j)++;	
		}
	}
}

// compare to the analytical form:

for ( int j = 0; j < 5; j++ ) {
	for (int i = 0; i < 201; i++ ) {
		mu_x[i] = -1 + 0.01*i;
		trm1 = ( 1 + pow(mu_x[i],2) ) / 2.0;
		trm2 = 1 / ( 1 + alpha(j,0)*( 1 - mu_x[i] ) );
		trm3 = 2*pow(alpha(j,0),2)*pow(1 - mu_x[i],2)*trm2 / trm1;
		f_ana[i][j] = ( ntrials/200.0 )*trm1*pow(trm2,2)*(1 + trm3);
	}
}
/*
plot(xout(:,1),nc(:,1),'rx',xout(:,2),nc(:,2),'b+',xout(:,3),nc(:,3),'ko',...
    xout(:,4),nc(:,4),'gx',xout(:,5),nc(:,5),'m+')
hold on
plot(mu_x,f_ana(:,1),'k',mu_x,f_ana(:,2),'c',mu_x,f_ana(:,3),'r',mu_x,f_ana(:,4),'b',...
    mu_x,f_ana(:,5),'k')
axis([-1 1 0 ntrials/200])
xlabel('\mu = cos(\theta)')
ylabel('Counts')
*/
} // end of program
