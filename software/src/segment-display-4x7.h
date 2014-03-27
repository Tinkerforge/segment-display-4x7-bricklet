/* segment-display-4x7-bricklet
 * Copyright (C) 2013 Olaf Lüke <olaf@tinkerforge.com>
 *
 * segment-display-4x7.h: Implementation of Segment Display 4x7 Bricklet messages
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

#ifndef SEGMENT_DISPLAY_4X7_H
#define SEGMENT_DISPLAY_4X7_H

#include <stdint.h>
#include "bricklib/drivers/pio/pio.h"
#include "bricklib/com/com_common.h"

#define I2C_HALF_CLOCK_400KHZ  1250  // 2500ns per clock

#define TM1637_ADDRESS_AUTO    0x40
#define TM1637_ADDRESS_FIXED   0x44
#define TM1637_ADDERSS_DIGITS  0xC0
#define TM1637_ADDRESS_SHOW    0x88

#define TM1637_COLON_ON  0x80
#define TM1637_COLON_OFF 0

#define FID_SET_SEGMENTS 1
#define FID_GET_SEGMENTS 2
#define FID_START_COUNTER 3
#define FID_GET_COUNTER_VALUE 4
#define FID_COUNTER_FINISHED 5

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) StandardMessage;

typedef struct {
	MessageHeader header;
	uint8_t segments[4];
	uint8_t brightness;
	bool colon;
} __attribute__((__packed__)) SetSegments;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetSegments;

typedef struct {
	MessageHeader header;
	uint8_t segments[4];
	uint8_t brightness;
	bool colon;
} __attribute__((__packed__)) GetSegmentsReturn;

typedef struct {
	MessageHeader header;
	int16_t from;
	int16_t to;
	int16_t increment;
	uint32_t length;
} __attribute__((__packed__)) StartCounter;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetCounterValue;

typedef struct {
	MessageHeader header;
	uint16_t value;
} __attribute__((__packed__)) GetCounterValueReturn;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) CounterFinished;

void set_segments(const ComType com, const SetSegments *data);
void get_segments(const ComType com, const GetSegments *data);
void start_counter(const ComType com, const StartCounter *data);
void get_counter_value(const ComType com, const GetCounterValue *data);

void invocation(const ComType com, const uint8_t *data);
void constructor(void);
void destructor(void);
void tick(const uint8_t tick_type);

void update_digits(void);

void i2c_clear_bus_delay(void);
void i2c_clear_bus_9clock(Pin *sda, Pin *scl);
void i2c_clear_bus_stop(Pin *sda, Pin *scl);
void i2c_clear_bus_start(Pin *sda, Pin *scl);
void i2c_clear_bus(Pin *sda, Pin *scl);

void i2c_clk_high(void);
void i2c_clk_low(void);
bool i2c_dio_value(void);
void i2c_dio_high(void);
void i2c_dio_low(void);
void i2c_sleep_halfclock(void);
void i2c_stop(void);
void i2c_start(void);
uint8_t i2c_recv_byte(void);
bool i2c_send_byte(uint8_t value);

#endif
