/*
 * Copyright (c) 2017, Sensirion AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of Sensirion AG nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "i2c.h"
// needed for delay() routine
#ifdef __ARDUINO__
#include <Arduino.h>
#include <Wire.h>
#else
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "i2crw.h"
#endif

/*
 * INSTRUCTIONS
 * ============
 *
 * Use the "arduino_example.ino" and copy
 * sht.h, shtxx.c, sht_common.h, sht_common.c, i2c.h,
 * hw_i2c/configuration.h, hw_i2c/configuration_Arduino.cpp
 * in the .ino folder.
 * Follow the function specification in the comments.
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize all hard- and software components that are needed for the I2C
 * communication. After this function has been called, the functions
 * i2c_read() and i2c_write() must succeed.
 */

void sensirion_i2c_init(uint8_t address)
{
#ifdef __ARDUINO__

   Wire.begin();
#else
	i2ccrw.begin(1, address);
#endif

}

int8_t sensirion_i2c_smbusblock_proccall(uint8_t command, uint8_t length, uint8_t * values)
{
   i2ccrw.i2c_smbus_block_proccall(command,  length,  values);

    return 0;
}


int8_t sensirion_i2c_read(uint8_t address, uint8_t* data, uint16_t count)
{
    
   
#ifdef __ARDUINO__
	 uint8_t readData[count];

	 uint8_t rxByteCount=0;
    // 2 bytes RH, 1 CRC, 2 bytes T, 1 CRC
    Wire.requestFrom(address, count);

    while (Wire.available()) { // wait till all arrive
      readData[rxByteCount++] = Wire.read();
      if(rxByteCount >= count)
        break;
    }
	 memcpy(data, readData, count);
#else
	//printf("read file lenth :%d \n",count);
//	int i;

	switch(count){
	
			case 1:
				*data = i2ccrw.i2c_read_bdata(address);
				break;
			case 2:{
					uint16_t hexvalue;
					hexvalue = i2ccrw.i2c_read_wdata(address);
					data[0] = (hexvalue & 0x00FF);
					data[1] = (hexvalue & 0xFF00) >> 8;
					//printf("read pdata( 1 0): %x %x  word:%#x \n",data[1],data[0],hexvalue);
					break;
				}
			default:
				i2ccrw.i2c_read_block_data(address, count,data);
				
				break;
		}
	
	//for(i=0;i<count;i++)
	//	printf("%x ",data[i]);
	//printf("\n");
#endif
   

    return 0;
}

int8_t sensirion_i2c_write(uint8_t address, const uint8_t* data, uint16_t count)
{
#ifdef __ARDUINO__
    Wire.beginTransmission(address);
    Wire.write(data, count);
    Wire.endTransmission();
#else
	
	
	//printf("write pdata( 1 0): %x %x   count=%d \n",data[1],data[0],count);
	
	//int i;
	//	for(i=0;i<count;i++)
	//		printf("0x%x ",data[i]);
	//	printf("\n");

	switch(count){

		case 1:
			printf("i2c command error\n");
			break;
		case 2:{
			i2ccrw.i2c_write_bdata(data[0], data[1]);
			break;}
		default:
			i2ccrw.i2c_write_block_data(data[0], count-1,(uint8_t* )&data[1]);
			break;
	}

#endif

    return 0;
}

/**
 * Sleep for a given number of microseconds. The function should delay the
 * execution for at least the given time, but may also sleep longer.
 *
 * @param useconds the sleep time in microseconds
 */
void sensirion_sleep_usec(uint32_t useconds) {
#ifdef __ARDUINO__
    delay((useconds / 1000) + 1);

#else
usleep((useconds) + 1);
#endif
}

#ifdef __cplusplus
} // extern "C"
#endif
