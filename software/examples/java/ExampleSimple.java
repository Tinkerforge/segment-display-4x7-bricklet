import com.tinkerforge.BrickletSegmentDisplay4x7;
import com.tinkerforge.IPConnection;

public class ExampleSimple {
	private static final String HOST = "localhost";
	private static final int PORT = 4223;
	private static final String UID = "XYZ"; // Change to your UID
	private static final byte[] DIGITS = {0x3f,0x06,0x5b,0x4f,
	                                      0x66,0x6d,0x7d,0x07,
	                                      0x7f,0x6f,0x77,0x7c,
	                                      0x39,0x5e,0x79,0x71}; // 0~9,A,b,C,d,E,F
	
	// Note: To make the example code cleaner we do not handle exceptions. Exceptions you
	//       might normally want to catch are described in the documentation
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletSegmentDisplay4x7 sd4x7 = new BrickletSegmentDisplay4x7(UID, ipcon); // Create device object

		ipcon.connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Write "4223" to the display with full brightness without colon
		short[] segments = {DIGITS[4], DIGITS[2], DIGITS[2], DIGITS[3]};
		sd4x7.setSegments(segments, (short)7, false);

		System.out.println("Press key to exit"); System.in.read();
		ipcon.disconnect();
	}
}
