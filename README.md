# Amplipi
### These are my projects that interface with the [AmpliPi](https://github.com/micro-nova/AmpliPi)  from [micro-nova](https://www.micro-nova.com/)

## esp32  Microcontroller 
The AmpliPI_esp32  sketch was developed on an [TTGO-T-Display](https://github.com/Xinyuan-LilyGO/TTGO-T-Display) esp32 produced by [LilyGO](https://github.com/Xinyuan-LilyGO)  which includes a TFT display and two buttons.
![](https://github.com/vszander/Amplipi/blob/main/docs/img/AmpliPi-ttgo.png)

This sketch is intended as a 'code stub' - so others can benefit from the lessons I learned when interfacing to the AmpliPi  API:
-  Connecting to wifi (or an alternate);   Parsing of json to display the status of each station (statusAmplipi()); and changing settings:
  
-  change the volume  (changeVolume(int))  - I plan to add a potentiometer to create a wall controller
-  change the source  (changeSource(int))
-  change the stream  (changeStream(int))
-  make an announcement (makeAnnouncement(int)) - I plan to trigger this with a Passive InfraRed motion sensor
  
  the button functionality is based upon the TTGO  [samples](https://github.com/Xinyuan-LilyGO/TTGO-T-Display/tree/master/TFT_eSPI/examples/FactoryTest). 
