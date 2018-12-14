package main

import (
	"fmt"
	"tinkerforge/ipconnection"
    "tinkerforge/segment_display_4x7_bricklet"
)

const ADDR string = "localhost:4223"
const UID string = "XYZ" // Change XYZ to the UID of your Segment Display 4x7 Bricklet.

var DIGITS = [16]uint8{0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71} // 0~9,A,b,C,d,E,F

func main() {
	ipcon := ipconnection.New()
    defer ipcon.Close()
	sd, _ := segment_display_4x7_bricklet.New(UID, &ipcon) // Create device object.

	ipcon.Connect(ADDR) // Connect to brickd.
    defer ipcon.Disconnect()
	// Don't use device before ipcon is connected.

	segments := [4]uint8{DIGITS[4], DIGITS[2], DIGITS[2], DIGITS[3]}
	sd.SetSegments(segments, 7, false)

	fmt.Print("Press enter to exit.")
	fmt.Scanln()

	ipcon.Disconnect()
}
