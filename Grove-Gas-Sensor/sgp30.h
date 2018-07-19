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

#ifndef SGP30_H
#define SGP30_H
#include "sensirion_configuration.h"
#include "sensirion_common.h"

#if 1
#ifdef __cplusplus
extern "C" {
#endif

extern short sgp_probe(void);
extern short sgp_iaq_init(void);

extern const char *sgp_get_driver_version(void);
extern unsigned char sgp_get_configured_address(void);
extern short sgp_get_feature_set_version(unsigned short *feature_set_version, unsigned char *product_type);

extern short sgp_get_iaq_baseline(unsigned long *baseline);
extern short sgp_set_iaq_baseline(unsigned long baseline);

extern short sgp_measure_iaq_blocking_read(unsigned short *tvoc_ppb, unsigned short *co2_eq_ppm);
extern short sgp_measure_iaq(void);
extern short sgp_read_iaq(unsigned short *tvoc_ppb, unsigned short *co2_eq_ppm);

extern short sgp_measure_tvoc_blocking_read(unsigned short *tvoc_ppb);
extern short sgp_measure_tvoc(void);
extern short sgp_read_tvoc(unsigned short *tvoc_ppb);

extern short sgp_measure_co2_eq_blocking_read(unsigned short *co2_eq_ppm);
extern short sgp_measure_co2_eq(void);
extern short sgp_read_co2_eq(unsigned short *co2_eq_ppm);

extern short sgp_measure_signals_blocking_read(unsigned short *scaled_ethanol_signal,
                                      unsigned short *scaled_h2_signal);
extern short sgp_measure_signals(void);
extern short sgp_read_signals(unsigned short *scaled_ethanol_signal, unsigned short *scaled_h2_signal);

extern short sgp_measure_test(unsigned short *test_result);

extern short sgp_set_absolute_humidity(unsigned long absolute_humidity);

#ifdef __cplusplus
}
#endif
#endif

#if 0
class sgp_measure {


public:
	sgp_measure(){}
	short sgp_probe(void);
	short sgp_iaq_init(void);
	
	const char *sgp_get_driver_version(void);
	unsigned char sgp_get_configured_address(void);
	short sgp_get_feature_set_version(unsigned short *feature_set_version, unsigned char *product_type);
	
	short sgp_get_iaq_baseline(unsigned long *baseline);
	short sgp_set_iaq_baseline(unsigned long baseline);
	
	short sgp_measure_iaq_blocking_read(unsigned short *tvoc_ppb, unsigned short *co2_eq_ppm);
	short sgp_measure_iaq(void);
	short sgp_read_iaq(unsigned short *tvoc_ppb, unsigned short *co2_eq_ppm);
	
	short sgp_measure_tvoc_blocking_read(unsigned short *tvoc_ppb);
	short sgp_measure_tvoc(void);
	short sgp_read_tvoc(unsigned short *tvoc_ppb);
	
	short sgp_measure_co2_eq_blocking_read(unsigned short *co2_eq_ppm);
	short sgp_measure_co2_eq(void);
	short sgp_read_co2_eq(unsigned short *co2_eq_ppm);
	
	short sgp_measure_signals_blocking_read( unsigned short *scaled_ethanol_signal,
										   unsigned short *scaled_h2_signal);
	short sgp_measure_signals(void);
	short sgp_read_signals(unsigned short *scaled_ethanol_signal, unsigned short *scaled_h2_signal);
	
	short sgp_measure_test(unsigned short *test_result);
	
	short sgp_set_absolute_humidity(unsigned long absolute_humidity);
	~sgp_measure(){}

};
#endif


#endif /* SGP30_H */

