#include <18F4550.h>
#device adc=10
#include <math.h>

#fuses HSPLL,MCLR,NOWDT,NOPROTECT,NOLVP,NODEBUG,USBDIV,PLL5,CPUDIV1,NOVREGEN,NOPBADEN
#use delay(clock=48000000)

#use fast_io(B)
#use fast_io(C)
#use fast_io(D)

#define Debug_serial 1
#ifdef Debug_serial
	#use rs232(baud=9600,uart1,stream=PICkit,parity=N,bits=8)
#endif

static unsigned int32 adc_sum;
static unsigned int16 adc_i;
static unsigned  int8 adc;
static unsigned int16 adc_val[2];
static float          adc_vol[2];
static float          adc_sen[2];

static unsigned int16 tmr0_frecu;
//const  unsigned int8  sen[20] = {128,89,53,25,7,1,7,25,53,89,128,167,203,231,249,255,249,231,203,167};
const  unsigned int8  sen[15] = {128,76,34,7,2,18,53,102,154,203,238,254,249,222,180};

static unsigned int8  s_n;
static unsigned int16 sen_n;
       unsigned int16 num_sen = 58;
const  unsigned int8  esp[60] = {128,116,101,83,62,41,22,8,1,3,13,29,48,67,84,98,108,115,119,121,122,123,123,124,124,124,125,125,126,127,128,128,129,130,130,131,131,132,132,132,133,134,137,141,148,158,172,190,209,228,243,252,254,246,231,212,190,170,152,138};
static unsigned int8  e_n;

static unsigned int16 tmr1_n;
static unsigned int16 tmr1_width;
static unsigned int16 tmr1_frecu;

static unsigned  int8 tmr2_n;

#include <interrupt.c>
#include <function.c>
