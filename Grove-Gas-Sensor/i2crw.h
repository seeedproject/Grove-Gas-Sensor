#ifndef _I2CRW_H
#define _I2CRW_H

#include "sensirion_configuration.h"

class I2Common
{
	private:
		static uint32_t 	adapterNr;
		static uint32_t 	saveAddress;
		static int32_t		file;
		static char 		filename[20];
	public:
		I2Common(void);
	    void begin(uint32_t,uint32_t);
	    void end(void);
		virtual int32_t i2c_read_wdata( uint8_t );
		virtual int32_t i2c_write_wdata(uint8_t, uint16_t );
		virtual int32_t i2c_read_bdata( uint8_t );
		virtual int32_t i2c_write_bdata(uint8_t, uint8_t );
		virtual int32_t i2c_read_block_data( uint8_t ,uint8_t ,uint8_t* );
		virtual int32_t i2c_write_block_data(uint8_t , uint8_t ,uint8_t*);
		virtual int32_t i2c_smbus_block_proccall( uint8_t command, uint8_t length,	uint8_t *values);
		
};

extern I2Common i2ccrw;



#endif /* _I2CRW_H  */
