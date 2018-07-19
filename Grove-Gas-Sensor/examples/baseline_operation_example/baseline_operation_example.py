#-----------

import Sensirion
from ctypes import *
import time
import ctypes
'''
EEPROM PATH:LOCATIOM
'''
EEPROMPATH = "./EEPROM.txt"

BASELINE_IS_STORED_FLAG = 0X55

i = 0


class eepromRW(object):
	def __init__(self,_path):
		self.path 	= _path
		
	def read_eeprom(self):
		
		result=[]
		fd = file(self.path, "r")
		
		for line in fd.readlines():
			result = line.split(' ')
		fd.close()
		
		return result
		

	def write_eeprom(self,string):
		fd = file(self.path, "wr+")
		fd.truncate()
		renum = fd.write(string)
		fd.close()
		return renum 
		
		

print("serial start!!\n");

eepromObjc = eepromRW(EEPROMPATH)



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

Sensirion.sgp_set_absolute_humidity(300000);

#err = Sensirion.sgp_iaq_init();



def array_to_u32(array):
	value = 0x00000000
	value = (value)|int(array[0]) << 24
	value = (value)|int(array[1]) << 16
	value = (value)|int(array[2]) << 8
	value = (value)|int(array[3])
	return value
	
def u32_to_array(longNumben):
	result = [0,0,0,0]
	result[0] = int((longNumben >> 24) & 0xFF)
	result[1] = int((longNumben >> 16) & 0xFF)
	result[2] = int((longNumben >> 8 ) & 0xFF)
	result[3] = int((longNumben >> 0 ) & 0xFF)
	
	return result
	
	


def set_baseline():
		
		baseline = [0,0,0,0,0]
		baseline_value=0
		baseline = eepromObjc.read_eeprom();
		print("%x %x %x %x %x"%(int(baseline[0]),int(baseline[1]),int(baseline[2]),int(baseline[3]),int(baseline[4])))
		if int(baseline[4]) != BASELINE_IS_STORED_FLAG:
			print("There is no baseline value in EEPROM")
			return;
		
		u32value = array_to_u32(baseline)
		
			
		Sensirion.sgp_set_iaq_baseline(u32value)
		print("u32value :%x "%(u32value)) 
		
		
			
def store_baseline():
	global i
	i = i+1
	print(i)	
	if i == 2000 :
		i = 0
		iaq_baseline = Sensirion.new_ulong()
		
		if Sensirion.sgp_get_iaq_baseline(iaq_baseline) != Sensirion.STATUS_OK:
			print("get baseline failed!")
		else:
			print("iaq_baseline %x "%(Sensirion.ulong_value(iaq_baseline)))
			print("get baseline")
			revArr = u32_to_array(Sensirion.ulong_value(iaq_baseline))
			
			print len(revArr)
			if len(revArr) == 4 :
				
				print("%x %x %x %x"%(int(revArr[0]),int(revArr[1]),int(revArr[2]),int(revArr[3])))
				
				strForm = str(revArr[0])+" "+str(revArr[1])+" "+str(revArr[2])+" "+str(revArr[3])+" 85"
				print strForm
				eepromObjc.write_eeprom(strForm)
			
	
	time.sleep(0.1)
		
	

	
	
'''
init ...
'''	
	
set_baseline()
	

while True:
	tvoc_ppb = Sensirion.new_ushortp();
	co2_eq_ppm = Sensirion.new_ushortp();

	err = Sensirion.sgp_measure_iaq_blocking_read(tvoc_ppb, co2_eq_ppm)
	if err == Sensirion.STATUS_OK:

		print("tVOC  Concentration: %d ppb"%(Sensirion.ushortp_value(tvoc_ppb)));
		print("CO2eq Concentration: %d ppm"%(Sensirion.ushortp_value(co2_eq_ppm)));
		
		print("")
		  
	else :
		 print("error reading IAQ values\n"); 
	
	store_baseline()
        
