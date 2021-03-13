#include <main.h>

void main()
{
	start();
	while(true) {
		get_adc_val_sen();
		
		dac8();
		
		time_sin();//500-4Khz
		
		time_150();//0-150Hz
		
		debug_PICkit();
	}
}
