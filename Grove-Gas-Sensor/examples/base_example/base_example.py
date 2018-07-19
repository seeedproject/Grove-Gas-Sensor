#-----------

import Sensirion

from ctypes import *
import time


print("serial start!!\n");


if Sensirion.sgp_probe() != Sensirion.STATUS_OK :
	print("SGP failed\n")

scaled_ethanol_signal = Sensirion.new_ushortp();
scaled_h2_signal = Sensirion.new_ushortp();

err = Sensirion.sgp_measure_signals_blocking_read(scaled_ethanol_signal,scaled_h2_signal)

#print(Sensirion.ushortp_value(scaled_ethanol_signal))
#print(Sensirion.ushortp_value(scaled_h2_signal))

if err == Sensirion.STATUS_OK :
	print("get ram signal!");
else:
	print("error reading signals"); 

Sensirion.sgp_set_absolute_humidity(200000);

err = Sensirion.sgp_iaq_init();

while True:
	tvoc_ppb = Sensirion.new_ushortp();
	co2_eq_ppm = Sensirion.new_ushortp();

	err = Sensirion.sgp_measure_iaq_blocking_read(tvoc_ppb, co2_eq_ppm)
	if err == Sensirion.STATUS_OK:

		print("tVOC  Concentration: %d ppb"%(Sensirion.ushortp_value(tvoc_ppb)));
		print("CO2eq Concentration: %d ppm"%(Sensirion.ushortp_value(co2_eq_ppm)));
		
		print("\n")
		  
	else :
		 print("error reading IAQ values\n"); 
	
	time.sleep(0.1)
        
