#!/bin/sh
# connects to localhost:4223 by default, use --host and --port to change it

# change to your UID
uid=XYZ
digits=(63 6 91 79 102 109 125 7 127 111 119 124 57 94 121 113)

# write "4223" to the display with full brightness without colon
segments=${digits[4]},${digits[2]},${digits[2]},${digits[3]}
tinkerforge call segment-display-4x7-bricklet $uid set-segments $segments 7 false
