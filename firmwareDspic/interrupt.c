#int_TIMER1
void  TIMER1_isr(void) { //sin + desfase
	if(sen_n<num_sen) {
      if(s_n<45) {
         output_e((input_e()&0b100000000)|sen[s_n]); //OUTPUT_B(~input_b());
         output_f((sen[s_n]>>6));//||(input_f()&&0b11111100));
         s_n++;
      }
      else {
         s_n=0;
         sen_n++;
      }
      if(sen_n==30&&s_n==33)
      	output_toggle(PIN_C15);//sincro   CMP                                      
      else if((sen_n==10&&s_n==22)||(sen_n==38&&s_n==22))
      	output_high(PIN_C13);//Ks E8
      else if((sen_n==10&&s_n==44)||(sen_n==38&&s_n==44))
      	output_low(PIN_C13);//Ks E8
   }
   else {
      if(e_n<135) { 
         output_e((input_e()&0b100000000)|esp[e_n]); //OUTPUT_B(~input_b());
         output_f((esp[e_n]>>6));//||(input_f()&&0b11111100));
         e_n++;
      }
      else {
         e_n=0;
         sen_n=0;
      }
   }
}

#int_TIMER2
void  TIMER2_isr(void) {	//1hz   Oxigeno                              
	if  (tmr2_m<=20750) output_high(PIN_E8);//C13
   else output_low(PIN_E8);//C13

   tmr2_m++;
   if(tmr2_m>=41500) tmr2_m=0;
   
   //1 - 150 Hz Vss
	if  (tmr2_n<=tmr2_width) output_high(PIN_C14);
   else output_low(PIN_C14);

   tmr2_n++;
   if(tmr2_n>=tmr2_frecu) tmr2_n=0;
}

#int_ADC1
void  ADC1_isr(void) {
   adc_sum+=read_adc(ADC_READ_ONLY);
   adc_i++;
   if(adc_i>=256) {
      adc_val[adc]=(int16)(adc_sum>>8);
      
      adc_sum=0;
      adc_i=0;
      
      adc++;
      if(adc==2) adc=0;
      set_adc_channel(adc);
   }
   read_adc(ADC_START_ONLY);
}
