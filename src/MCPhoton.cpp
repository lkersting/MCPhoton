//---------------------------------------------------------------------------//
//!
//! \file   MCPhoton.cpp
//! \author Luke Kersting
//! \brief  Monte Carlo Photon transport 
//!
//---------------------------------------------------------------------------//

#include "MCPhoton.hpp"
#include <ctime>
#include <cmath>
#include <cstdlib>

// Number of histogram bins
const int num_bins = 100;

// Histogram of exiting photons energy spectrum
double hist[num_bins][2];

main () {

// Max photon histogram energy range [MeV]
double val_max = 1.0;

// Min photon histogram energy range [MeV]
double val_min = 0.0;

// Uniform histogram bin width
double bin_width = (val_max - val_min) / num_bins;

// Bin number of the data point
int bin_idx;

// Density of Iron (g/cm^3)
const double N_Fe = 55.845;

// Iron (Fe) absorption and total cross section data file [cm^2/g] (E in MeV)
std::string name = "/Fe.txt";

// Full file path
std::string file = _DIR + name;

// Random number for interaction sampling
double rnd;

// Micro absorption cross section
double sigma_a;

// Micro total cross section
double sigma_t;

// Macro total cross section
double Sig_t;

// Current photon z location [cm]
double z;

// Current photon Orientation (u_x, u_y, u_z)
double u[3];	

// Current photon energy [MeV]
double E = 1.0;		// Initial energy

// Number of mean free paths in the shield thickness
double mfp = 10.0;

// Thickness of the iron shield
double thickness;

// Approximate attenuation
double Atten;

// Boolean variable for looping particle transport inside the shield
bool InShield;

// Number of photons that exited backward from the shield
int BackwardExit = 0;

// Number of photons that exited forward from the shield
int ForwardExit = 0;

// Number of photons absorbed
int Absorbed = 0;

// The scalar flux at the far end of the shield
float scalar_flux;

// Start and end times for timer
std::clock_t start, end;

// Run time duration
double duration;

// Number of photons being modeled 
int NumPhotons;// = 1e5; 

//---------------------------------------------------------------------------//
// User inputs
//---------------------------------------------------------------------------//
// Input # of photons to be modeled
std::cout << "Choose the number of photons to model (ie: 100000): ";
std::cin >> NumPhotons;

// Start timer
start = std::clock();

// Histogram bin center value
for (int i = 0; i < num_bins; i++) {
	hist[i][1] = val_min + (i + 0.5)*bin_width;
}

// Get the initial micro total cross section
_INTERPOLATOR3 ( file, E, sigma_a, sigma_t );

// Calculate initial macro total cross section
Sig_t = sigma_t*N_Fe;

// Calcaulate shield thickness (10 mfp)
thickness = mfp/Sig_t;

// Approximate attenuation
Atten = NumPhotons*exp(-10.0);
std::cout << "\n-------------------------------------------------\n" << 
"The approximate attenuation was:\n" << Atten << " photons/cm\u00b2" << std::endl;

// Run Monte Carlo calculations for NumPhotons
for (int p = 0; p < NumPhotons; p++) {

	// Set initial photon location
	z = 0.0;

	// Set initial photon Orientation
	u[0] = u[1] = 0.0;
	u[2] = 1.0;

	// Set initial photon energy
	E = 1.0;

	// Loop while particle is inside the shield
	InShield = true;

	while (InShield) 
	{

		// Get Micro absorption and total cross section at current energy
		_INTERPOLATOR3 ( file, E, sigma_a, sigma_t );

		// Sample for scattering or absorption
		rnd = std::rand()/(double)RAND_MAX;

		if ( rnd < sigma_a/sigma_t ) 
		{
			// Tally absorbed photons
			Absorbed++;

			// Exit inshield loop
			InShield = false;
		}	// End absorption loop
		
		else 
		{
			// Calculate Macro total cross scrtion
			Sig_t = sigma_t*N_Fe;
	
			// Sample the mean free path to next collision
			PhotonTransport ( z, u[2], Sig_t );

			// Sample the scatter orientation and new energy
			PhotonScatter ( u, E );

			if (z <= 0.0){
				// Tally backward exiting photons
				BackwardExit ++;
	
				// Exit inshield loop
				InShield = false;
			}
		
			else if (z >= thickness){
				// Tally forward exiting photons
				ForwardExit ++;

				// Add the weighted crossing to the scalar flux
				scalar_flux += abs(1.0/u[2]);

				// Find phton energy bin index
				bin_idx = (int)((E - val_min) / bin_width);

				// Put photon energy in the histogram bin
				hist[bin_idx][0]++;

				// Exit inshield loop
				InShield = false;
			}

		}	// End scattering loop

	}	// End of while inshield loop

}	// End of NumPhoton loop

// Normalize scalar flux to total number of photons modeled
scalar_flux /= NumPhotons;

// End timer
end = std::clock();

// Calculate total run time
duration = ( end - start )/(double) CLOCKS_PER_SEC; 

if (ForwardExit > 0 )
{
	// Print histogram header
	std::cout << "-------------------------------------------------\n" <<
	"   Energy Histogram" <<
	"\n--------------------------\n" <<
	"#\t\tE [MeV]" << 
	"\n--------------------------" << std::endl;

	// Print histogram 
	for ( int i = 0; i < num_bins; i++ ) {
		if ( hist[i][0] != 0 ) {
			std::cout << hist[i][0] << "\t\t" << hist[i][1] << std::endl;
		}
	}

// Print scalar flux
std::cout << "-------------------------------------------------\n" <<
"The scalar flux was:\n"<< scalar_flux << " 1/cm\u00b2\n" <<
scalar_flux*NumPhotons << " photons/cm\u00b2\n\n";


// Print approximate attenuation
std::cout << "The approximate attenuation was:\n" << Atten << " photons/cm\u00b2\n";

}

// Print results
std::cout << "-------------------------------------------------\n" << 
BackwardExit << "\tphotons exited backward from the shield\n" << 
ForwardExit << "\tphotons exited forward from the shield\n" << 
Absorbed << "\tphotons absorbed\n"<<
BackwardExit + ForwardExit + Absorbed << "\ttotal # of photons\n"<<
"-------------------------------------------------" << std::endl;

// Print total run time
std::cout << "-------------------------------------------------\n" 
"Total run time was " << duration << " seconds\n" << std::endl;

}
