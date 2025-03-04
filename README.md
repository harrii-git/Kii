# Kii
Code wirrten in Arduino IDE to use a WiiMote as an input device when connected to an esp32 Arduino module. In this case the input is used to turn a servo and open a lock. 

Connect the WiiMote to the Arduino by holding 1 and 2 simultaneously.

Unlock the lock by entering A-1-2-B on the WiiMote.

Lock the door again by pressing A and B at the same time on the WiiMote.

Libraries --------------------------------------------------------------------------------------------------------------------------------------------------------------

This porject uses the Arduino libary ESP32Wiimote, a fork of which can be found [here](https://github.com/hrgraf/ESP32Wiimote). 

It also uses the library ESP32Servo to communicate between the main board and the servo. 

Setting Password --------------------------------------------------------------------------------------------------------------------------------------------------------------

I have set the default password to A-1-2-B, though this can be changed around line 9 under passwordSequence. If you do change / increase the length of the password then you also need to increase the value of currentStep to the length of your new password in the if statement on line 62. For exmaple, if you change the password to A-1-2-B-C-B then you will need to increase 'currentStep == 4' to 'currentStep == 6'.

It should also be noted that using this code, the password has to start with A. Otherwise, the programme thinks that you have reset the input combo and result in a failed entry attempt. 

I am aware that I am a horrible programmer and there are definitely better ways to do this. 




