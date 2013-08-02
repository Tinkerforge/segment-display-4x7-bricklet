/* segment-display-4x7-bricklet
 * Copyright (C) 2013 Olaf Lüke <olaf@tinkerforge.com>
 *
 * segment-display-4x7.c: Implementation of Segment Display 4x7 Bricklet messages
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "segment-display-4x7.h"

#include "bricklib/bricklet/bricklet_communication.h"
#include "bricklib/utility/util_definitions.h"
#include "bricklib/utility/init.h"
#include "bricklib/drivers/adc/adc.h"
#include "brickletlib/bricklet_entry.h"
#include "brickletlib/bricklet_simple.h"
#include "config.h"

const uint8_t digits[] = {0x3f,0x06,0x5b,0x4f,
                          0x66,0x6d,0x7d,0x07,
                          0x7f,0x6f,0x77,0x7c,
                          0x39,0x5e,0x79,0x71}; // 0~9,A,b,C,d,E,F

void invocation(const ComType com, const uint8_t *data) {
	switch(((MessageHeader*)data)->fid) {
		case FID_SET_SEGMENTS: {
			set_segments(com, (SetSegments*)data);
			return;
		}

		case FID_GET_SEGMENTS: {
			get_segments(com, (GetSegments*)data);
			return;
		}

		default: {
			BA->com_return_error(data, sizeof(MessageHeader), MESSAGE_ERROR_CODE_NOT_SUPPORTED, com);
			return;
		}
	}
}

void set_segments(const ComType com, const SetSegments *data) {
	BC->segments[0]  = data->segments[0] & 0x7F;
	BC->segments[1]  = data->segments[1] & 0x7F;
	BC->segments[2]  = data->segments[2] & 0x7F;
	BC->segments[3]  = data->segments[3] & 0x7F;
	BC->brightness   = MIN(data->brightness, 7);
	BC->clock_points = data->clock_points;

	update_digits();

	BA->com_return_setter(com, data);
}

void get_segments(const ComType com, const GetSegments *data) {
	GetSegmentsReturn gsr;
	gsr.header        = data->header;
	gsr.header.length = sizeof(GetSegmentsReturn);

	gsr.segments[0]   = BC->segments[0];
	gsr.segments[1]   = BC->segments[1];
	gsr.segments[2]   = BC->segments[2];
	gsr.segments[3]   = BC->segments[3];
	gsr.brightness    = BC->brightness;
	gsr.clock_points  = BC->clock_points;

	BA->send_blocking_with_timeout(&gsr,
	                               sizeof(GetSegmentsReturn),
	                               com);
}

void constructor(void) {
    PIN_DIO.type = PIO_INPUT;
    PIN_DIO.attribute = PIO_DEFAULT;
    BA->PIO_Configure(&PIN_DIO, 1);
    PIN_DIO.pio->PIO_CODR = PIN_DIO.mask;

    PIN_CLK.type = PIO_INPUT;
    PIN_CLK.attribute = PIO_DEFAULT;
    BA->PIO_Configure(&PIN_CLK, 1);
    PIN_CLK.pio->PIO_CODR = PIN_CLK.mask;

	BC->segments[0] = 0;
	BC->segments[1] = 0;
	BC->segments[2] = 0;
	BC->segments[3] = 0;
	BC->brightness = 0;
	BC->clock_points = false;

    BC->tick = 0;
}

void destructor(void) {
    PIN_DIO.type = PIO_INPUT;
    PIN_DIO.attribute = PIO_PULLUP;
    BA->PIO_Configure(&PIN_DIO, 1);

    PIN_CLK.type = PIO_INPUT;
    PIN_CLK.attribute = PIO_PULLUP;
    BA->PIO_Configure(&PIN_CLK, 1);
}

bool i2c_clk_value(void) {
	return PIN_CLK.pio->PIO_PDSR & PIN_CLK.mask;
}

void i2c_clk_high(void) {
	PIN_CLK.pio->PIO_ODR = PIN_CLK.mask;
}

void i2c_clk_low(void) {
	PIN_CLK.pio->PIO_OER = PIN_CLK.mask;
}

bool i2c_dio_value(void) {
	return PIN_DIO.pio->PIO_PDSR & PIN_DIO.mask;
}

void i2c_dio_high(void) {
	PIN_DIO.pio->PIO_ODR = PIN_DIO.mask;
}

void i2c_dio_low(void) {
	PIN_DIO.pio->PIO_OER = PIN_DIO.mask;
}

void i2c_sleep_halfclock(void) {
	SLEEP_NS(I2C_HALF_CLOCK_400KHZ);
}

void i2c_stop(void) {
	i2c_clk_low();
	i2c_dio_low();
	i2c_sleep_halfclock();
	i2c_clk_high();
	i2c_sleep_halfclock();
	i2c_dio_high();
	i2c_sleep_halfclock();
}

void i2c_start(void) {
	i2c_clk_high();
	i2c_sleep_halfclock();
	i2c_dio_low();
	i2c_sleep_halfclock();
}

uint8_t i2c_recv_byte(void) {
	uint8_t value;

	for(int8_t i = 0; i < 8; i++) {
		i2c_clk_low();
		i2c_sleep_halfclock();
		i2c_clk_high();
		value |= (1 << i);
		i2c_sleep_halfclock();
	}

	// Wait for ACK
	bool ret = false;

	i2c_clk_low();
	i2c_sleep_halfclock();
	i2c_clk_high();
	if(!i2c_dio_value()) {
		ret = true;
	}

	i2c_sleep_halfclock();
	return ret;
}

bool i2c_send_byte(const uint8_t value) {
	for(int8_t i = 0; i < 8; i++) {
		i2c_clk_low();
		if((value >> i) & 1) {
			i2c_dio_high();
		} else {
			i2c_dio_low();
		}
		i2c_sleep_halfclock();
		i2c_clk_high();
		i2c_sleep_halfclock();
	}

	// Wait for ACK
	bool ret = false;

	i2c_clk_low();
	i2c_sleep_halfclock();
	i2c_clk_high();
	if(!i2c_dio_value()) {
		ret = true;
	}

	i2c_sleep_halfclock();
	return ret;
}

void update_digits(void) {
	i2c_start();
	i2c_send_byte(TM1637_ADDRESS_AUTO);
	i2c_stop();

	i2c_sleep_halfclock();
	i2c_sleep_halfclock();

	i2c_start();
	i2c_send_byte(TM1637_ADDERSS_DIGITS);
	i2c_send_byte(BC->segments[3] | (BC->clock_points ? TM1637_CLOCK_POINT_ON : TM1637_CLOCK_POINT_OFF));
	i2c_send_byte(BC->segments[2] | (BC->clock_points ? TM1637_CLOCK_POINT_ON : TM1637_CLOCK_POINT_OFF));
	i2c_send_byte(BC->segments[1] | (BC->clock_points ? TM1637_CLOCK_POINT_ON : TM1637_CLOCK_POINT_OFF));
	i2c_send_byte(BC->segments[0] | (BC->clock_points ? TM1637_CLOCK_POINT_ON : TM1637_CLOCK_POINT_OFF));
	i2c_stop();

	i2c_sleep_halfclock();
	i2c_sleep_halfclock();

	i2c_start();
	i2c_send_byte(TM1637_ADDRESS_SHOW + BC->brightness);
	i2c_stop();
}

void tick(const uint8_t tick_type) {
}
