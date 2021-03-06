#!/usr/bin/env ruby
# -*- ruby encoding: utf-8 -*-

require 'tinkerforge/ip_connection'
require 'tinkerforge/bricklet_segment_display_4x7'

include Tinkerforge

HOST = 'localhost'
PORT = 4223
UID = 'XYZ' # Change XYZ to the UID of your Segment Display 4x7 Bricklet
DIGITS = [0x3f,0x06,0x5b,0x4f,
          0x66,0x6d,0x7d,0x07,
          0x7f,0x6f,0x77,0x7c,
          0x39,0x5e,0x79,0x71] # // 0~9,A,b,C,d,E,F

ipcon = IPConnection.new # Create IP connection
sd = BrickletSegmentDisplay4x7.new UID, ipcon # Create device object

ipcon.connect HOST, PORT # Connect to brickd
# Don't use device before ipcon is connected

# Write "4223" to the display with full brightness without colon
segments = [DIGITS[4], DIGITS[2], DIGITS[2], DIGITS[3]]
sd.set_segments segments, 7, false

puts 'Press key to exit'
$stdin.gets
ipcon.disconnect
