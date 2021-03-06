#int_TIMER0
void  TIMER0_isr(void) { //sin + desfase
   if(sen_n<num_sen) {
      if(s_n<15) {
         output_b(sen[s_n]>>2); //OUTPUT_B(~input_b());
         output_d((sen[s_n]<<6)||(input_d()&&0b00111111));
         s_n++;
      }
      else {
         s_n=0;
         sen_n++;
      }
   }
   else {
      if(e_n<60) {
         output_b(esp[e_n]>>2); //OUTPUT_B(~input_b());
         output_d((esp[e_n]<<6)||(input_d()&&0b00111111));
         e_n=e_n+2;
      }
      else {
         e_n=0;
         sen_n=0;
      }
   }
   set_timer0(tmr0_frecu); //65535-80
}

#int_TIMER1
void  TIMER1_isr(void) {  // 1 - 150 Hz
   output_toggle(PIN_C0); //dont do nothing
   if  (tmr1_n<=tmr1_width) output_high(PIN_C2);
   else output_low(PIN_C2);

   tmr1_n++;
   if(tmr1_n>=tmr1_frecu) tmr1_n=0;

   set_timer1(65460);//65535-75=50uS  
}

#int_TIMER2
void  TIMER2_isr(void) { // 1 Hz
   if  (tmr2_n<=100) output_high(PIN_C1);
   else output_low(PIN_C1);

   tmr2_n++;
   if(tmr2_n>=200) tmr2_n=0;
}

#int_AD
void  AD_isr(void) {
   adc_sum+=read_adc(ADC_READ_ONLY);
   adc_i++;
   if(adc_i>=4096) {
      adc_val[adc]=(int16)(adc_sum>>12);
      adc_sum=0;
      adc_i=0;
      
      adc++;
      if(adc==2) adc=0;
      set_adc_channel(adc);
   }
   read_adc(ADC_START_ONLY);
}
