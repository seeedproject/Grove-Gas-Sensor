%module Sensirion
%{
 #include <stdint.h>
 #include "sensirion_common.h"
 #include "sgp30.h"
%}

%include "stdint.i" 
%include "sensirion_common.h"
%include "sgp30.h"
extern short sgp_measure_signals_blocking_read( unsigned short *scaled_ethanol_signal, unsigned short *scaled_h2_signal);
extern short sgp_get_iaq_baseline(unsigned long *baseline);

%include cpointer.i
%pointer_functions(unsigned short,  ushortp);
%pointer_functions(unsigned long,  ulong);

