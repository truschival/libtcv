/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 George Redivo
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

/************************************************************************************
 * \file   tcv_internal.h
 * \brief  Internal Data structures and transceiver helper functions,
 * 		   not to be included by client
 * \author  ruschi
 *  		Copyright (c) - 2014 thomas ruschival <thomas@ruschival.de>
 * Created on: Jun 29, 2014
 ************************************************************************************/

#ifndef TCV_INTERNAL_H_
#define TCV_INTERNAL_H_

#include <stdint.h>
#include <stddef.h>
#include <pthread.h>
#include <stdbool.h>
/* include public interface */
#include "libtcv/tcv.h"

/**
 * \brief	Generic transceiver structure.
 *
 * It's a generic transceiver representation, it's valid for both SFP and XFP.
 */
struct tcv_t{
	int index;				//! Port index referent to TCV port.
	i2c_read_cb_t read;		//! Callback to I2C read function.
	i2c_write_cb_t write;	//! Callback to I2C write function.
	const struct tcv_functions * fun; //! Transceiver methods
	/** TCV internal data - don't touch !*/
	void *data;
	pthread_mutex_t lock; //! Lock for library functions
	bool created; //! tcv has been initialized by tcv_create()
	bool initialized; //! tcv has been initialized by tcv_init()
};


/**
 * \brief Transceiver methods
 *
 * generic get/set operations on transceivers
 */
struct tcv_functions {
	int (*get_identifier)(tcv_t *);
	int (*get_ext_identifier)(tcv_t *);
	int (*get_connector)(tcv_t *);
	int (*get_vendor_name)(tcv_t *, char* name);
	int (*get_vendor_oui)(tcv_t *);
	int (*get_vendor_revision)(tcv_t *, char* rev);
	int (*get_vendor_part_number)(tcv_t *, char* pn);
	int (*get_vendor_serial_number)(tcv_t *, char* sn);
	int (*get_vendor_date_code)(tcv_t *, tcv_date_code_t *);
	const uint8_t* (*get_vendor_rom)(tcv_t *);
	size_t (*get_vendor_rom_size)(tcv_t *);
	const uint8_t* (*get_user_writable_eeprom)(tcv_t *);
	size_t (*get_user_writable_eeprom_size)(tcv_t *);
	int (*get_10g_compliance_codes)(tcv_t *, tcv_10g_eth_compliance_codes_t *);
	int (*get_infiniband_compliance_codes)(tcv_t *,
	                                       tcv_infiniband_compliance_codes_t *);
	int (*get_escon_compliance_codes)(tcv_t *, tcv_escon_compliance_codes_t *);
	int (*get_sonet_compliance_codes)(tcv_t *, tcv_sonet_compliance_codes_t *);
	int (*get_eth_compliance_codes)(tcv_t *, tcv_eth_compliance_codes_t *);
	int (*get_fibre_channel_link_length)(tcv_t *,
	                                     tcv_fibre_channel_link_length_t *);
	int (*get_fibre_channel_technology)(tcv_t *,
	                                    tcv_fibre_channel_technology_t *);
	int (*get_sfp_plus_cable_technology)(tcv_t *,
	                                     sfp_plus_cable_technology_t *);
	int (*get_fibre_channel_media)(tcv_t *, tcv_fibre_channel_media_t *);
	int (*get_fibre_channel_speed)(tcv_t *, fibre_channel_speed_t *);
	int (*get_encoding)(tcv_t*);
	int (*get_nominal_bit_rate)(tcv_t*);
	int (*get_rate_identifier)(tcv_t*);
	int (*get_sm_length)(tcv_t *);
	int (*get_max_bit_rate)(tcv_t*);
	int (*get_min_bit_rate)(tcv_t*);
	int (*get_diagnostic_type)(tcv_t *, tcv_diagnostic_type_t *);
	int (*get_enhanced_options)(tcv_t *, tcv_enhanced_options_type_t *);
	int (*get_cc_ext)(tcv_t*);
	int (*calculate_cc_ext)(tcv_t *);
	int (*get_om1_length)(tcv_t *);
	int (*get_om2_length)(tcv_t *);
	int (*get_om3_length)(tcv_t *);
	int (*get_om4_copper_length)(tcv_t *);
	int (*get_wave_len)(tcv_t*);
	int (*get_passive_cable_compliance)(tcv_t *, passive_cable_compliance_t *);
	int (*get_active_cable_compliance)(tcv_t *, active_cable_compliance_t *);
	int (*get_cc_base)(tcv_t*);
	int (*calculate_cc_base)(tcv_t *);
	int (*get_implemented_options)(tcv_t *, tcv_implemented_options_t *);
	const uint8_t* (*get_8079_rom)(tcv_t *);
	int (*raw_read)(tcv_t *, uint8_t, uint8_t, uint8_t*, size_t);
	int (*raw_write)(tcv_t *, uint8_t, uint8_t, const uint8_t*, size_t);
	/* digital diagnostics */
	int (*get_rx_pwr)(tcv_t*, uint16_t*);
	int (*get_tx_pwr)(tcv_t*, uint16_t*);
	int (*get_tx_cur)(tcv_t*, uint16_t*);
	int (*get_temp)(tcv_t*, int16_t*);
	int (*get_voltage)(tcv_t*, uint16_t*);
	int (*get_temp_high_warning)(tcv_t*, uint16_t*);
	int (*get_tx_pwr_high_warning)(tcv_t*, uint16_t*);
	int (*get_rx_pwr_high_warning)(tcv_t*, uint16_t*);
};
/******************************************************************************/

#endif /* TCV_INTERNAL_H_ */
