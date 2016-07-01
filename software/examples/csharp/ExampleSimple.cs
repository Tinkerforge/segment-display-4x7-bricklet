using System;
using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XYZ"; // Change XYZ to the UID of your Segment Display 4x7 Bricklet
	private static byte[] DIGITS = {0x3f,0x06,0x5b,0x4f,
	                                0x66,0x6d,0x7d,0x07,
	                                0x7f,0x6f,0x77,0x7c,
	                                0x39,0x5e,0x79,0x71}; // 0~9,A,b,C,d,E,F

	static void Main()
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletSegmentDisplay4x7 sd =
		  new BrickletSegmentDisplay4x7(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Write "4223" to the display with full brightness without colon
		byte[] segments = {DIGITS[4], DIGITS[2], DIGITS[2], DIGITS[3]};
		sd.SetSegments(segments, 7, false);

		Console.WriteLine("Press enter to exit");
		Console.ReadLine();
		ipcon.Disconnect();
	}
}
