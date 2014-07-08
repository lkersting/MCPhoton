//---------------------------------------------------------------------------//
//!
//! \file   histogram.cpp
//! \author Luke Kersting
//! \brief  Put a vector into histogram form
//!
//---------------------------------------------------------------------------//

#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <eigen3/Eigen/Dense>

main () {

double
// Max value of range
val_max = 1,
// Min value of range
val_min = -1,
// Data
data[11] = {-1, .99, 0.5, 0.1, -.2, -1, -.4, 0.5, 0.4, 0.66, .01};
const int
// Number of bins
num_bins = 200;
double
// Uniform bin width
bin_width = (val_max - val_min) / num_bins;
std::cout << "bin width = " << bin_width << std::endl;
int
// Bin number of the data point
bin_idx;
Eigen::MatrixXd
// Histogram of data
hist(num_bins,2);

// Bin center value
for (int i = 0; i < num_bins; i++) {
//std::cout << "i= " << i << std::endl;
	hist(i,1) = val_min + (i + 0.5)*bin_width;
}

// Put data in the histogram bins
for (double i : data) {
	bin_idx = (int)((i - val_min) / bin_width);
std::cout << "data point = " << i << 
             "  bin # = " << bin_idx << std::endl;
	hist(bin_idx,0)++;	
}

std::cout << "histogram = \n" << hist << std::endl;

} // END OF FUNCTION
