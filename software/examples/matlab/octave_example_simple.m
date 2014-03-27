function octave_example_simple
    more off;
    
    HOST = "localhost";
    PORT = 4223;
    UID = "kTf"; % Change to your UID

    DIGITS = [hex2dec("3f") hex2dec("06") hex2dec("5b") ...
              hex2dec("4f") hex2dec("66") hex2dec("6d") ...
              hex2dec("7d") hex2dec("07") hex2dec("7f") ...
              hex2dec("6f") hex2dec("77") hex2dec("7c") ...
              hex2dec("39") hex2dec("5e") hex2dec("79") ...
              hex2dec("71")]; % 0~9,A,b,C,d,E,F
          
    ipcon = java_new("com.tinkerforge.IPConnection"); % Create IP connection
    sd4x7 = java_new("com.tinkerforge.BrickletSegmentDisplay4x7", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Write "4223" to the display with full brightness without colon.
    % Adding 1 with the index because the array was designed for arrays
    % that starts with index 0 but OCTAVE arrays start with index 1.
    segments = [DIGITS(4+1) DIGITS(2+1) DIGITS(2+1) DIGITS(3+1)];
    sd4x7.setSegments(segments, 7, false);

    input("\nPress any key to exit...\n", "s");
    ipcon.disconnect();
end
