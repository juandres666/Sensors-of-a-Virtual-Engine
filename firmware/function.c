#inline
void start (void) {
   setup_adc_ports(AN0_TO_AN1|VSS_VDD);
   setup_adc(ADC_CLOCK_DIV_64);  //||ADC_ACQT_2TAD);;tad=0.8u
   #asm
   movlw 0b10010110; right justified,Tacq=4Tad(2Tad),Fad=Fosc/64    tacq=2.45us
   iorwf 0xFC0,1; direccion de ADCON2
   #endasm
   
   setup_timer_0(T0_INTERNAL|T0_DIV_1);
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);
   setup_timer_2( T2_DIV_BY_16,234,16);
   
   setup_spi(FALSE);
   setup_psp(PSP_DISABLED);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   port_b_pullups(FALSE);

   set_tris_a(0xff);
   set_tris_b(0b11000000);
   set_tris_c(0b10001000);
   set_tris_d(0x00);
   set_tris_e(0xff);
   
   enable_interrupts(int_ad);
   enable_interrupts(int_timer0);
   enable_interrupts(int_timer1);
   enable_interrupts(int_timer2);
   disable_interrupts(int_rda);
   disable_interrupts(int_ext);
   disable_interrupts(int_ext1);
   disable_interrupts(int_ext2);
   enable_interrupts(GLOBAL);
   //enable_interrupts(PERIPH);
   #ifdef Debug_serial fprintf(PICkit,"Inicio Tesis: Marco Chabla, Jose Mora;\r\n");
   #endif
   
   set_adc_channel(adc);
   read_adc(ADC_START_ONLY);
}

#inline
void debug_PICkit(void) {
	#ifdef Debug_serial
		static unsigned  int8 option;
      if(kbhit(PICkit)) {
         option=fgetc(PICkit);
         if(option=='1')
            fprintf(PICkit,"ADC0\r\n val:%Lu vol:%f 1:%f\r\n",adc_val[0],adc_vol[0],adc_sen[0]);
         else if(option=='2')
            fprintf(PICkit,"ADC1\r\n val:%Lu vol:%f 2:%f\r\n",adc_val[1],adc_vol[1],adc_sen[1]);
         else if(option=='f')
            fprintf(PICkit,"frec %5Lu \r\n",tmr1_frecu);
         else if(option=='v')
            fprintf(PICkit,"widt %5Lu \r\n",tmr1_width);
         }
   #endif
}

#inline
void get_val(void) {
   adc_vol[0]=((float)(adc_val[0]*5)/1024);
   adc_vol[1]=((float)(adc_val[1]*5)/1024);
}

#inline
void time_sin(int16 val_i10_a) {
   tmr0_frecu=65450-val_i10_a; //65535-80=65455 min time
}

#inline
void time_150(int16 val_i10_b) { //1hz=20000   150hz=130
   if(val_i10_b<2) {
      tmr1_frecu=20000;
      tmr1_width=10000;
   }
   else {
      tmr1_frecu=(int16)((float)(111000/val_i10_b));//(7/adc)/50uS
      tmr1_width=(tmr1_frecu/2);
   }
}
