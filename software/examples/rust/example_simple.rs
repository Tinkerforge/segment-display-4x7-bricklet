use std::{error::Error, io};

use tinkerforge::{ip_connection::IpConnection, segment_display_4x7_bricklet::*};

const HOST: &str = "127.0.0.1";
const PORT: u16 = 4223;
const UID: &str = "XYZ"; // Change XYZ to the UID of your Segment Display 4x7 Bricklet

const DIGITS: [u8; 16] = [0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71]; // 0~9,A,b,C,d,E,F

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection
    let sd = SegmentDisplay4x7Bricklet::new(UID, &ipcon); // Create device object

    ipcon.connect((HOST, PORT)).recv()??; // Connect to brickd
                                          // Don't use device before ipcon is connected

    // Write "4223" to the display with full brightness without colon
    let segments = [DIGITS[4], DIGITS[2], DIGITS[2], DIGITS[3]];
    sd.set_segments(segments, 7, false);

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;
    ipcon.disconnect();
    Ok(())
}
