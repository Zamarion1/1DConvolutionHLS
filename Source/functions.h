#ifndef EXP_WIDTH

#include "ap_fixed.h"


typedef ap_fixed<EXP_WIDTH, INT_WIDTH> float24_t;

#endif

#ifndef __FUNCTIONS_H
#define __FUNCTIONS_H

float24_t relu(float24_t a)
{
	if (a > 0)
		return a;
	return 0;
}

#endif



