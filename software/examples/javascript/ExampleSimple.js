var IPConnection = require('Tinkerforge/IPConnection');
var BrickletSegmentDisplay4x7 = require('Tinkerforge/BrickletSegmentDisplay4x7');

var HOST = 'localhost';
var PORT = 4223;
var UID = 'iWR';// Change to your UID
var DIGITS = [0x3f,0x06,0x5b,0x4f,
              0x66,0x6d,0x7d,0x07,
	          0x7f,0x6f,0x77,0x7c,
	          0x39,0x5e,0x79,0x71];// 0~9,A,b,C,d,E,F

var ipcon = new IPConnection();// Create IP connection
var sd4x7 = new BrickletSegmentDisplay4x7(UID, ipcon);// Create device object

ipcon.connect(HOST, PORT,
    function(error) {
        console.log('Error: '+error);        
    }
);// Connect to brickd

// Don't use device before ipcon is connected
ipcon.on(IPConnection.CALLBACK_CONNECTED,
    function(connectReason) {
        // Write "4223" to the display with full brightness without colon
        var segments = [DIGITS[4], DIGITS[2], DIGITS[2], DIGITS[3]];
        sd4x7.setSegments(segments, 7, false);
    }
);

console.log("Press any key to exit ...");
process.stdin.on('data',
    function(data) {
        ipcon.disconnect();
        process.exit(0);
    }
);

