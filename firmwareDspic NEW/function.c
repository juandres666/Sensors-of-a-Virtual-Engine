#inline
void start (void) {
   setup_spi( FALSE );
   
	setup_adc_ports(sAN0|sAN1,VSS_VDD );
	setup_adc(ADC_CLOCK_DIV_16|ADC_TAD_MUL_16);//setup_adc(ADC_CLOCK_DIV_4|ADC_TAD_MUL_8);
	
	setup_timer1(TMR_INTERNAL | TMR_DIV_BY_1, 1165); //sin
	setup_timer2(TMR_INTERNAL | TMR_DIV_BY_64, 10);//1hz   //1-150hz
	//setup_timer3(TMR_INTERNAL | TMR_DIV_BY_256, 56850);//1hz 

	set_tris_b(0b100001111);// B7-B4 4-lsb
	set_tris_c(0b0001111111111111);//c15 sin_sincro  c14 1-150hz  c13 1hz
	set_tris_d(0b11110000);// D4-D0 4-msb
	set_tris_e(0b011000000);//E8 Oxi  E5-E0 6-lsb SIN
	set_tris_f(0b11110100);// D4-D0 2-msb SIN
	
	enable_interrupts(INT_ADC1);
	enable_interrupts(int_timer1);
   enable_interrupts(int_timer2);
	
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
            fprintf(PICkit,"ADC0 val:%4Lu vol:%1.3e sen:%1.3e\r\n",adc_val[0],adc_vol[0],adc_sen[0]);
         else if(option=='2')
            fprintf(PICkit,"ADC1 val:%4Lu vol:%1.3e sen:%1.3e\r\n",adc_val[1],adc_vol[1],adc_sen[1]);
         else if(option=='d')
            fprintf(PICkit,"value:%1.3e max:%1.3e data:%3u \r\n",value,max,data);
         /*else if(option=='v')
            fprintf(PICkit,"widt %5Lu \r\n",tmr2_width);*/
         }
   #endif
}

#inline
void get_adc_val_sen(void) {
   adc_vol[0]=(float)adc_val[0]*0.0048828;//Tps
   adc_vol[1]=(float)adc_val[1]*0.0048828;//Vss
   
   adc_sen[0]=adc_vol[0];//TPS
   adc_sen[1]=adc_vol[1]*30;//VSS
}

#inline
void time_sin(void) { //500hz=1165   4khz=145   10bits CKP
      setup_timer1(TMR_INTERNAL | TMR_DIV_BY_1, (1165-(1023-adc_val[0])));
}

#inline
void time_150(void) { //1hz=41500   150hz=277   10bits VSS
      f_150=(1+ceil(0.190*adc_val[1]));
      tmr2_frecu=floor(41500/f_150);
      tmr2_width=ceil(tmr2_frecu/2);
}

#inline
void dac8(void) { //500hz=1165   4khz=145   10bits MAP
	data=(int8)ceil(value*51);

	output_d(data); //OUTPUT_B(~input_b());
	output_b(data);//||(input_f()&&0b11111100));
}
