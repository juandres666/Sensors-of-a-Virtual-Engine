#include <main.h>

void main() {
   start();
   while(true) {
      get_val();

      //////////////////////////////////////
      //%%%%% calculos del duty cicle  %%%%%
      //////////////////////////////////////
      
      //interpolaciones

      //////////////////////////////////////
      //%%%%% %%%%%%%%%%%%%%%%%%%%%%%  %%%%%
      //////////////////////////////////////
      
      time_sin(adc_val[0]);
      time_150(adc_val[1]);//0-150Hz
      debug_PICkit();
   }
}
