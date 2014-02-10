#!/usr/bin/perl  

use Tinkerforge::IPConnection;
use Tinkerforge::BrickletSegmentDisplay4x7;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'ioiu'; # Change to your UID

my @digits = (0x3f,0x06,0x5b,0x4f,
	          0x66,0x6d,0x7d,0x07,
	          0x7f,0x6f,0x77,0x7c,
	          0x39,0x5e,0x79,0x71); # // 0~9,A,b,C,d,E,F

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $sd4x7 = Tinkerforge::BrickletSegmentDisplay4x7->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Write "4223" to the display with full brightness without colon
my @segments;

push(@segments, $digits[4]);
push(@segments, $digits[2]);
push(@segments, $digits[2]);
push(@segments, $digits[3]);

$sd4x7->set_segments(\@segments, 7, 0);

print "\nPress any key to exit...\n";
<STDIN>;
$ipcon->disconnect();
