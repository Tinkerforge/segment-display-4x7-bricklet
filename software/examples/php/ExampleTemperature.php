<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletSegmentDisplay4x7.php');
require_once('Tinkerforge/BrickletTemperature.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletSegmentDisplay4x7;
use Tinkerforge\BrickletTemperature;

const HOST = 'localhost';
const PORT = 4223;
const UID_DISP = 'XYZ1'; // Change to your Segment Display 4x7 Bricklet UID
const UID_TEMP = 'XYZ2'; // Change to your Temperature Bricklet UID
$DIGITS = array(0x3f,0x06,0x5b,0x4f,
                0x66,0x6d,0x7d,0x07,
                0x7f,0x6f,0x77,0x7c,
                0x39,0x5e,0x79,0x71); // 0~9,A,b,C,d,E,F

$ipcon = new IPConnection(); // Create IP connection
$sd = new BrickletSegmentDisplay4x7(UID_DISP, $ipcon); // Create device object
$t = new BrickletTemperature(UID_TEMP, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Get current temperature (unit is °C/100)
$temperature = $t->getTemperature();

// Write temperature to the display with full brightness with colon
$segments = array($DIGITS[($temperature / 1000) % 10],
                  $DIGITS[($temperature / 100) % 10],
                  $DIGITS[($temperature / 10) % 10],
                  $DIGITS[$temperature % 10]);
$sd->setSegments($segments, 7, true);

echo "Press key to exit\n";
fgetc(fopen('php://stdin', 'r'));
$ipcon->disconnect();

?>
