# Amplipi
projects that interface with the AmpliPi  from micro-nova

The AmpliPI_esp32  sketch was developed on an esp32 produced by TTGO  which includes a TFT display and two buttons.

This sketch is intended as a 'code stub' - so others can benefit from the lessons I learned when interfacing to the AmpliPi  API:
  Connecting to wifi (or an alternate);   Parsing of json to display the status of each station (statusAmplipi()); and changing settings:
  
  change the volume  (changeVolume(int))  - I plan to add a potentiometer to create a wall controller
  change the source  (changeSource(int))
  change the stream  (changeStream(int))
  make an announcement (makeAnnouncement(int)) - I plan to trigger this with a Passive InfraRed motion sensor
  
  the button functionality is based upon the TTGO  samples. 
