# PushButtonCommand
Arduino push button command's to read click, double click and long push of push buttons.

In one of my Arduino projects I use push buttons to set commands for a remote server. This server is polling my Arduino by 
Modbus RTU/TCP for any commands. As the cycle time over Modbus is longer as necessary to detect double clicks, I decided to 
write my own push button library. 

The push button library can be used to detect click, double click and long push of any push buttons. In special it’s possible 
to store the command until it’s read from a remote system. Once it was read, the command can be reseted and the command 
detection starts again. 

Find the Arduino sketch example for understanding the use of this library.

