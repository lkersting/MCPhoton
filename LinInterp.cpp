//---------------------------------------------------------------------------//
//!
//! \file   LinInterp.cpp
//! \author Luke Kersting
//! \brief  Linear Interpolation of a two column data txt file
//!
//---------------------------------------------------------------------------//

#include "ComptonEffect.hpp"

float x_a, x_b, S_a, S_b;
double weight;
int search;

float ComptonEffect::getLinearInterpolation ( std::string filename, 
											   float x )
{
	std::ifstream file;
	file.open(filename);
	search =1;
	while (search == 1) 
	{ 
		x_a = x_b;
		S_a = S_b;	
		file >> x_b >> S_b;
		if ( x <= x_b ) 
		{
			search = 0;
		}
	}
	file.close();
	weight = ( x_b - x )/( x_b - x_a );
	return (1-weight)*S_a + weight*S_b;
}

main () {

//float array[44][2];
float x, S;
std::string name = "H.txt";

//std::cout << "input desired scattering medium (H, He, C, K): ";
//std::cin >> name;
//name += ".txt";


x = .11;
S = ComptonEffect::getLinearInterpolation ( name, x );

std::cout << "S = " << S << std::endl;

}




