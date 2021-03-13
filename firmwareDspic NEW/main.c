#include <main.h>

void main()
{
	start();
	while(true) {
		get_adc_val_sen();
		
		//MAP     f = p00 + p10*x + p01*y + p20*x^2 + p11*x*y + p02*y^2;        subs(f, [x, y], [vss, tps])
		value = -14.49 + 0.1403*adc_sen[1] + 9.239*adc_sen[0] + -0.0003145*adc_sen[1]*adc_sen[1] + -0.03021*adc_sen[1]*adc_sen[0] -1.363*adc_sen[0]*adc_sen[0];
		dac8();
		//
		
		time_sin();//500-4Khz CKP
		
		time_150();//0-150Hz VSS
		
		debug_PICkit();
	}
}
