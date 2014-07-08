//---------------------------------------------------------------------------//
//!
//! \file   histogram.hpp
//! \author Luke Kersting
//! \brief  Put a vector into histogram form
//!
//---------------------------------------------------------------------------//

#include <algorithm> 

#ifndef HISTOGRAM_HPP
#define HISTOGRAM_HPP

//	----- BEGIN PhotonTransport -----
double histogram (double (&data)[], double (&N) ) {

// Max value of range
double val_max = std::max_element(data,data+N);

// Min value of range
double val_min = 0;

// Number of bins
const int num_bins = 100;

// Uniform bin width
double bin_width = (val_max - val_min) / num_bins;

// Bin number of the data point
int bin_idx;

// Histogram of data
double hist[num_bins][2];

// Bin center value
for (int i = 0; i < num_bins; i++) {
	hist[i][1] = val_min + (i + 0.5)*bin_width;
}

// Put data in the histogram bins
for (double i : data) {
	bin_idx = (int)((i - val_min) / bin_width);
	hist[bin_idx][0]++;	
}

}
//	----- End Histogram -----

#endif // end HISTOGRAM_HPP