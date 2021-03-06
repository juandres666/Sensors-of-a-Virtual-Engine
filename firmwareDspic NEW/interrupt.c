 #int_TIMER1
void  TIMER1_isr(void) { //sin + desfase
	output_e((input_e()&0b100000000)|ckp[s_n]); //OUTPUT_B(~input_b());
	output_f((ckp[s_n]>>6));//||(input_f()&&0b11111100));
      
   if(s_n==1383)
      output_toggle(PIN_C15);//sincro   CMP
   else if((s_n==472)||(s_n==1732))
      output_high(PIN_C13);//Ks E8
   else if((s_n==494)||(s_n==1754))
      output_low(PIN_C13);//Ks E8
   
   s_n++;
   if(s_n>=2700)//0-2699
   	s_n=0;
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
