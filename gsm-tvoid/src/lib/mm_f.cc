
#include "mm_f.h"

mm_f::mm_f(float omega):
	d_omega(omega),
	d_mu(0.5),
	d_x_1(0.0),
	d_a_1(0.0),
	d_gain_mu(0.01),
	d_gain_omega(0.25 * d_gain_mu * d_gain_mu)
{}


float mm_f::slicer(float x)
{	
	return x < 0 ? -1.0 : 1.0;
}

float mm_f::update(float x_0, float a_0)
{
    d_mm = (d_a_1 * x_0) - (a_0 * d_x_1);
	
	//limit d_mm
	if (d_mm > 1.0) d_mm = 1.0;
	else if (d_mm < -1.0) d_mm = -1.0;

	//error feedback
	d_omega = d_omega + d_gain_omega * d_mm;
	
	//limit omega
/*		
	if (d_omega > d_max_omega)
		d_omega = d_max_omega;
	else if (d_omega < d_min_omega)
		d_omega = d_min_omega;
*/
	//update mu		
	d_mu = d_mu + d_omega + d_gain_mu * d_mm;
	//process mu / ii advances after burst processing for burst timing
	
	//update delay taps
	d_x_1 = x_0;
	d_a_1 = a_0;

	return d_mu;
}


float mm_f::update(float x_0)
{
	return update(x_0, slicer(x_0) );
}



