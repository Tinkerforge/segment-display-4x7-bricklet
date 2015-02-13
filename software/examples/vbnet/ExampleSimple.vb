Imports Tinkerforge

Module ExampleSimple
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "XYZ" ' Change to your UID
    Dim DIGITS() As Byte = {&H3f,&H06,&H5b,&H4f, _
                            &H66,&H6d,&H7d,&H07, _
                            &H7f,&H6f,&H77,&H7c, _
                            &H39,&H5e,&H79,&H71} ' 0~9,A,b,C,d,E,F

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim sd4x7 As New BrickletSegmentDisplay4x7(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        ' Write "4223" to the display with full brightness without colon
        Dim segments() As Byte = {DIGITS(4), DIGITS(2), DIGITS(2), DIGITS(3)}
        sd4x7.SetSegments(segments, 7, false)

        System.Console.WriteLine("Press key to exit")
        System.Console.ReadLine()
        ipcon.Disconnect()
    End Sub
End Module
