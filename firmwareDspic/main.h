#include <30F4011.h>
#device adc=10

#INCLUDE <MATH.H>

#FUSES NOWDT                 	//No Watch Dog Timer
#FUSES FRC_PLL16             	//Internal Fast RC oscillator with 16X PLL
#FUSES NOCKSFSM              	//Clock Switching is disabled, fail Safe clock monitor is disabled
//#FUSES NOPUT                 	//No Power Up Timer
//#FUSES BORV27						//
//#FUSES BROWNOUT					//brownout reset

#FUSES PUT64                 	//No Power Up Timer PUT64 
#FUSES BORV42						//42
#FUSES BROWNOUT					//brownout reset



#use delay(clock=117920000) //7.37Mhz x16
//#use fixed_IO(E_outputs = PIN_E0,PIN_E0,PIN_E1,PIN_E1,PIN_E2,PIN_E2)

#use fast_io(B)
#use fast_io(C)
#use fast_io(D)
#use fast_io(E)
#use fast_io(F)

//#define Debug_serial 1
#ifdef Debug_serial
	#use rs232(baud=9600,uart1,stream=PICkit,parity=N,bits=8)
#endif

const unsigned  int8  sen[ 45] = {128,110,93,76,61,46,34,23,14,7,3,1,2,5,10,18,28,40,53,68,85,102,119,137,154,171,188,203,216,228,238,246,251,254,255,253,249,242,233,222,210,195,180,163,146};
//const unsigned  int8  sen[ 36] = {128,106,85,65,46,31,18,9,3,1,3,9,18,31,46,65,85,106,128,150,171,191,210,225,238,247,253,255,253,247,238,225,210,191,171,150};
const  unsigned int8  esp[135] = {128,122,117,111,105,98,89,81,72,62,53,43,34,25,18,11,6,3,1,1,3,6,10,16,23,31,40,48,57,65,73,81,88,94,99,104,108,111,114,116,118,119,120,121,122,122,123,123,123,123,123,123,124,124,124,124,124,124,125,125,125,125,126,126,126,127,127,127,128,128,129,129,129,129,130,130,130,130,131,131,131,131,131,131,132,132,132,132,132,133,133,133,134,135,136,137,139,142,144,148,152,157,163,169,176,184,192,200,209,217,226,233,240,246,250,253,254,254,251,247,242,235,227,219,210,200,190,181,172,163,156,148,142,136,132};
//const  unsigned int8  esp[108] = {128,121,114,107,98,87,76,65,53,41,30,20,11,5,2,1,3,7,13,22,31,42,53,63,73,83,91,98,104,109,113,116,118,120,121,122,122,123,123,123,123,123,124,124,124,124,125,125,125,125,126,126,127,127,128,128,129,129,129,130,130,130,131,131,131,131,131,132,132,132,132,132,133,134,134,136,137,140,143,147,152,158,166,174,184,194,205,215,226,235,243,249,253,254,253,249,242,233,223,212,200,188,176,166,156,147,139,133};
static unsigned int8  s_n;
static unsigned int8  e_n;
static unsigned int8 sen_n;
unsigned int8 num_sen = 57;//57

static unsigned int16 tmr2_m;
static unsigned int16 tmr2_n;
static unsigned int16 tmr2_width;
static unsigned int16 tmr2_frecu;
static unsigned int8  f_150;

static unsigned int32 adc_sum;
static unsigned int16 adc_i;
static unsigned int8  adc;
static unsigned int16 adc_val[2];
static float          adc_vol[2];
static float          adc_sen[2];

static unsigned int8 data;
static float value;
static float max;

#include <interrupt.c>
#include <function.c>
