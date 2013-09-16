<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletSegmentDisplay4x7.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletSegmentDisplay4x7;

$host = 'localhost';
$port = 4223;
$uid = 'XYZ'; // Change to your UID
$digits = array(0x3f,0x06,0x5b,0x4f,
                0x66,0x6d,0x7d,0x07,
                0x7f,0x6f,0x77,0x7c,
                0x39,0x5e,0x79,0x71); // 0~9,A,b,C,d,E,F

$ipcon = new IPConnection(); // Create IP connection
$sd4x7 = new BrickletSegmentDisplay4x7($uid, $ipcon); // Create device object

$ipcon->connect($host, $port); // Connect to brickd
// Don't use device before ipcon is connected

// Write "4223" to the display with full brightness without colon
$segments = array($digits[4], $digits[2], $digits[2], $digits[3]);
$sd4x7->setSegments($segments, 7, false);

echo "Press key to exit\n";
fgetc(fopen('php://stdin', 'r'));
$ipcon->disconnect();

?>
